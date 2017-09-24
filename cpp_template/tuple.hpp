/*------------------------------------------------------------------

	tuple impl

-------------------------------------------------------------------*/
struct null_t{};

//com duo

template <typename T1, typename T2>
struct duo
{
	typedef T1 type1;
	typedef T2 type2;
	enum{N=2};

	T1 _v1;
	T2 _v2;
	duo() :_v1(),_v2(){}
	duo(T1 const& a, T2 const& b) :_v1(a), _v2(b)	{}

	template<typename U1, typename U2>
	duo(duo<U1, U2> const & d) : _v1(d.v1()), _v2(d.v2())	{}
	
	template<typename U1,typename U2>
	duo<T1, T2>& operator =(duo<U1, U2> const & u)
	{
		_v1 = u._v1;
		_v2 = u._v2;
		return *this;
	}

	T1& v1() {	return _v1;}
	T1 const & v1() const { return _v1;}
	T2& v2() {	return _v2;}
	T2 const & v2() const { return _v2; }

	template<typename U1, typename U2> inline
	bool operator == (duo<U1, U2> const & t)
	{
		return t.v1() == this->v1() && t.v2() == this->v2();
	}

	template<typename U1,typename U2> inline
	bool operator != (duo<U1, U2> const & t)
	{
		return !(t == *this);
	}
	template<typename U1,typename U2> inline
	duo<U1, U2> make_duo(U1 const & a, U2 const & b)
	{
		return duo<U1, U2>(a, b);
	}
};

//recru duo
template<typename A, typename B, typename C>
struct duo<A, duo<B, C> >
{
	typedef A T1;
	typedef duo<B, C> T2;
	enum { N = duo<B, C>::N + 1 };
//same
	T1 _v1;
	T2 _v2;
	duo() :_v1(), _v2(){}
	duo(T1 const& a, T2 const& b) :_v1(a), _v2(b){}

	template<typename U1, typename U2>
	duo(duo<U1, U2> const & d) : _v1(d.v1()), _v2(d.v2()){}

	template<typename U1, typename U2>
	duo<T1, T2>& operator =(duo<U1, U2> const & u)
	{
		_v1 = u._v1;
		_v2 = u._v2;
		return *this;
	}

	T1& v1() { return _v1; }
	T1 const & v1() const { return _v1; }
	T2& v2() { return _v2; }
	T2 const & v2() const { return _v2; }

	template<typename T1, typename T2> inline
		bool operator == (duo<T1, T2> const & t)
	{
		return t.v1() == this->v1() && t.v2() == this->v2();
	}

	template<typename T1, typename T2> inline
		bool operator != (duo<T1, T2> const & t)
	{
		return !(t == *this);
	}
	template<typename T1, typename T2> inline
		duo<T1, T2> make_duo(T1 const & a, T2 const & b)
	{
		return duo<T1, T2>(a, b);
	}
};

template<typename A>
struct duo<A,void>
{
	typedef A T1;
	typedef void T2;
	enum {N=1};
	T1 _v1;
	duo() :_v1() {}
	duo(T1 const &a) :_v1(a) {}
	T1 & v1() { return _v1; }
	T1 const & v1() const { return _v1; }
	void v2() {}
	void v2() const {}


	template<typename U>
	duo<T1, void>& operator =(duo<U, void> const & u)
	{
		_v1 = u._v1;
		return *this;
	}

	template<typename T1> inline
	bool operator == (duo<T1, void> const & t)
	{
		return t.v1() == this->v1() ;
	}

	template<typename T1> inline
	bool operator != (duo<T1, void> const & t)
	{
		return !(t == *this);
	}
	template<typename T1> inline
	duo<T1,void> make_duo(T1 const & a)
	{
		return duo(a);
	}
};

//duo type deduction 
template <int N, typename T>
struct duo_t
{
	typedef void result_t;
};

template<typename A, typename B>
struct duo_t<1,duo<A,B> >
{
	typedef A result_t;
};

template<typename A, typename B>
struct duo_t<2, duo<A, B> >
{
	typedef B result_t;
};

template<int N,typename A, typename B, typename C>
struct duo_t<N,duo<A, duo<B,C> > >
{
	typedef typename duo_t<N - 1, duo_t<B, C> >::result_t result_t;
};

template<typename A, typename B, typename C>
struct duo_t<1, duo<A, duo<B, C> > >
{
	typedef A result_t;
};

template<typename A, typename B, typename C>
struct duo_t<2, duo<A, duo<B, C> > >
{
	typedef B result_t;
};
//tool: type operator
template<typename T>
struct type_op
{
	typedef T arg_t;
	typedef T base_t;
	typedef T const const_t;
	typedef T& ref_t;
	typedef T& ref_base_t;
	typedef T const & ref_const_t;
};

template<typename T>
struct type_op<T const>
{
	typedef T const arg_t;
	typedef T base_t;
	typedef T const const_t;
	typedef T const & ref_t;
	typedef T & ref_base_t;
	typedef T const & ref_const_t;
};

template<typename T>
struct type_op<T&>
{
	typedef T & arg_t;
	typedef typename type_op<T>::base_t bast_t;
	typedef T const const_t;
	typedef T &  ref_t;
	typedef typename type_op<T>::base_t & ref_base_t;
	typedef T const & ref_const_t;
};

template<>
struct type_op<void>
{
	typedef void arg_t;
	typedef void base_t;
	typedef void const const_t;
	typedef void ref_t;
	typedef void ref_base_t;
	typedef void ref_const_t;
};
//duo value deduction

template<int N, typename T>
struct duo_v
{
	static void get(T&) {}
	static void get(T const &) {}
};

template<typename A,typename B>
struct duo_v<1, duo<A, B> >
{
	static A& get(duo<A, B> &d)
	{
		return d.v1();
	}
	static A const& get(duo<A, B> const &d)
	{
		return d.v1();
	}
};

template<typename A,typename B>
struct duo_v<2,duo<A,B> >
{
	static B& get(duo<A, B> &d) {
		return d.v2();
	}
	static B const & get(duo<A, B> &d) const {
		return d.v2();
	}
};

template<int N,typename A,typename B, typename C>
struct duo_v<N, duo<A, duo<B, C> > > {
	static 
	typename type_op<typename duo_t<N-1,duo<B,C> >::result_t>::ref_t 
	get(duo<A, duo<B, C> > &d) {
		return duo_v<N - 1, duo<B, C> >::get(d.v2());
	}
};

template<typename A, typename B, typename C>
struct duo_v<1, duo<A, duo<B, C> > >
{
	static A& get(duo<A, duo<B, C> > &d){
		return d.v1();
	}
	static A const & get(duo<A, duo<B, C> > &d) const {
		return d.v1();
	}
};

template<typename A, typename B, typename C>
struct duo_v<2, duo<A, duo<B, C> > >
{
	static A& get(duo<A, duo<B, C> > &d) {
		return d.v2();
	}
	static A const & get(duo<A, duo<B, C> > &d) const {
		return d.v2();
	}
};
namespace rm {
template<typename P1, 	typename P2=null_t,	typename P3=null_t,	typename P4=null_t,	typename P5=null_t>
struct tuple:public duo<P1,typename tuple<P2,P3,P4,P5,null_t>::base_t>
{
	typedef duo<P1, typename tuple<P2, P3, P4, P5, null_t>::base_t> bast_t;

	tuple() {}
	tuple(type_op<P1>::ref_const_t a1,
		type_op<P2>::ref_const_t a2,
		type_op<P3>::ref_const_t a3=null_t(),
		type_op<P4>::ref_const_t a4=null_t(),
		type_op<P5>::ref_const_t a5=null_t())
		:bast_t(a1, tuple<P2, P3, P4, P5, null_t>(a2, a3, a4, a5)) {}
};

template<typename T1> inline
tuple<T1> make_tuple(T1 const&a1) {
	return tuple<T1>(a1);
}
template<typename T1, typename T2> inline
tuple<T1,T2> make_tuple(T1 const&a1,T2 const &a2) {
	return tuple<T1,T2>(a1,a2);
}
template<typename T1, typename T2,typename T3> inline
tuple<T1, T2,T3> make_tuple(T1 const&a1, T2 const &a2,T3 const &a3) {
	return tuple<T1, T2,T3>(a1, a2,a3);
}
template<typename T1, typename T2, typename T3,typename T4> inline
tuple<T1, T2, T3,T4> make_tuple(T1 const&a1, T2 const &a2, T3 const &a3,T4 const& a4) {
	return tuple<T1, T2, T3,T4>(a1, a2, a3,a4);
}
template<typename T1, typename T2, typename T3, typename T4,typename T5> inline
tuple<T1, T2, T3, T4,T5> make_tuple(T1 const&a1, T2 const &a2, T3 const &a3, T4 const& a4,T5 const& a5) {
	return tuple<T1, T2, T3, T4,T5>(a1, a2, a3, a4,a5);
}
}//end of namespace rm