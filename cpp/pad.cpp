#include <string>
#include <iostream>

using namespace std;

template <typename T> 
void pad(basic_string<T>& s, typename basic_string<T>::size_type n, T c)//为什么size_type要加typename 
{
	if(n>s.length())
	{
		s.append(n-s.length(),c);
	}
}

int main()
{
	string s="Appendix A";
	wstring ws=L"Acknowledgments";

	pad(s,20,'*');
	pad(ws,20,L'#');

	cout<<s<<endl;
	wcout<<ws<<endl;
}