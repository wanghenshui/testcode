#ifndef __SIZEOF_CONSTRAINTS__
#define 

template<typename T>
class larger_than
{
	T dummy_[2];
};

typedef char no_type;
typedef larger_than<no_type> yes_type;

template<size_t N>
struct fixed_size
{
	typedef char type[N];
};
//fixed_size<N>::type == N
#endif
