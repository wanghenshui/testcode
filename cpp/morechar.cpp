#include <iostream>
int main()
{
	using namespace std;
	char ch = 'M';
	int i = ch;
	
	cout << "the ascii code for " << ch << " is " << i << endl;
	cout << "add one " << endl;
	ch = ch + 1;
	i = ch;

	cout << "the ascii code for " << ch << " is " << i << endl;

	cout << "cout.put" << endl;
	cout.put(ch);
	cout.put('!');


}
