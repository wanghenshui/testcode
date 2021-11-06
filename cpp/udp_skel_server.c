#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define set_errno(e)	errno = (e)
#define isvalidfd(fd)	(fd>=0)


char* program_name;

void error(int status, int err,char *fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	fprintf(stderr,"%s:",program_name);
	vfprintf(stderr,fmt,ap);
	va_end(ap);
	if(err)
		fprintf(stderr,": %s (%d)\n",strerror(err),err);//strerror like perror
	if(status)
		exit(status);
}

static void set_address(char* hname, char* sname, struct sockaddr_in* sap ,char* protocol)
{
	struct servent* sp;
	struct hostent* hp;
	char* endptr;
	short port;

	bzero(sap,sizeof(*sap));
	sap->sin_family = AF_INET;

	if(hname !=NULL)
	{
		if(!inet_aton(hname, &sap->sin_addr))
		{
			hp = gethostbyname(hname);
			if(hp == NULL)
				error(1,0,"unknown host:%s",hname);

			sap->sin_addr = *(struct in_addr*)hp->h_addr;
		}
	}
	else
	{
		sap->sin_addr.s_addr = htonl(INADDR_ANY);
	}

	
	port = strtol(sname,&endptr,0);
	if (*endptr == '\0')
		sap->sin_port = htons(port);
	else
	{
		sp = getservbyname(sname,protocol);
		if(sp == NULL)
			error(1,0,"unknown service,%s\n",sname);
		sap->sin_port = sp->s_port;
	}
}

static void server(int fd,struct sockaddr_in* notuse)
{
	struct sockaddr_in peer;
	int peerlen;
	char buf[1];
	for(;;)
	{
		peerlen = sizeof(peer);
		if(recvfrom(fd,buf,sizeof(buf),0,(struct sockaddr*)&peer,&peerlen)<0)
			error(1,errno,"recvfrom error");

		if(sendto(fd,"hello world\n",13,0,(struct sockaddr *)&peer,peerlen)<0)
			error(1,errno,"sendto error");
	}
}

int main(int argc, char ** argv)
{
	struct sockaddr_in local;

	char* hname;
	char* sname;
	int socket_fd;

	program_name = strrchr(argv[0],'/')? program_name++:(program_name = argv[0]);

	if(argc ==2)
	{
		hname = NULL;
		sname = argv[1];
	}
	else
	{
		hname = argv[1];
		sname = argv[2];
	}

	set_address(hname, sname,&local,"udp");

	socket_fd = socket(AF_INET, SOCK_DGRAM,0);
	if(!isvalidfd(socket_fd))
		error(1,errno,"socket failed");

	if(bind(socket_fd,(struct sockaddr*)&local,sizeof(local)))
		error(1,errno,"bind error");

	server (socket_fd,&local);
} 
