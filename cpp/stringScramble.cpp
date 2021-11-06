#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1 == s2) return true;
        if (s1.size() != s2.size()) return false;
        int n = s1.size(), m[26] = {0};
        for (int i = 0; i < n; ++i) {
            ++m[s1[i] - 'a'];
            --m[s2[i] - 'a'];
        }
        for (int i = 0; i < 26; ++i) {
            if (m[i] != 0) return false;
        }
        for (int i = 1; i < n; ++i) {
            if ((isScramble(s1.substr(0, i), s2.substr(0, i)) && isScramble(s1.substr(i), s2.substr(i))) || (isScramble(s1.substr(0, i), s2.substr(n - i)) && isScramble(s1.substr(i), s2.substr(0, n - i)))) {
                return true;
            }
        }
        return false;
    }
};

int main()
{
	Solution solute;
	std::string  s;
    std::vector<string> v;

	for( int i =  0; i < 2; i++) 
	{ 
		cin >> s;  //读取字符串，不含空格
		v.push_back(s); 
		s =  ""; 
	}
	
	if(solute.isScramble(v[0],v[1]))
	{
		cout<<"Scrambled"<<endl;
	}
	else{
		cout<<"Not Scrambled"<<endl;
	}
}