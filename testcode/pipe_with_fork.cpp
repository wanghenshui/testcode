#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
int  main()
{
    int pipea[2];
    pid_t pid;
    char buf[100];
    int num;

    memset(buf,0,sizeof(buf));

    if(pipe(pipea)<0)
	{
	    std::cout<<"pipe error"<<"\n";
	    return -1;
    }
	if(pid=fork()==0)
    {
     	close(pipea[1]);
		sleep(2);
	
		if((num=read(pipea[0],buf,100))>0)
			std::cout<<num<<" read from pipe is "<<buf<<"\n";
		close(pipea[0]);
		exit(0);
    }
	else if(pid>0)
    {
		close(pipea[0]);
		if(write(pipea[1],"fuck you" ,8)!= -1)
			std::cout<<"parent fuck you"<<"\n";
		if(write(pipea[1],"fuck you again",14)!=-1)
			std::cout<<"parent fuck you again"<<"\n";
		close(pipea[1]);
		sleep(4);
		waitpid(pid,NULL,0);
		exit(0);
    }
}
