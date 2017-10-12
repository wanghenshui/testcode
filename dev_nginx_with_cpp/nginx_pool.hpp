#include "nginx_exception.hpp"
#include "nginx_wrapper.hpp"

class NgxPool /*final*/ :public NgxWrapper<ngx_pool_t>
{
public:
	typedef NgxWrapper<ngx_pool_t> super_type;
	typedef NgxPool this_type;

	NgxPool(ngx_pool_t* p):super_type(p){}
	~NgxPool() = default;

	//ngx_pool_t在很多结构中是成员变量pool
	template<typename T> NgxPool(T* x):NgxPool(x->pool){}

	template<typename T, bool no_exception = false>
	T * palloc() const
	{
		auto p = ngx_pcalloc(get(),sizeof(T));
		if(!p)
		{
			if(no_exception)
			{
				return nullptr;
			}
			NgxException::raise();
		}
		assert(p);
		return new(p) T();
	}

	template<typename T>
	T* alloc() const
	{
		return palloc<T,false>();
	}

	template<typename T>
	T* alloc_noexcept() const
	{
		return palloc<T,true>();
	}

	template<typename T>
	T* nalloc(size_t n) const
	{
		auto p = ngx_pcalloc(get(),n);
		NgxException::require(p);
		return reinterpret_cast<T*>(*p);
	}

	template<typename T, typename ...Args>
	T* construct(const Args& ...args)
	{
		auto p = ngx_pcalloc(get(),sizeof(T));
		NgxException::require(p);
		return new(p) T(args ...)
	}

	//ngx_pool_cleanup_t

	template<typename F, typename T>
	ngx_pool_cleanup_t* cleanup(F func, T* data, size_t size=0) const
	{
		auto p = ngx_pool_cleanup_add(get(),size);
		NgxException::require(p);
		p->handler = func;

		if(data)
			p->data = data;
		return p;
	}

	template<typename T>
	static void destory(void* p)
	{
		(reinterpret_cast<T*>(p))->~(T);
	}

	template<typename T>
	void cleanup(T* data) const
	{
		cleanup(&this_type::destory<T>,data);//this
	}
}

template<typename T>
class NgxAlloctor:public NgxWrapper<ngx_pool_t>
{
public:
	typedef NgxWrapper<ngx_pool_t> super_type;
	typedef NgxAlloctor this_type;
	typedef size_t size_type;
	typedef T* pointer;
	typedef T value_type;

	NgxAlloctor(ngx_pool_t* p):super_type(p){}
	~NgxAlloctor()=default;

	pointer allocate(size_type n)
	{
		return reinterpret_cast<pointer>(ngx_pcalloc(get(),n*sizeof(T)));
	}

	void deallocate(pointer prt,size_type n)
	{
		boost::ignore_unused(n);
		ngx_pfree(get(),ptr);
	}
}