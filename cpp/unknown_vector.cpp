#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

vector<int> input(){
	vector<int> arr;
    for(int i=0;;i++)
    {   int tem;
        cin >> tem;
        arr.push_back(tem);
        if(getchar()=='\n') //遇回车结束
            break;
	}
	return arr;
}