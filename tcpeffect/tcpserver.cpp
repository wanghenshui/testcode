#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	sockaddr_in local;
	

	local.sin_family = AF_INET;
	local.sin_port = htons(7500);
	local.sin_addr.s_addr = htonl(INADDR_ANY);

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd<0)
	{
		perror("socket error");
		exit(1);
	}

	int ret = bind(fd,(sockaddr*)(&local),sizeof(local));
	if (ret<0)
	{
		perror("bind error");
		exit(1);
	}

	ret = listen(fd,5);
	if(ret)
	{
		perror("listen error");
		exit(1);
	}

	int accept_fd = accept(fd,NULL,NULL);
	if(accept_fd<0)
	{
		perror("accept error");
		exit(1);
	}

	char buf[1];
	ret = recv(accept_fd,buf,1,0);
	if(ret<=0)
	{
		perror("recv error");
		exit(1);
	}

	printf("%c\n",buf[0]);
	ret = send(accept_fd,"2",1,0);
	if(ret<=0)
	{
		perror("send error");
	}
}
