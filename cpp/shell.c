#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

void do_exe(char* buf, char* argv[]) //���س���
{
	pid_t pid = fork();

	if (pid == 0)//�ӽ���
	{
		//Ѱ���ض����־ >
		for (int i = 0; argv[i] != NULL; ++i)
		{
			if (strcmp(argv[i], ">") == 0)
			{
				if (argv[i + 1] == NULL) //> ����δ������
					perror("command '>'[option]?"), exit(1);
				argv[i] = NULL;
				//���ݽ����������������/��һ�ļ�
				int fd = open(argv[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0664);
				if (fd == -1)perror("open"), exit(1);
				//�ض������
				dup2(fd, 1); //dup2(oldfd, newfd);
				close(fd);
			}
		}
		execvp(buf, argv);
		perror("fork"); //ִ�е��ˣ�˵��execvpδִ�гɹ���forkʧ��
		exit(1);
	}
	wait(NULL);  //�ȴ��ӽ�������, ����
}
//��������н���
void do_parse(char* buf) {
	char* argv[8] = {}; //��buf�е������ԡ� ��Ϊ�ֽ����ָ��������
	int argc = 0;
	int status = 0; //һ���µ��ַ���
	for (int i = 0; buf[i] != 0; ++i) {
		if (status == 0 && !isspace(buf[i])) {
			argv[argc++] = buf + i;
			status = 1;
		}
		else if (isspace(buf[i])) {
			status = 0;
			buf[i] = 0;
		}
	}
	argv[argc] = NULL;

	do_exe(buf, argv);
}

int main()
{
	char buf[1024] = {};
	while (1)
	{
		printf("sh> ");
		memset(buf, 0, sizeof(buf));

		//[^\n]ƥ���\n����������ַ�,*��������ת��
		//scanf�ɹ��������������
		while (scanf("%[^\n]%*c", buf) == 0) { //Ϊ0��ʾֻ�����˻���
			printf("sh> ");
			while (getchar() != '\n');  //�������һ����\n'
		}
		do_parse(buf);
	}
	return 0;
}