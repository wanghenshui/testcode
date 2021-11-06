#include <iostream>
#include <vector> 
#include <climits>
#include <cstdio>
using namespace std; 
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = 0, smax = INT_MIN;
        const size_t size = nums.size();
		for(int i=0;i<size;i++){
			int num = nums[i];
            sum += num;
            smax = max(smax, sum);
            if (sum < 0) {
                sum = 0;
            }
        }
        return smax;
    }
};

int main(){
    Solution s;
	while(1){
		vector<int> arr;
		for(int i=0;;i++)
		{   int tem;
			cin >> tem;
			arr.push_back(tem);
			if(getchar()=='\n') //遇回车结束
				break;
		}
		if(arr.size()==1 && arr[0]==-1) break;
		cout<<s.maxSubArray(arr)<<endl;
	}
}