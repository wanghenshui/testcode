#include <iostream>

int main()
{
	int a=0;
	int b=0;
    if(!((!a&&b)||(a&&!b)))
	    std::cout << "ERROR1 " <<((!a&&b)||(a&&!b))<<std::endl;
	else
		std::cout <<"pass1"<<std::endl;
	if((a > 1)||(b > 1)||(!((a == 1)||a == 0))|| (!((b == 1) || b == 0)))
	{
		std::cout <<"ERROR2"<<std::endl;
	}
	else
		std::cout <<"pass2"<<std::endl;

	a=1;
	b=0;
    if((!a&&b)||(a&&!b))
	    std::cout << "ERROR1 " <<((!a&&b)||(a&&!b))<<std::endl;
	else
		std::cout <<"pass1"<<std::endl;
	if((a > 1)||(b > 1)||(!((a == 1)||a == 0))|| (!((b == 1) || b == 0)))
	{
		std::cout <<"ERROR2"<<std::endl;
	}
	else
		std::cout <<"pass2"<<std::endl;

	a=1;
	b=1;
    if (!((!a&&b)||(a&&!b)))
	    std::cout << "ERROR1 " <<((!a&&b)||(a&&!b))<<std::endl;
	else
		std::cout <<"pass1"<<std::endl;
	if((a > 1)||(b > 1)||(!((a == 1)||a == 0))|| (!((b == 1) || b == 0)))
	{
		std::cout <<"ERROR2"<<std::endl;
	}
	else
		std::cout <<"pass2"<<std::endl;
	
	a=0;
	b=1;
    if(!((!a&&b)||(a&&!b)))
	    std::cout << "ERROR1 " <<((!a&&b)||(a&&!b))<<std::endl;
	else
		std::cout <<"pass1"<<std::endl;
	if((a > 1)||(b > 1)||(!((a == 1)||a == 0))|| (!((b == 1) || b == 0)))
	{
		std::cout <<"ERROR2"<<std::endl;
	}
	else
		std::cout <<"pass2"<<std::endl;

	a=10;
	b=1;
    if(!((!a&&b)||(a&&!b)))
	    std::cout << "ERROR1 " <<((!a&&b)||(a&&!b))<<std::endl;
	else
		std::cout <<"pass1"<<std::endl;
	if((a > 1)||(b > 1)||(!((a == 1)||a == 0))|| (!((b == 1) || b == 0)))
	{
		std::cout <<"ERROR2"<<std::endl;
	}
	else
		std::cout <<"pass2"<<std::endl;
	a=1;
	b=10;
    if(!((!a&&b)||(a&&!b)))
	    std::cout << "ERROR1 " <<((!a&&b)||(a&&!b))<<std::endl;
	else
		std::cout <<"pass1"<<std::endl;
	if((a > 1)||(b > 1)||(!((a == 1)||a == 0))|| (!((b == 1) || b == 0)))
	{
		std::cout <<"ERROR2"<<std::endl;
	}
	else
		std::cout <<"pass2"<<std::endl;
	a=10;
	b=10;
    if(!((!a&&b)||(a&&!b)))
	    std::cout << "ERROR1 " <<((!a&&b)||(a&&!b))<<std::endl;
	else
		std::cout <<"pass1"<<std::endl;
	if((a > 1)||(b > 1)||(!((a == 1)||a == 0))|| (!((b == 1) || b == 0)))
	{
		std::cout <<"ERROR2"<<std::endl;
	}
	else
		std::cout <<"pass2"<<std::endl;
}
