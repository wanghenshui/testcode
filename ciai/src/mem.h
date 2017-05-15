#ifndef __MEM__CIAI__
#define __MEM__CIAI__
//#include "except.h"
//extern const EXCEPT_T mem_failed;

extern void *__cii_mem_alloc(long nbytes, const char *file, int line);
extern void *__cii_mem_calloc(long count, long nbytes,const char *file,int line);
extern void  __cii_mem_free(void *ptr,const char *file,int line);
extern void *__cii_mem_resize(void *ptr, long nbytes,const char *file,int line);

#define __CII_ALLOC(nbytes) 		__cii_mem_calloc((nbytes),__FILE__,__LINE__)
#define __CII_CALLOC(count,nbytes)	__cii_mem_alloc((count),(nbytes),__FILE__,__LINE__)
#define __CII_FREE(ptr)		 ((void)__cii_mem_free((ptr),__FILE__,__LINE__))
#define __CII_RESIZE(ptr,nbytes) ((ptr) = __cii_mem_resize((ptr),(nbytes,__FILE__,__LINE__)))

#define __CII_NEW(p) ((p) = __CII_ALLOC((long)sizeof *(p)))
#define __CII_NEW0(p) ((p = __CII_CALLOC(1,(long)sizeof *(p)))



#endif
