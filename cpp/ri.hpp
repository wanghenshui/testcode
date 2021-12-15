#ifndef __LEETCODE_ROTATE_IMAGE_H
#define __LEETCODE_ROTATE_IMAGE_H
#include <vector>
#include <algorithm>
class Solution{
public:
	void rotate(std::vector<std::vector<int> >& matrix)
	{
		const int n = matrix.size();
		for(int i=0; i<n; ++i)//副对角线
			for(int j=0; j<n-1; ++j)
				std::swap(matrix[i][j],matrix[n-1-j][n-1-i]);

		for(int i=0; i<n/2; ++i)//水平中线
			for(int j=0; j<n; ++j)
				std::swap(matrix[i][j],matrix[n-1-i][j]);

#if 0
		for(int i=0; i<n/2; ++i)//水平中线
			for(int j=0; j<n; ++j)
				std::swap(matrix[i][j],matrix[n-1-i][j]);

		for(int i=0; i<n; ++i)//主对角线
			for(int j=0; j<n-1; ++j)
				std::swap(matrix[i][j],matrix[j][i]);
#endif
	}
};

#endif
