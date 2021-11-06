#include <string>
#include <iostream>
#include <cctype>
#include <cwctype>

using namespace std;

template <typename T,typename F>
void rtrim_whitespace(basic_string<T>& s, F f)//注意这里，函数对象可以这么使用
{
	if(s.empty())	return;

	typename basic_string<T>::iterator it;

	for(it=s.end();it!=s.begin()&&f(*--it);	)
		//当然这里用反向迭代器更好一些
		;
	if(!f(*it)) it++;

	s.erase(it,s.end());
}
//重载也可以重载自己将细节隐藏在实现里。这种是不是调用代价挺大的？
void rtrim_whitespace(string &s) {	rtrim_whitespace(s,::isspace); }
void rtrim_whitespace(wstring &ws) {	rtrim_whitespace(ws,::iswspace);	}

/*
isspace在c++的实现是模板，想调用c系列的对象得用::
编译不通过的原因见
https://stackoverflow.com/questions/3679801/overloading-functions-not-compiling

更改后gcc通过，clang还是没通过，编译信息有一页，有点恐怖，我就没研究
*/
int main()
{
	string s="sss    ";
	wstring ws=L"wswsws    ";

	rtrim_whitespace(s);
	rtrim_whitespace(ws);
	cout<<s<<"|\n";
	wcout<<ws<<L"|\n";

}