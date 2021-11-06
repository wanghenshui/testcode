#include <iostream>
#include <istream>
#include <fstream>
#include <string>
using namespace std;

class Employee{
	friend ostream& operator<<(ostream& out, const Employee& emp);
	friend istream& operator>>(istream& in, Employee& emp);
public:
	Employee(){};
	~Employee(){};
	void setFirstName(const string& name){firstName_ = name;}
	void setLastName(const string& name){lastName_ = name;}
private:
	string firstName_;
	string lastName_;
};

ostream& operator<<(ostream& out, const Employee& emp)
{
	out << emp.firstName_ << endl;
	out << emp.lastName_  << endl;
	return out;
}

istream& operator>>(istream& in, Employee& emp)
{
	in>>emp.firstName_;
	in>>emp.lastName_;
	return in;
}

int main()
{
	Employee e;
	string first = "John";
	string last = "Snow";
	e.setFirstName(first);
	e.setLastName(last);

	ofstream out("e.txt");
	if(!out.is_open())
	{
		cerr << "Unable to open output file \n";
		exit(1);
	}

	out<<e;
	out.close();

	ifstream in("e.txt");
	if(!in)//.is_open())
	{
		cerr << "Unable to open input file \n";
		exit(1);
	}

	Employee e2;
	in >> e2;
	in.close();
	cout<<e2;
}