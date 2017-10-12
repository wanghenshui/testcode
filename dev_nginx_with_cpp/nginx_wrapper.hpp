#include <boost/type_traits.hpp>

template <typename T> class NgxWrapper
{
public:
	typedef typename boost::remove_pointer<T>::type wrapped_type;
	typedef wrapped_type* pointer_type;
	typedef wrapped_type& reference_type;
	pointer_type get() const
	{
		return m_ptr;
	}

	operator bool () const
	{
		return get();
	}

	operator pointer_type () const
	{
		return get();
	}

	pointer_type operator ->() const
	{
		return get();
	}

private:
	pointer_type m_ptr = std::nullptr;
protected:
	NgxWrapper(pointer_type p):m_ptr(p){}
	NgxWrapper(reference_type r):m_ptr(&r){}
	~NgxWrapper() = default;
}