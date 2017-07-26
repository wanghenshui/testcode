#include <iostream>

#if 0
// expected constructor, destructor, or type conversion before ‘;’ token

void ct()
{
	std::cout<<"out main"<<std::endl;
}

ct();
#endif
class base
{
public:
	base(){
		OnInitInstance();
		run();
	};
	~base(){
		std::cout<<"leave base"<<std::endl;
	};

	void OnInitInstance()
	{
		std::cout<<"base instance"<<std::endl;
	}
	
	virtual bool run()
	{
		std::cout<<"base run"<<std::endl;
	}
};
class client :public base
{
public:
	client()
	{
		run();
	};
	~client(){
	std::cout<<"leave client"<<std::endl;	
	};
	bool run()
	{
		std::cout<<"run client"<<std::endl;
	}	
};
base a;

int main()
{
	client c;
	std	::cout<<"main"<<std::endl;
}