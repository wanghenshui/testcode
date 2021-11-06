#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <numeric>
struct count_odd{
    static size_t count;
    void operator()(const int & i)
    {
        if(i%2==1)
            count++;
    }
};
size_t count_odd::count = 0;
struct ok_t{
    ok_t(const int& a):t(a){}
    int t;
    bool ok() const {return t!=0;}
};

struct count_odd2{
    int operator()(const int& init,const ok_t& last)
    {
        return last.ok()?init+1:init;
    }
};


int main()
{
    std::vector<int> a ={1,2,3,4,5};
    std::for_each(a.begin(),a.end(),count_odd());
    std::cout << "Hello, Wandbox!" <<count_odd::count<< std::endl;
    std::vector<int> b ={1,2,3,4,5};
    std::for_each(b.begin(),b.end(),count_odd());
    std::cout << "Hello, Wandbox!" <<count_odd::count<< std::endl;
    std::vector<ok_t> c= {ok_t(1),ok_t(0),ok_t(0),ok_t(0),ok_t(5)};
    size_t d = std::accumulate(c.begin(),c.end(),0,count_odd2());
    std::cout << "Hello, Wandbox!" <<d<< std::endl;
}