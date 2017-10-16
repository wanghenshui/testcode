#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
	ios_base::fmtflags flags = cout.flags();
	string first,last,citystate;
	int width = 20;

	first = "Richard";
	last = "Stevens";
	citystate = "Tucson, A2";

	cout<<left
			<<setw(width)<<first
			<<setw(width)<<last
			<<setw(width)<<citystate<<endl;
	cout.flags(flags);
}
