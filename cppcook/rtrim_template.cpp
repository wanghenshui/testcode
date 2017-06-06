#include <string>
#include <iostream>

using namespace std;

template<typename T>
void rtrim(basic_string<T>& s,T c)
{
	if(s.empty()) return;

	typename basic_string<T>::iterator it;

	for(it=s.end();it!=s.begin()&&*--it==c;	)
		;

	if(*it !=c) it++;
	
	s.erase(it,s.end());
}

int main()
{
	string s="Great!!!!    ";
	wstring ws=L"super!!!!####";

	rtrim(s,' ');
	cout<<s<<'\n';
	rtrim(s,'!');
	cout<<s<<'\n';

	rtrim(ws,L'#');
	wcout<<ws<<'\n';
	rtrim(ws,L'!');
	wcout<<ws<<'\n';
	//注意宽字符的输出wcout和L 不然编译错误会有一页

}