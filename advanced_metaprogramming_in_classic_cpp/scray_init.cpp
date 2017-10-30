template<typename X,typename T>
struct base_inner
{
	template<typename T2>
	base_inner& operator-(const base_inner<X,T2>&){}
};

template<typename T>
struct outer
{
	template<typename X>
	struct inner:public base_inner<X,T>
	{
		template<typename ANOTHER_T>
		inner& operator=(const base_inner<X,ANOTHER_T>& that)
		{
			static_cast<base_inner<X,T>&>(*this) = that;
			return *this;
		}
	};
};

template<>
struct outer<int>
{
	template<typename X>
	struct inner:public base_inner<X,int>
	{
		template<typename ANOTHER_T>
		inner& operator=(const base_inner<X,ANOTHER_T>& that)
		{
			static_cast<base_inner<X,int>&>(*this) = that;
			return *this;
		}
	};
};

int main()
{
	outer<double>::inner<void> i1;
	outer<int>::inner<void> i2;
	i1=i2;
}
