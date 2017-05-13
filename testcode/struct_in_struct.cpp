
bool om_status;
bool llc_status;



struct EMB
{
	bool is_f(){return ::om_status?1:0;};
	bool is_s(){return ::llc_status?1:0;};
	typedef int value_type;	

	EMB(value_type & inst)
	{
		if(is_f())
		{
			if (is_s())
			{
				inst =1;
			}
			else
			{
				inst =0;
			}
		}
		else
		{
			inst = 0;
		}
	};
};


struct BLOB
{
	int blob;
	EMB b;
};

BLOB g;
#include <iostream>
int main()
{
	std::cout<<g.b<<std::endl;
	om_status=0;llc_status=0;
	std::cout<<g.b<<std::endl;
	std::endl;
	om_status=0;llc_status=1;
	std::cout<<g.b<<std::endl;
	std::endl;
	om_status=1;llc_status=0;
	std::cout<<g.b<<std::endl;
	std::endl;
	om_status=1;llc_status=1;
	std::cout<<g.b<<std::endl;

}