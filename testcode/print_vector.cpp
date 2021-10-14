#include <vector>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <cstdio>
using namespace std;

void inline print_vector(const std::vector<int> & v)
{
    ostringstream oss;
    copy(v.begin(), v.end(), std::ostream_iterator<int>(oss, " "));
    printf("%s\n", oss.str().c_str());
}
int main()
{
    vector<int> vec {1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6};
    vec.erase(std::remove(
        begin(vec), end(vec), 
                      *std::max_element(begin(vec), end(vec))),
          end(vec));
    print_vector(vec);
}
