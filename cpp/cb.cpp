class Solution {
public:
    vector<int> countBits(int num) 
    {
        vector<int> answer;
        
        for(int tmp=0; tmp<=num; ++tmp )
        {
            answer.push_back(count_one(tmp));
        }
        return answer;
    }
    
    int count_one(int n)
    {
        unsigned int c =0 ;
        for (c =0; n; ++c)
        {
            n &= (n -1) ; 
        }
        return c ;
    }
};