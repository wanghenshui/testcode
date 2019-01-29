// CPP program to find Minimum  
// number of jumps to reach end 
#include <iostream>
#include <vector> 
#include <climits>
#include <cstdio>
using namespace std; 
  
// Returns minimum number of jumps to reach arr[n-1] from arr[0] 
int minJumps(int arr[], int n) 
{ 
    int *jumps = new int[n];  // jumps[n-1] will hold the result 
    int i, j; 
  
    if (n == 0 || arr[0] == 0) 
        return INT_MAX; 
  
    jumps[0] = 0; 
  
    // Find the minimum number of jumps to reach arr[i] 
    // from arr[0], and assign this value to jumps[i] 
    for (i = 1; i < n; i++) 
    { 
        jumps[i] = INT_MAX; 
        for (j = 0; j < i; j++) 
        { 
            if (i <= j + arr[j] && jumps[j] != INT_MAX) 
            { 
                 jumps[i] = min(jumps[i], jumps[j] + 1); 
                 break; 
            } 
        } 
    } 
    return jumps[n-1]; 
} 
  
// Driver program to test above function 
int main() 
{ 
    vector<int> arr;
    for(int i=0;;i++)
    {   int tem;
        cin >> tem;
        arr.push_back(tem);
        if(getchar()=='\n') //遇回车结束
            break;
    }
    int size = arr.size(); 
	//int a[arr.size()];
	int * a=new int[size];
	for(int i=0;i<size;++i)
	{
		a[i]=arr[i];
	}
    cout<< minJumps(a, size); 
    return 0; 
} 