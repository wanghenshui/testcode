#include <iostream>
using namespace std;

int main()
{
	const size_t BUFSIZ = 128;
	char s[BUFSIZ];
	size_t wc = 0;

	while(cin>>s)
		++wc;
	cout<<wc<<endl;
}