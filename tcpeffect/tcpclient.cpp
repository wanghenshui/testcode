#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(7500);
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int s = socket(AF_INET, SOCK_STREAM, 0) ;
	if (s<0)
	{
		perror("socket fd error");
		exit(1);
	}

	int rc = connect(s,(sockaddr *)&peer, sizeof(peer));
	if(rc<0)
	{
		perror("connect fd error");
		exit(2);
	}

	rc = send(s,"1",1,0);
	if(rc<=0)
	{
		perror("send error");
		exit(3);
	}

	char buf[1];
	rc = recv(s,buf,1,0);
	if(rc<=0)
	{
		perror("recv failed");
	}
	else
	{
		printf("%c\n",buf[0]);
	}
	exit(0);
}
