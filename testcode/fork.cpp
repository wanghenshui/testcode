#include <iostream>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid;

	std::cout<<"i am your father pid = "<<getpid()<<std::endl;
	pid = fork();

	if(pid<0)
		std::cout<<"fork errro"<<std::endl;
	else if(pid == 0)
		std::cout<<"child, pid =  "<<getpid()<<std::endl;
	else 
		std::cout<<"parent, pid = "<<getpid()<<std::endl;

}
