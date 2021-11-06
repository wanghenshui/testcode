#include <iostream>
#include <string>
#include <functional>
using namespace std;
static const int32_t kTotalChunk = 1 << 20;
int main(int argc, char * argv[])
{
    if(argc > 1) {
        auto s1 = string(argv[1]);
        cout<< s1<<" : "<<hash<string>()(s1) % kTotalChunk<<"\n";
    }
}
