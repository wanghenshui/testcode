#include <string>
#include <unordered_set>

class Solution {
public:
    std::vector<std::string> findWords(std::vector<std::string>& words) {
        std::unordered_set<char> row1 {'q', 'w', 'e', 'r', 't', 'y','u', 'i', 'o', 'p'};
        std::unordered_set<char> row2 {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'}; 
        std::unordered_set<char> row3 { 'z', 'x', 'c', 'v', 'b' ,'n', 'm'};
        std::vector<std::unordered_set<char>> rows {row1, row2, row3};
        
        
        std::vector<std::string> validWords;
        for(std::vector<std::string>::size_type i=0; i!=words.size(); ++i)
        {
            int row=0;
            
            for(int k=0; k<3; ++k)
            {
                if(rows[k].count((char)tolower(words[i][0])) > 0) row = k;
            }
            
            validWords.push_back(words[i]);
            for(std::vector<std::string>::size_type j=1; j!=words[i].size(); ++j){
                if(rows[row].count((char)tolower(words[i][j])) == 0){
                    validWords.pop_back();
                    break;
                }
            }
            
        }
        return validWords;
    }
};