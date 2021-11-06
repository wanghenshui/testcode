// 1 (a)
#include <stdio.h>


void wordCount(char *str)  
{  
    int count = 0, flag = 0;  
    char *p = str;  
    while (*p != '\0'){  
        while (*p == 32){  
            if (*(p + 1) == 0){/*当空白的下一位是结束符时，意味着最后一个单词后面是空格，那么就做一个标记，让下面的程序看到*/  
                flag = 1;  
            }  
            ++p;  
        }  
        while (*p != 0 && *p != 32){  
            ++p;  
        }  
        if (!flag){/*根据上面的标记，知道这个时候不是单词结束了，而是句子要结束了，不再统计单词个数了*/  
            ++count;  
        }  
    }  
    printf("Word:%d\n", count);  
    p = str;  
    flag = 0;  
    while (*p != 0){  
        while (*p == 32){  
            if (*(p + 1) == 0){/*和上面的一样*/  
                flag = 1;  
            }  
            ++p;  
        }  
        while (*p != 0 && *p != 32){  
            putchar(*p);  
            ++p;  
        }  
        if (!flag){  
            putchar(10);  
        }  
    }  
  
}
int main()
{	
	char *pch = "she sells sea shells by the seashore";
	printf("%s\n",pch);
	wordCount(pch);
	
	return 0;
}