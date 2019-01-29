// C++ program to find maximum sum of hour 
// glass in matrix 
#include <iostream>
#include <vector> 
#include <climits>
#include <cstdio>
using namespace std; 

  

// Returns maximum sum of hour glass in ar[][] 
int findMaxSum(vector<vector<int> >&mat) 
{ 
    size_t R = mat.size();
	size_t C = mat[0].size();
	if (R<3 ||C<3) 
		return -1; 

	// Here loop runs (R-2)*(C-2) times considering 
	// different top left cells of hour glasses. 
	int max_sum = INT_MIN; 
	for (int i=0; i<R-2; i++) 
	{ 
		for (int j=0; j<C-2; j++) 
		{ 
			// Considering mat[i][j] as top left cell of 
			// hour glass. 
			int sum = (mat[i][j]+mat[i][j+1]+mat[i][j+2])+ 
					(mat[i+1][j+1])+ 
				(mat[i+2][j]+mat[i+2][j+1]+mat[i+2][j+2]); 

			// If previous sum is less then current sum then 
			// update new sum in max_sum 
			max_sum = max(max_sum, sum); 
		} 
	} 
	return max_sum; 
} 

// Driver code 
int main() 
{ 

	int m;
	int n;
	
    scanf("%d %d",&n,&m);
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
		for(int i=0;i<m;i++)
		{
			target[i][j] = arr[m*i+j];
		}
	}
	
	cout<<findMaxSum(target); 
	return 0; 
} 
