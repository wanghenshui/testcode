#include "printtuple.hpp"
#include <tuple>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	tuple<int, float, string> t(77,1.1,"more light");
	cout<< t<<endl;
}