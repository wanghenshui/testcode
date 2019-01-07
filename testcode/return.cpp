#include <iostream>

using namespace std;

void g(int a,int b, int c){
cout<< a<<"\n"<<b<<"\n"<<c<<"\n"<<endl;
}

void f(int a,int b){
    return g(a,b,3);
}

int main()
{
f(1,2);
}