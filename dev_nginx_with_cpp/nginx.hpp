extern "C"{
#include <ngx_http.h>
}

#include <assert>
#include <boost/core/ignore_unused.hpp>


class NgxUnsetValue //final
{
public:
	static const NgxUnsetValue& get()
	{
		static NgxUnsetValue const v = {};
		return v;
	}
	template<typename T> operator T() const
	{
		return static_cast<T>(-1);
	}

	template <typename T> operator T* () const
	{
		return reinterpret_cast<T*>(-1);
	}
}

class NgxValue
{
public:
	NgxValue() = default;
	~NgxValue() = default;

	template<typename T> static bool invalid(const T& v)
	{
		return v == static_cast<T>(NgxUnsetValue::get());
	}

	template<typename T, typename U> static void init(T& x, const U& v)
	{
		if(invalid(x))	
			x=v;
	}

	template<typename T, typename U, typename V>
	static void merge(T& t, const U& u,const V& v)
	{
		if(invalid(t))
			t=invalid(u)?v:u;
	}

	template<typename T, typename ... Args>
	static void unset(T& v, Args& ...args)
	{
		v = NgxUnsetValue::get();
		unset(args...);
	}

	static void unset(){}//end recrusive deduction
	//usage: NgxValue::unset(a,b,c,d,e,f)
}