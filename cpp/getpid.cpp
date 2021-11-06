#include <iostream>
#include <unistd.h>
#include <cstdlib>

int main()
{
	std::cout<<"PID = "<<getpid()<<std::endl;
	std::cout<<"PPID = "<<getppid()<<std::endl;
}
