#ifndef __STATIC_VALUE__
#define __STATIC_VALUE__

template<typename T, T VALUE>
struct static_parameter{};

template<typename T, T VALUE>
struct static_value:static_parameter<T,VALUE>
{
	static const T value = VALUE;

	operator T () const
	{
		return VALUE;
	}
	static_value(int =0)
	{}
};

#endif
