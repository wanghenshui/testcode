#define IMPL_STR(R)  #R  
#define _STR(R)  IMPL_STR(R)
#define MSG _STR(THIS_FUNCTION_IS_DEPRECATED_)
#define DEPRECATED_MESSAGE_IMPL "%s",__FUNCTION__ 
#define DEPRECATED_MESSAGE MSG DEPRECATED_MESSAGE_IMPL


#include <cstdio>
void f()
{
	printf(DEPRECATED_MESSAGE);	
}
int main()
{
	f();	
}