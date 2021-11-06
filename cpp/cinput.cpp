#include <cctype>
#include <cstdlib>
#include <iostream>
#include "cinput.h"
namespace calc_cl_naive{

cinput::cinput()
{
	std::cin >> ci_buf;

	int c = ci_buf[0];

	if(std::isdigit(c))
		ci_token = tokNumber;
	else if(c == '+' || c == '*' || c == '/')
		ci_token = c;
	else if(c == '-')
	{
		if(std::isdigit(_buf[1]))
			ci_token = tokNumber;
		else
			ci_token = c;
	}
	else 
		ci_token = tokError;
}

int cinput::number () const
{
	assert(_token == tokNumber);
	return std::atoi(ci_buf);
}

int cinput::token() const
{
	return ci_token;
}

cinput::~cinput(){};

}//: end for namespace calc_cl_naive