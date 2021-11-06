#include <stdio.h>
#include <stdlib.h>

static const int pagelen = 24;
static const int linelen = 512;

//print
int see_more(FILE * tty)
{
	int c;
	printf("\033[7m more?\033[m");
	while((c=getc(tty))!=EOF)
	{
		if(c=='q')
			return 0;
		if(c==' ')
			return pagelen;
		if(c=='\n')
			return 1;
	}
	return 0;
}

// read pagelen lines 
void do_more(FILE *fp)
{
	char line[linelen];
	int num_of_lines = 0;
	int reply;
	FILE * fp_tty = fopen("/dev/tty","r");
	if (fp_tty==NULL)
		exit(1);

	while(fgets(line,linelen,fp))
	{
		if(num_of_lines == pagelen)
		{
			reply=see_more(fp_tty);
			if(!reply)
				break;
			num_of_lines -=reply;
		}
		if(fputs(line,stdout) == EOF)
			exit(1);
		num_of_lines++;
	}
}

int main(int argc,char **argv)
{
	FILE * fp;
	if (argc == 1)
		do_more(stdin);
	else
		while(--argc)
			if ((fp=fopen(*++argv,"r"))!=NULL)
			{
				do_more(fp);
				fclose(fp);
			}
			else
				exit(1);
	return 0;
}