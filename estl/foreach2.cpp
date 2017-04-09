#include "algostuff.hpp"

template<class T>
class add_value
{
    private: 
	    T value2add;
    public:
	     add_value(const T& v):value2add(v){    }

	     void operator()(T& elem) const{	elem+= value2add;}
};


int main()
{
    std::vector<int> coll;
    INSERT_ELEMENTS(coll,1,9);

    std::for_each(coll.begin(),coll.end(),add_value<int>(10));
    PRINT_ELEMENTS(coll);


    std::for_each(coll.begin(),coll.end(),add_value<int>(*coll.begin()));
    PRINT_ELEMENTS(coll);
}

