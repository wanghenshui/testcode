//:
#include <string>
#include <fstream>
using namespace std;

int main()
{
	ifstream in ("scopy.cpp");
	ofstream out ("scopy2.cpp");
	string s;
	while(getline(in,s))
		out << s << "\n";
}
///:~