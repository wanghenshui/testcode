
#include <iostream>
#include <vector> 
#include <climits>
#include <cstdio>
using namespace std; 
using namespace std; 
  
#define SIZE 10 
  
// function to find the maximum sum 
// path in a matric 
int maxSum(vector<vector<int> >&mat, int n) 
{ 
    // if there is a single element only 
    if (n == 1) 
        return mat[0][0]; 
  
    // dp[][] matrix to store the results 
    // of each iteration 
    //int dp[n][n]; huawei oj msvc 2005 fuck it
	int ** dp = new int*[n];
	for(int i=0;i<n;i++)
		dp[i] = new int[n];
	
    int maxSum = INT_MIN, max; 
  
    // base case, copying elements of 
    // last row 
    for (int j = 0; j < n; j++) 
        dp[n - 1][j] = mat[n - 1][j]; 
  
    // building up the dp[][] matrix from 
    // bottom to the top row 
    for (int i = n - 2; i >= 0; i--) { 
        for (int j = 0; j < n; j++) { 
            max = INT_MIN; 
  
            // finding the maximum diagonal element in the 
            // (i+1)th row if that cell exists 
            if (((j - 1) >= 0) && (max < dp[i + 1][j - 1])) 
                max = dp[i + 1][j - 1]; 
            if (((j + 1) < n) && (max < dp[i + 1][j + 1])) 
                max = dp[i + 1][j + 1]; 
  
            // adding that 'max' element to the 
            // mat[i][j] element 
            dp[i][j] = mat[i][j] + max; 
        } 
    } 
  
    // finding the maximum value from the 
    // first row of dp[][] 
    for (int j = 0; j < n; j++) 
        if (maxSum < dp[0][j]) 
            maxSum = dp[0][j]; 
  
    // required maximum sum 
	for(int i=0;i<n;i++)
		delete[]dp[i];
	delete []dp;
    return maxSum; 
} 
  
// Driver program to test above 
int main() 
{ /*
    int mat[SIZE][SIZE] = { { 5, 6, 1, 7 }, 
                            { -2, 10, 8, -1 }, 
                            { 3, -7, -9, 11 }, 
                            { 12, -4, 2, 6 } }; 
*/
    int n=0;
    scanf("%d",&n);
	while(getchar()=='\n') break;
	
    vector<int> arr;
    for(int i=0;;i++)
    {   int tem;
        cin >> tem;
        arr.push_back(tem);
        if(getchar()=='\n') //遇回车结束
            break;
    }

	vector<vector<int> > target;
	const vector<int> init(n,0);
	for(int i=0;i<n;i++)
	{
		target.push_back(init);
	}
	
	const int size = arr.size();

	for(int j=n-1;j>-1;j--)
	{
		for(int i=0;i<n;i++)
		{
			target[i][j] = arr[n*i+j];
		}
	}

    cout << maxSum(target, n); 
  
    return 0; 
} 