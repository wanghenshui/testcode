#include <bitset>
#include <cstddef>
#include <iostream>
#include <string>

using namespace std;

template <typename charT, size_t N>
basic_string<charT> bitset2string(const bitset<N>& bs)
{
	return bs. template to_string<charT,char_traits<charT>,allocator<charT> >();
}

int main(int argc, char const *argv[])
{
	bitset<10> bs;
	bs.set(1);
	bs.set(5);

	cout<<bs<<endl;
	string s = bitset2string<char> (bs);
	cout<<s<<endl;
	return 0;
}