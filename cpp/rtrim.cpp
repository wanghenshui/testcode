#include <string>
#include <iostream>

void rtrim(std::string& s,char c)
{
	if(s.empty()) return;

	std::string::iterator p;

	for(p=s.end();p!=s.begin()&&*--p == c; );
		//学习一下这种写法

	if(*p !=c)	p++;

	s.erase(p,s.end());
}

int main()
{
	std::string s="ZOO  ";
	rtrim(s,' ');
	std::cout<<s<<'\n';

	rtrim(s,'O');
	std::cout<<s<<'\n';
}