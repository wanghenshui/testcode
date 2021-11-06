#include <iostream>
#include <cmath> // for fabs

using namespace std;

bool doubleEquals(double left, double right ,double epsilion)
{
	return (fabs(left -right) < epsilion);
}

bool doubleLes(double left,double right,double epsilion , bool orequal = false)
{
	if (doubleEquals(left,right,epsilion))
		return orequal;
	
	return left <right;
}

bool doubleGreater(double left, double right, double epsilion, bool orequal = false)
{
	if(doubleEquals(left,right,epsilion))
		return orequal;
		
	return left > right;
}


int main()
{
	double first = 0.33333333;
	double second = 1.0/3.0;

	cout << first << endl;
	cout << second << endl;

	cout << boolalpha << (first == second)<< endl;

	cout << doubleEquals(first,second,.0001)<< endl;
	cout << doubleGreater(first,second,.0001) << endl;
	cout << doubleLes(first,second,.0001) << endl;
	cout << doubleGreater(first,second,.0001,true) << endl;
	cout << doubleLes(first,second,.0001,true) << endl;
}
