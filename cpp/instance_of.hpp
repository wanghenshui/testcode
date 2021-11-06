#ifndef __INSTANCE_OF
#define __INSTANCE_OF
template <typename T>
struct instance_of
{
	typedef T type;
	instance_of(int =0){}
};

//usage: const instance_of<int> g = instance_of<int>()

#endif
