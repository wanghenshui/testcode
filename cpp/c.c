#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>


int token;                    // current token
int token_val;                // value of current token (mainly for number)
char *src, *old_src;          // pointer to source code string;
int poolsize;                 // default size of text/data/stack
int line;                     // line number
int *text,                    // text segment
    *old_text,                // for dump text segment
    *stack;                   // stack
char *data;                   // data segment

/*
PC 程序计数器，它存放的是一个内存地址，该地址中存放着 下一条 要执行的计算机指令。
SP 指针寄存器，永远指向当前的栈顶。注意的是由于栈是位于高地址并向低地址增长的，所以入栈时 SP 的值减小。
BP 基址指针。也是用于指向栈的某些位置，在调用函数时会使用到它。
AX 通用寄存器，我们的虚拟机中，它用于存放一条指令执行后的结果。
*/
int *pc, *bp, *sp, ax, cycle; // virtual machine registers
int *current_id,              // current parsed ID
    *symbols;                 // symbol table
int *idmain;                  // the `main` function

// instructions
enum { LEA ,IMM ,JMP ,CALL,JZ  ,JNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PUSH,
       OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
       OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT };

// tokens and classes (operators last and in precedence order)
enum {
  Num = 128, Fun, Sys, Glo, Loc, Id,
  Char, Else, Enum, If, Int, Return, Sizeof, While,
  Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};

/*
标识符与符号表
标识符（identifier）可以理解为变量名。对于语法分析而言，
我们并不关心一个变量具体叫什么名字，而只关心这个变量名代表的唯一标识。
例如 int a; 定义了变量 a，而之后的语句 a = 10，
我们需要知道这两个 a 指向的是同一个变量。

基于这个理由，词法分析器会把扫描到的标识符全都保存到一张表中，
遇到新的标识符就去查这张表，如果标识符已经存在，就返回它的唯一标识。
*/

struct identifier {
    int token;
    int hash;
    char * name;
    int class;
    int type;
    int value;
    int Bclass;
    int Btype;
    int Bvalue;
    /*
Symbol table:
----+-----+----+----+----+-----+-----+-----+------+------+----
 .. |token|hash|name|type|class|value|btype|bclass|bvalue| ..
----+-----+----+----+----+-----+-----+-----+------+------+----
    |<---       one single identifier                --->|
    */
}
/*
token：该标识符返回的标记，理论上所有的变量返回的标记都应该是 Id，
但实际上由于我们还将在符号表中加入关键字如 if, while 等，它们都有对应的标记。
hash：顾名思义，就是这个标识符的哈希值，用于标识符的快速比较。
name：存放标识符本身的字符串。
class：该标识符的类别，如数字，全局变量或局部变量等。
type：标识符的类型，即如果它是个变量，变量是 int 型、char 型还是指针型。
value：存放这个标识符的值，如标识符是函数，刚存放函数的地址。
BXXXX：C 语言中标识符可以是全局的也可以是局部的，当局部标识符的名字与全局标识符相同时，用作保存全局标识符的信息。
*/

// fields of identifier
enum {Token, Hash, Name, Type, Class, Value, BType, BClass, BValue, IdSize};

// types of variable/function
enum { CHAR, INT, PTR };

void next() {
    char *last_pos;
    int hash;
    while (token = *src) {
        ++src;
        // parse token here
        if (token == '\n') {
            ++line;
        }
        else if (token == '#') {
            // skip macro, because we will not support it
            while (*src != 0 && *src != '\n') {
                src++;
            }
        }
        else if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') || (token == '_')) {

            // parse identifier
            last_pos = src - 1;
            hash = token;
            while ((*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z') || (*src >= '0' && *src <= '9') || (*src == '_')) {
                hash = hash * 147 + *src;
                src++;
            }
            // look for existing identifier, linear search
            current_id = symbols;
            while (current_id[Token]) {
                if (current_id[Hash] == hash && !memcmp((char *)current_id[Name], last_pos, src - last_pos)) {
                    //found one, return
                    token = current_id[Token];
                    return;
                }
                current_id = current_id + IdSize;
            }
            // store new ID
            current_id[Name] = (int)last_pos;
            current_id[Hash] = hash;
            token = current_id[Token] = Id;
            return;
        }
        else if (token >= '0' && token <= '9') {
            // parse number, three kinds: dec(123) hex(0x123) oct(017)
            token_val = token - '0';
            if (token_val > 0) {
                // dec, starts with [1-9]
                while (*src >= '0' && *src <= '9') {
                    token_val = token_val*10 + *src++ - '0';
                }
            } else {
                // starts with number 0
                if (*src == 'x' || *src == 'X') {
                    //hex
                    token = *++src;
                    while ((token >= '0' && token <= '9') || (token >= 'a' && token <= 'f') || (token >= 'A' && token <= 'F')) {
                        token_val = token_val * 16 + (token & 15) + (token >= 'A' ? 9 : 0);
                        token = *++src;
                    }
                } else {
                    // oct
                    while (*src >= '0' && *src <= '7') {
                        token_val = token_val*8 + *src++ - '0';
                    }
                }
            }
            token = Num;
            return;
        }
        else if (token == '"' || token == '\'') {
            // parse string literal, currently, the only supported escape
            // character is '\n', store the string literal into data.
            last_pos = data;
            while (*src != 0 && *src != token) {
                token_val = *src++;
                if (token_val == '\\') {
                    // escape character
                    token_val = *src++;
                    if (token_val == 'n') {
                        token_val = '\n';
                    }
                }
                if (token == '"') {
                    *data++ = token_val;
                }
            }
            src++;
            // if it is a single character, return Num token
            if (token == '"') {
                token_val = (int)last_pos;
            } else {
                token = Num;
            }
            return;
        }
        else if (token == '/') {
            if (*src == '/') {
                // skip comments
                while (*src != 0 && *src != '\n') {
                    ++src;
                }
            } else {
                // divide operator
                token = Div;
                return;
            }
        }
/*
        这里我们要额外介绍 lookahead 的概念，即提前看多个字符。上述代码中我们看到，
        除了跳过注释，我们还可能返回除号 /(Div) 标记。
提前看字符的原理是：有一个或多个标记是以同样的字符开头的
（如本小节中的注释与除号），因此只凭当前的字符我们并无法确定具体应该解释成哪一个标记，
所以只能再向前查看字符，如本例需向前查看一个字符，若是 / 则说明是注释，反之则是除号。
我们之前说过，词法分析器本质上也是编译器，其实提前看字符的概念也存在于编译器，
只是这时就是提前看k个“标记”而不是“字符”了。平时听到的 LL(k) 中的 k 就是需要向前看的标记的个数了。
另外，我们用词法分析器将源码转换成标记流，能减小语法分析复杂度，
原因之一就是减少了语法分析器需要“向前看”的字符个数。
*/
        else if (token == '=') {
            // parse '==' and '='
            if (*src == '=') {
                src ++;
                token = Eq;
            } else {
                token = Assign;
            }
            return;
        }
        else if (token == '+') {
            // parse '+' and '++'
            if (*src == '+') {
                src ++;
                token = Inc;
            } else {
                token = Add;
            }
            return;
        }
        else if (token == '-') {
            // parse '-' and '--'
            if (*src == '-') {
                src ++;
                token = Dec;
            } else {
                token = Sub;
            }
            return;
        }
        else if (token == '!') {
            // parse '!='
            if (*src == '=') {
                src++;
                token = Ne;
            }
            return;
        }
        else if (token == '<') {
            // parse '<=', '<<' or '<'
            if (*src == '=') {
                src ++;
                token = Le;
            } else if (*src == '<') {
                src ++;
                token = Shl;
            } else {
                token = Lt;
            }
            return;
        }
        else if (token == '>') {
            // parse '>=', '>>' or '>'
            if (*src == '=') {
                src ++;
                token = Ge;
            } else if (*src == '>') {
                src ++;
                token = Shr;
            } else {
                token = Gt;
            }
            return;
        }
        else if (token == '|') {
            // parse '|' or '||'
            if (*src == '|') {
                src ++;
                token = Lor;
            } else {
                token = Or;
            }
            return;
        }
        else if (token == '&') {
            // parse '&' and '&&'
            if (*src == '&') {
                src ++;
                token = Lan;
            } else {
                token = And;
            }
            return;
        }
        else if (token == '^') {
            token = Xor;
            return;
        }
        else if (token == '%') {
            token = Mod;
            return;
        }
        else if (token == '*') {
            token = Mul;
            return;
        }
        else if (token == '[') {
            token = Brak;
            return;
        }
        else if (token == '?') {
            token = Cond;
            return;
        }
        else if (token == '~' || token == ';' || token == '{' || token == '}' || token == '(' || token == ')' || token == ']' || token == ',' || token == ':') {
            // directly return the character as token;
            return;
        }
    }
    return;
}

void expression(int level) {
    // do nothing
}

void program(){
	next();
	while(token>0){
        printf("token is: %3d('%c')\n", token, token);
		next();
	}
}
/*
MOV 是所有指令中最基础的一个，它用于将数据放进寄存器或内存地址，有点类似于 C 语言中的赋值语句。x86 的 MOV 指令有两个参数，分别是源地址和目标地址：MOV dest, source （Intel 风格），表示将 source 的内容放在 dest 中，它们可以是一个数、寄存器或是一个内存地址。

一方面，我们的虚拟机只有一个寄存器，另一方面，识别这些参数的类型（是数据还是地址）是比较困难的，因此我们将 MOV 指令拆分成 5 个指令，这些指令只接受一个参数，如下：

IMM <num> 将 <num> 放入寄存器 ax 中。
LC 将对应地址中的字符载入 ax 中，要求 ax 中存放地址。
LI 将对应地址中的整数载入 ax 中，要求 ax 中存放地址。
SC 将 ax 中的数据作为字符存放入地址中，要求栈顶存放地址。
SI 将 ax 中的数据作为整数存放入地址中，要求栈顶存放地址。

PUSH
在 x86 中，PUSH 的作用是将值或寄存器，而在我们的虚拟机中，
它的作用是将 ax 的值放入栈中。
这样做的主要原因是为了简化虚拟机的实现，并且我们也只有一个寄存器 ax 。

JMP
JMP <addr> 是跳转指令，
无条件地将当前的 PC 寄存器设置为指定的 <addr>

JZ/JNZ

为了实现 if 语句，我们需要条件判断相关的指令。
这里我们只实现两个最简单的条件判断，即结果（ax）为零或不为零情况下的跳转。

子函数调用

这是汇编中最难理解的部分，所以合在一起说，要引入的命令有 CALL, ENT, ADJ 及 LEV。

首先我们介绍 CALL <addr> 与 RET 指令，CALL 的作用是跳转到地址为 <addr> 的子函数，RET 则用于从子函数中返回。

为什么不能直接使用 JMP 指令呢？原因是当我们从子函数中返回时，
程序需要回到跳转之前的地方继续运行，这就需要事先将这个位置信息存储起来。反过来，
子函数要返回时，就需要获取并恢复这个信息。因此实际中我们将 PC 保存在栈中。

ENT

ENT <size> 指的是 enter，用于实现 ‘make new call frame’ 的功能，
即保存当前的栈指针，同时在栈上保留一定的空间，用以存放局部变量。

ADJ

ADJ <size> 用于实现 ‘remove arguments from frame’。
在将调用子函数时压入栈中的数据清除，本质上是因为我们的 ADD 指令功能有限。

LEV

本质上这个指令并不是必需的，只是我们的指令集中并没有 POP 指令。
并且三条指令写来比较麻烦且浪费空间，所以用一个指令代替。对应的汇编指令为：
; restore old call frame
mov     esp, ebp
pop     ebp
; return
ret

LEA

上面的一些指令解决了调用帧的问题，但还有一个问题是如何在子函数中获得传入的参数。这里我们首先要了解的是当参数调用时，
栈中的调用帧是什么样的。我们依旧用上面的例子（只是现在用“顺序”调用参数）：

sub_function(arg1, arg2, arg3);
|    ....       | high address
+---------------+
| arg: 1        |    new_bp + 4
+---------------+
| arg: 2        |    new_bp + 3
+---------------+
| arg: 3        |    new_bp + 2
+---------------+
|return address |    new_bp + 1
+---------------+
| old BP        | <- new BP
+---------------+
| local var 1   |    new_bp - 1
+---------------+
| local var 2   |    new_bp - 2
+---------------+
|    ....       |  low address

所以为了获取第一个参数，我们需要得到 new_bp + 4，
但就如上面的说，我们的 ADD 指令无法操作除 ax 外的寄存器，所以我们提供了一个新的指令：LEA <offset>

运算符指令
我们为 C 语言中支持的运算符都提供对应汇编指令。
每个运算符都是二元的，即有两个参数，第一个参数放在栈顶，第二个参数放在 ax 中。
这个顺序要特别注意。因为像 -，/ 之类的运算符是与参数顺序有关的。
计算后会将栈顶的参数退栈，结果存放在寄存器 ax 中。因此计算结束后，
两个参数都无法取得了（汇编的意义上，存在内存地址上就另当别论）。
*/
int eval(){
	int op, *tmp;
    while (1) {
        op = *pc++;
        if (op == IMM)       {ax = *pc++;}                                     // load immediate value to ax
        else if (op == LC)   {ax = *(char *)ax;}                               // load character to ax, address in ax
        else if (op == LI)   {ax = *(int *)ax;}                                // load integer to ax, address in ax
        else if (op == SC)   {ax = *(char *)*sp++ = ax;}                       // save character to address, value in ax, address on stack
        else if (op == SI)   {*(int *)*sp++ = ax;}   // *sp++ == POP           // save integer to address, value in ax, address on stack
        else if (op == PUSH) {*--sp = ax;}                                     // push the value of ax onto the stack
        else if (op == JMP)  {pc = (int *)*pc;}                                // jump to the address
        else if (op == JZ)   {pc = ax ? pc + 1 : (int *)*pc;}                   // jump if ax is zero
        else if (op == JNZ)  {pc = ax ? (int *)*pc : pc + 1;}                   // jump if ax is zero
        else if (op == CALL) {*--sp = (int)(pc+1); pc = (int *)*pc;}           // call subroutine
        //else if (op == RET)  {pc = (int *)*sp++;}                              // return from subroutine;
        else if (op == ENT)  {*--sp = (int)bp; bp = sp; sp = sp - *pc++;}      // make new stack frame
        else if (op == ADJ)  {sp = sp + *pc++;}                                // add esp, <size>
        else if (op == LEV)  {sp = bp; bp = (int *)*sp++; pc = (int *)*sp++;}  // restore call frame and PC
        else if (op == ENT)  {*--sp = (int)bp; bp = sp; sp = sp - *pc++;}      // make new stack frame
        else if (op == ADJ)  {sp = sp + *pc++;}                                // add esp, <size>
        else if (op == LEV)  {sp = bp; bp = (int *)*sp++; pc = (int *)*sp++;}  // restore call frame and PC
        else if (op == LEA)  {ax = (int)(bp + *pc++);}                         // load address for arguments.

		else if (op == OR)  ax = *sp++ | ax;
		else if (op == XOR) ax = *sp++ ^ ax;
		else if (op == AND) ax = *sp++ & ax;
		else if (op == EQ)  ax = *sp++ == ax;
		else if (op == NE)  ax = *sp++ != ax;
		else if (op == LT)  ax = *sp++ < ax;
		else if (op == LE)  ax = *sp++ <= ax;
		else if (op == GT)  ax = *sp++ >  ax;
		else if (op == GE)  ax = *sp++ >= ax;
		else if (op == SHL) ax = *sp++ << ax;
		else if (op == SHR) ax = *sp++ >> ax;
		else if (op == ADD) ax = *sp++ + ax;
		else if (op == SUB) ax = *sp++ - ax;
		else if (op == MUL) ax = *sp++ * ax;
		else if (op == DIV) ax = *sp++ / ax;
		else if (op == MOD) ax = *sp++ % ax;


        else if (op == EXIT) { printf("exit(%d)", *sp); return *sp;}
        else if (op == OPEN) { ax = open((char *)sp[1], sp[0]); }
        else if (op == CLOS) { ax = close(*sp);}
        else if (op == READ) { ax = read(sp[2], (char *)sp[1], *sp); }
        else if (op == PRTF) { tmp = sp + pc[1]; ax = printf((char *)tmp[-1], tmp[-2], tmp[-3], tmp[-4], tmp[-5], tmp[-6]); }
        else if (op == MALC) { ax = (int)malloc(*sp);}
        else if (op == MSET) { ax = (int)memset((char *)sp[2], sp[1], *sp);}
        else if (op == MCMP) { ax = memcmp((char *)sp[2], (char *)sp[1], *sp);}
        else {
            printf("unknown instruction:%d\n", op);
            return -1;
        }
    }
    return 0;
}

int main(int argc,char **argv)
{
	int i,fd;

	argc--;
	argv++;

	poolsize = 256 * 1024; // arbitrary size
    line = 1;
    if ((fd = open(*argv, 0)) < 0) {
        printf("could not open(%s)\n", *argv);
        return -1;
    }

    // allocate memory for virtual machine
    if (!(text = old_text = malloc(poolsize))) {
        printf("could not malloc(%d) for text area\n", poolsize);
        return -1;
    }
    if (!(data = malloc(poolsize))) {
        printf("could not malloc(%d) for data area\n", poolsize);
        return -1;
    }
    if (!(stack = malloc(poolsize))) {
        printf("could not malloc(%d) for stack area\n", poolsize);
        return -1;
    }
    if (!(symbols = malloc(poolsize))) {
        printf("could not malloc(%d) for symbol table\n", poolsize);
        return -1;
    }

    memset(text, 0, poolsize);
    memset(data, 0, poolsize);
    memset(stack, 0, poolsize);
    memset(symbols, 0, poolsize);
    bp = sp = (int *)((int)stack + poolsize);
    ax = 0;

    src = "char else enum if int return sizeof while "
          "open read close printf malloc memset memcmp exit void main";
     // add keywords to symbol table
    i = Char;
    while (i <= While) {
        next();
        current_id[Token] = i++;
    }
    // add library to symbol table
    i = OPEN;
    while (i <= EXIT) {
        next();
        current_id[Class] = Sys;
        current_id[Type] = INT;
        current_id[Value] = i++;
    }
    next(); current_id[Token] = Char; // handle void type
    next(); idmain = current_id; // keep track of main


    // read the source file
    if ((fd = open(*argv, 0)) < 0) {
        printf("could not open(%s)\n", *argv);
        return -1;
    }

    if (!(src = old_src = malloc(poolsize))) {
        printf("could not malloc(%d) for source area\n", poolsize);
        return -1;
    }
    // read the source file
    if ((i = read(fd, src, poolsize-1)) <= 0) {
        printf("read() returned %d\n", i);
        return -1;
    }
    src[i] = 0; // add EOF character
    close(fd);

    program();
    return eval();
}