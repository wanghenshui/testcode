#include <iostream>
#include <map>
#include <string>

struct A {
int a, b;
    std::string c;
    std::map<int, int> m;
};

struct B {
int a, b;
    std::string c;
    std::map<int, int> m;
};


int main() {
    A a;

    B b;
    b.a = 1;
    b.b = 2;
    static_assert(sizeof(A) == sizeof(B), "size must equal");
    a = *(reinterpret_cast<A*>(&b));
    std::cout<< a.a << " " << a.b << '\n';
    return 0;
}
