//http://www.cnblogs.com/grandyang/p/4402656.html
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    int numIslands(vector<vector<int> > &grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size(), res = 0;
        vector<vector<bool> > visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    numIslandsDFS(grid, visited, i, j);
                    ++res;
                }
            }
        }
        return res;
    }
    void numIslandsDFS(vector<vector<int> > &grid, vector<vector<bool> > &visited, int x, int y) {
        if (x < 0 || x >= grid.size()) return;
        if (y < 0 || y >= grid[0].size()) return;
        if (grid[x][y] != '1' || visited[x][y]) return;
        visited[x][y] = true;
        numIslandsDFS(grid, visited, x - 1, y);
        numIslandsDFS(grid, visited, x + 1, y);
        numIslandsDFS(grid, visited, x, y - 1);
        numIslandsDFS(grid, visited, x, y + 1);
    }
};
// Function to print the matrix 
void displayMatrix(const vector<vector<int> >& mat) 
{ 
    const size_t N=mat.size();
	const size_t R=mat[0].size();
    for (int i = 0; i < R; i++) 
    { 
        for (int j = 0; j < N; j++) 
            cout<<"  ", mat[i][j]; 
  
        cout<<("\n"); 
    } 
    cout<<("\n"); 
} 

int main()
{
	Solution solute;
	int n;
    std::vector<int> v;
    int least=2;
	for( int i =  0; i < 2; i++) 
	{ 
		cin >> n;  //读取字符串，不含空格
		v.push_back(n); 
		if(least==2 && i==1) least += v[0]*v[1];
	}
	
	const size_t row = v[0];
	const size_t N=v[1];
	
	vector<int> arr;
	for( int i =  0; i < row*N; i++) 
	{ 
		arr.push_back(v[i+2]); 
		cout<<arr[i]<<" ";
	}

	vector<vector<int> > target;
	const vector<int> init(N,0);
	for(int i=0;i<row;i++)
	{
		target.push_back(init);
	}

	for(int j=row-1;j>-1;j--)
	{
		for(int i=0;i<N;i++)
		{
			target[i][j] = arr[row*(row-i-j)+i];
		}
	}
	displayMatrix(target);
	
	cout<<solute.numIslands(target)<<endl;
}