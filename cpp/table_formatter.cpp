#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

template<typename T>
class table_formatter{
public:
		table_formatter(basic_ostream<T>& os): out_(os){}
		~table_formatter(){out_ <<flush;}
		
		template<typename NT>
		void write_table_row(const vector<NT>& v, int width );
private:
		basic_ostream<T>& out_;
};

template<typename T> template<typename NT>
void table_formatter<T>::write_table_row(const vector<NT>& v, int width)
{
		ios_base::fmtflags flags = out_.flags();
		out_.flush();
		out_ << setprecision(2) << fixed;

		for(typename vector<NT>::const_iterator p = v.begin(); p!=v.end(); ++p)
		{
			out_ <<setw(width) <<left << *p;
		}
		out_ << endl;
		out_.flags(flags);
}


int main()
{
	table_formatter<char> fmt(cout);
	vector<string> vs;
	vs.push_back("Sunday");
	vs.push_back("Tuesday");
	vs.push_back("Monday");
	
	fmt.write_table_row(vs,12);
	fmt.write_table_row(vs,12);
	fmt.write_table_row(vs,12);

	vector<double> vd;
	
	vd.push_back(4.0);
	vd.push_back(3.0);
	vd.push_back(2.0);
	vd.push_back(1.0);
	fmt.write_table_row(vd,5);
}
