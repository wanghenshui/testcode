#include <iostream>
using namespace std;

const int defaultsize = 100;

template<typename T>
class Array{
	T *element;
	int ArraySize;
public:
	Array(int size=defaultsize);
	Array(const Array<T> & a);
	~Array(){delete [] element;}
	Array<T> & operator = (const Array<T>& rhs);
	T& operator [] (int i);
	int length() const {return ArraySize;}
	void resize(int size);
};

template<typename T>
Array<T>& Array<T>::operator = (const Array<T> & rhs)
{
	if(ArraySize!=rhs.ArraySize)
	{
		delete [] element;
		element = new T[rhs.ArraySize];
		if(element == nullptr)
		{
			ArraySize = 0;
			cerr << "alloc error"<<endl;
			exit(1);//or throw bad_alloc?
		}
		ArraySize = rhs.ArraySize;
	}
	T * destptr = element;
	T * srcptr = rhs.element;
	int n = rhs.ArraySize;
	while(n--)
			*destptr++ = *srcptr++;
	return *this;
}

template <typename T>
Array<T>::Array(int size)
{
	if(size<=0)
	{
		ArraySize = 0;
		cerr<< "ctor size error"<<endl;
		return;
	}

	element = new T[size];
	if(element == nullptr)
	{
		ArraySize = 0;
		cerr << "alloc error"<<endl;
		exit(1);
	}
	ArraySize = size;
}


template<typename T>
Array<T>::Array(const Array<T> & a)
{
	int n = a.ArraySize;
	ArraySize = n;
	//static_assert(element == nullptr);
	element = new T[n];
	T * destptr = element;
	T * srcptr = rhs.element;
	while(n--)	*destptr++ = *srcptr++;
}

template<typename T>
T& Array<T>::operator [](int i)
{
//assert i
	return	element[i];
}

template<typename T>
void Array<T>::resize(int size)
{
	if(size >0 && size!= ArraySize)
	{
		T * newarray = new T[size];
		int n =  (sz<=ArraySize)?size:ArraySize;

		T * destptr = element;
		T * srcptr = newarray;
		while(n--)	*destptr++ = *srcptr++;
		delete [] element;
		element = newarray;
		ArraySize = size;
	}
}
