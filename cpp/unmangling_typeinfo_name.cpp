#include <cstdlib>

#include <memory>
#include <string>
#include <typeinfo>

#include <cxxabi.h>

// https://stackoverflow.com/questions/281818/unmangling-the-result-of-stdtype-infoname
std::string demangle(const char* name) {

    int status = -4; // some arbitrary value to eliminate the compiler warning

    // enable c++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };
    return (status==0) ? res.get() : name ;
}

template <class T>
std::string type(const T& t) {
    return demangle(typeid(t).name());
}


#include <iostream>
int main() {
    // it's UB
    auto && s= std::move(std::string("1234"));
    s.append("5");
    std::cout<<s;
    std::cout<<type(s);
}
