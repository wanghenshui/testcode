#ifndef __COMPILE_TIME_CHECKER__
#define __COMPILE_TIME_CHECKER__

template<bool> struct compile_time_checker
{
	compile_time_checker(...);
};

template<> struct compile_time_checker<false>{};

#define STATIC_CHECK(expr,msg)\
{\
	class ERROR_##msg{};\
	(void)sizeof(compile_time_checker<(expr)>(ERROR_##msg()));\
}
template<typename TO, typename FROM>
TO safe_reinterpret_cast(FROM from)
{
	STATIC_CHECK(sizeof(FROM)<=sizeof(TO),Destination_Type_Too_Narrow);
	return reinterpret_cast<TO>(from);
}
#endif

