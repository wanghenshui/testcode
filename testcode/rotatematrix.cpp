#include <iostream>
#include <vector> 
#include <climits>
#include <cstdio>
using namespace std; 
void rotateMatrix(vector<vector<int> >& mat) 
{ 
    // Consider all squares one by one 
	const size_t N=mat.size();
    for (int x = 0; x < N / 2; x++) 
    { 
        // Consider elements in group of 4 in  
        // current square 
        for (int y = x; y < N-x-1; y++) 
        { 
            // store current cell in temp variable 
            int temp = mat[x][y]; 
  
            // move values from right to top 
            mat[x][y] = mat[y][N-1-x]; 
  
            // move values from bottom to right 
            mat[y][N-1-x] = mat[N-1-x][N-1-y]; 
  
            // move values from left to bottom 
            mat[N-1-x][N-1-y] = mat[N-1-y][x]; 
  
            // assign temp to left 
            mat[N-1-y][x] = temp; 
        } 
    } 
} 
  
// Function to print the matrix 
void displayMatrix(const vector<vector<int> >& mat) 
{ 
    const size_t N=mat.size();
    for (int i = 0; i < N; i++) 
    { 
        for (int j = 0; j < N; j++) 
            printf("%2d ", mat[i][j]); 
  
        printf("\n"); 
    } 
    printf("\n"); 
} 

int main()
{
    int n=0;
    scanf("%d",&n);

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
	//displayMatrix(target);
	rotateMatrix(target);
	displayMatrix(target);
    return 0;
}