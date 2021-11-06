#include <iostream>
#include <string>
#include <vector>
using namespace std;

//http://www.cnblogs.com/grandyang/p/4298664.html
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size()) return false;
        int n1 = s1.size(), n2 = s2.size();
        vector<vector<bool> > dp(n1 + 1, vector<bool> (n2 + 1, false)); 
        for (int i = 0; i <= n1; ++i) {
            for (int j = 0; j <= n2; ++j) {
                if (i == 0 && j == 0) {
                    dp[i][j] = true;
                } else if (i == 0) {
                    dp[i][j] = dp[i][j - 1] && s2[j - 1] == s3[i + j - 1];
                } else if (j == 0) {
                    dp[i][j] = dp[i - 1][j] && s1[i - 1] == s3[i + j - 1];
                } else {
                    dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) || (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
                }
            }
        }
        return dp[n1][n2];
    }
};

int main()
{
	Solution solute;
	std::string  s;
    std::vector<string> v;

	for( int i =  0; i < 3; i++) 
	{ 
		cin >> s;  //读取字符串，不含空格
		v.push_back(s); 
		s =  ""; 
	}
	
	if(solute.isInterleave(v[0],v[1],v[2]))
	{
		cout<<"True"<<endl;
	}
	else{
		cout<<"False"<<endl;
	}
}