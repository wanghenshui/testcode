class Solution 
{
    public:
        string longestPalindrome(const string& s)
        {
            const int n = s.size();
            vector<vector<bool> > f(n, vector<bool>(n, false));
            size_t max_len = 1, start = 0; 
            for (size_t i = 0; i < s.size(); i++) 
            {
                f[i][i] = true;
                for (size_t j = 0; j < i; j++) 
                { 
                    f[j][i] = (s[j] == s[i] && (i - j < 2 || f[j + 1][i - 1]));
                    if (f[j][i] && max_len < (i - j + 1)) 
                    {
                        max_len = i - j + 1;
                        start = j;
                    }
                }
            }
            return s.substr(start, max_len);
        }
};