#include <ratio>
#include <iostream>

using namespace std;

int main()
{
	typedef ratio<5,3> FiveThirds;
	typedef ratio<25,15> AlsoFiveThirds;
	cout<<FiveThirds::num<<"/"<<FiveThirds::den<<endl;
	cout<<AlsoFiveThirds::num<<"/"<<AlsoFiveThirds::den<<endl;
	cout<<std::ratio_add<std::ratio<2,7>, std::ratio<2,6>>::type::num<<"/"
		<<std::ratio_add<std::ratio<2,7>, std::ratio<2,6>>::type::den<<endl;
}