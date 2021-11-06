#include <cmath> 
#include <cstdlib> 
#include <iostream> 
#include <vector> 
using namespace std; 
class Solution {
public:
    int bulbSwitch(int n) {
        return sqrt(double(n));//fuck msvc 2005
		//https://stackoverflow.com/questions/22962661/getting-error-c2668-sqrt-ambiguous-call-to-overloaded-function
    }
};

int main() 
{	 
	Solution s;
	int N =0 ; 
	cin>>N;
 
	cout<<s.bulbSwitch(N); 
}