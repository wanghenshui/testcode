#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

int main()
{
	pid_t pc,pr;
	pc = fork();

	if(pc==0)
	{
		std::cout <<"child, pid = "<<getpid()<<std::endl;
		sleep(10);
	}
	else if(pc>0)
	{
		pr=wait(NULL);
		std::cout<<"catch child pid = "<<pr<<std::endl;
	}

}
