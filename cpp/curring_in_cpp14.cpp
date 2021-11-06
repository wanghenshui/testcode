#include <iostream>
using std::cout;
template<typename F,typename... Args>
auto currying(F f,Args... args)
{
    return [=](auto... rest)
    {
        return f(args... ,rest...);
    };
}

int x2y(int x,int y)
{
    return x*x + y;
}




int main()
{
    auto x = currying(x2y,2);
    cout<<x(4)<<"\n";
}