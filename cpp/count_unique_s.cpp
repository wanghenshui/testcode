#include <string>
#include <iostream>

template <typename T>
int count_unique_s(const std::basic_string<T>& s)
{
	using std::basic_string;

	basic_string<T> chars;

	for(typename basic_string<T>::const_iterator iter =s.begin();iter!=s.end();++iter)
	{
		if(chars.find(*iter)== basic_string<T>::npos)
				chars +=*iter;
	}
	return chars.length();
	
}

int main()
{
	std::string s= "Abracadabra";
	std::cout <<count_unique_s(s)<<'\n';
}
