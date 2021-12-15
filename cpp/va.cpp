class Solution {
public:
    bool isAnagram(string s, string t)
    {
        if (s.length() != t.length()) return false;
        
        unordered_map<char, int> counts;
        //用map记录一遍位置，一样就都消掉 
        for (int i = 0; i !=s.length(); ++i) 
        {
            ++counts[s[i]];
            --counts[t[i]];
        }

        for (auto &i: counts)
            if (i.second) return false;
        return true;
    }
};