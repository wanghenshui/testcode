#include "algostuff.hpp"

void print(int elem)
{
    std::cout<<elem<<' ';
}

int main()
{
    std::vector<int> coll;
    INSERT_ELEMENTS(coll,1,9);

    std::for_each(coll.begin(),coll.end(),print);

    std::cout<<std::endl;
}

