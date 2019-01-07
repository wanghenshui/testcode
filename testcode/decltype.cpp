#include <iostream>
#include <type_traits>
#include <typeinfo>
using namespace std;


struct S
{
    int iarr[10];
    int i;
    std::string sarr[10];
    std::string s;
};

S get() { return S{}; }

std::string sarr[10];

template<class T>
void foo(T&& v) {}
/*
decltype

a) 若 expression 的值类别为亡值，则 decltype 产生 T&& ；
b) 若 expression 的值类别为左值，则 decltype 产生 T& ；
c) 若 expression 的值类别为纯右值，则 decltype 产生 T 。
若 expression 是返回类类型纯右值的函数调用，或是右运算数为这种函数调用的逗号表达式，则不对该纯右值引入临时量。

(C++17 前)
若 expression 是（可有括号的）立即调用以外的 (C++20 起)纯右值，则不从该纯右值实质化临时对象。

(C++17 起)
类型不需要完整或拥有可用的析构函数，而且能为抽象。此规则不应用到子表达式： decltype(f(g())) 中， g() 必须有完整类型，但 f() 不必。

*/
int main()
{
    cout<<is_rvalue_reference_v <decltype(get().iarr[0])><<endl;//true ->xvalue
    cout<<is_rvalue_reference_v <decltype(get().i)><<endl;
    cout<<is_rvalue_reference_v <decltype(get().sarr[0])><<endl;//true ->xvalue
    cout<<is_rvalue_reference_v <decltype(get().s)><<endl;
    cout<<is_rvalue_reference_v <decltype(get())><<endl;
    cout<<is_rvalue_reference_v <decltype(get().iarr)><<endl;
    cout<<is_rvalue_reference_v <decltype(get().sarr)><<endl;
cout<<endl;
    cout<<is_lvalue_reference_v <decltype(get().iarr[0])><<endl;
    cout<<is_lvalue_reference_v <decltype(get().i)><<endl;
    cout<<is_lvalue_reference_v <decltype(get().sarr[0])><<endl;
    cout<<is_lvalue_reference_v <decltype(get().s)><<endl;
    cout<<is_lvalue_reference_v <decltype(get())><<endl;
    cout<<is_lvalue_reference_v <decltype(get().iarr)><<endl;
    cout<<is_lvalue_reference_v <decltype(get().sarr)><<endl;


     
    return 0;
}