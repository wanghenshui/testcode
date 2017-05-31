#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <cstdlib>


int main()
{
	int pipe_fd[2];

	if(pipe(pipe_fd)<0)
	{
		std::cout<<"pipe create error"<<"\n";
		return -1;
	}
	else
		std::cout<<"fuck yeah"<<std::endl;

	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
