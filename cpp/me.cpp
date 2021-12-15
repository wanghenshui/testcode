#define MAP_LOOP_SOLUTION 1
#ifdef MAP_STL_SOLUTION
struct LessBySecond
{
    template <typename Lhs, typename Rhs>
    bool operator()(const Lhs& lhs, const Rhs& rhs) const
    {
        return lhs.second < rhs.second;
    }
};
#endif
class Solution {
public:
    int majorityElement(vector<int>& nums)
    {
        
        
 #ifdef MAP_LOOP_SOLUTION
        map<const int,int> kv;
        for(int i=0;i<nums.size();++i)
        {
            kv.insert(make_pair(nums[i],count(nums.begin(),nums.end(),nums[i])));
        }
        /*
        for(auto &i :kv)
        {
            cout<<i.first<<i.second<<endl;
        }*/
        map<int,int>::iterator it = kv.begin();
        int max_value =  it->second;
        int res =it->first;
        for(;it!=kv.end();++it)
        {
            if(it->second>max_value)
            {
                max_value = it->second;
                res = it->first;
            }
        }
        //cout<<it->first<<it->second<<endl;
        cout<<"FUCK TLE"<<endl;
        return res;
       
#endif

#ifdef MAP_STL_SOLUTION
        for(auto &i :kv)
        {
            if(i.second == std::max_element(kv.begin(), kv.end(), LessBySecond())->second)
            return i.first;
        }
#endif
    }
};

