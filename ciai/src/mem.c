#include <stdlib.h>
#include <stddef.h>
//#include <assert.h>
//except.h
#include "mem.h"

void *__cii_mem_alloc(long nbytes,const char *file, int line);
{
    void *ptr;
    assert(nbytes>0);
    ptr =  malloc(nbytes);
    if(ptr == NULL)
	;    //raise memlloc failed
    return ptr;
}
