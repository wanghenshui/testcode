#ifndef __EXCEPT__CIAI__
#define __EXCEPT__CIAI__
#include <setjmp>

#define T EXCEPT_T
typedef struct T
{
    const char *reason;// just descripe is 
} T;

enum 
{
	except_entered=0,
    except_raised,
	except_handled,
	except_finalized
};

typedef struct except_frame EXCEPT_FRAME;

struct except_frame
{
    except_frame *prev;
    jmp_buf env;
    const char *file;
    int line;
    const T *exception;
};

extern except_frame EXCEPT_STACK;

#define  RAISE(e) EXCEPT_RAISE(&(e),__FILE__,__LINE__ )
#define  RERAISE  EXCEPT_RAISE(EXCEPT_FRAME.exception,EXCEPT_FRAME.file,EXCEPT_FRAME.line)
#define TRY do{\
	volatile int except_flag;\
	except_frame EXCEPT_FRAME;\
	/*push */\
	EXCEPT_FRAME.prev = EXCEPT_STACK; \
	EXCEPT_STACK = &EXCEPT_FRAME;\
	except_flag = setjmp(EXCEPT_FRAME.enc);\
	if (except_flag == except_entered ){
	do
	{
	}
	}
}
void EXCEPT_RAISE(const T * e, const char *file,int line);


#undef T
#endif
