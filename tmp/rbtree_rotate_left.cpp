#include <iostream>
#include <cstdlib>
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <algorithm>
#include <thread>
#include <memory>
using namespace std;
int main()
{

    std::map<int, int> v;
    for(int i=0;i<10; i++)
        v[i]=i;

    std::vector<std::thread> threads(10);
    for (size_t i=0; i<12; ++i) {
        threads[i] = thread([&, i] {
            std::cout<<v[i]<<'\n';
        });
    }

    for (auto &t :threads)
        t.join();
}
