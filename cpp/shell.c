#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

void do_exe(char* buf, char* argv[]) //加载程序
{
	pid_t pid = fork();

	if (pid == 0)//子进程
	{
		//寻找重定向标志 >
		for (int i = 0; argv[i] != NULL; ++i)
		{
			if (strcmp(argv[i], ">") == 0)
			{
				if (argv[i + 1] == NULL) //> 后面未带参数
					perror("command '>'[option]?"), exit(1);
				argv[i] = NULL;
				//根据解析命令参数，创建/打开一文件
				int fd = open(argv[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0664);
				if (fd == -1)perror("open"), exit(1);
				//重定向操作
				dup2(fd, 1); //dup2(oldfd, newfd);
				close(fd);
			}
		}
		execvp(buf, argv);
		perror("fork"); //执行到此，说明execvp未执行成功，fork失败
		exit(1);
	}
	wait(NULL);  //等待子进程死亡, 回收
}
//对命令进行解析
void do_parse(char* buf) {
	char* argv[8] = {}; //将buf中的命令以‘ ’为分界存入指针数组中
	int argc = 0;
	int status = 0; //一个新的字符串
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

		//[^\n]匹配除\n以外的所有字符,*用于抑制转换
		//scanf成功返回输入的项数
		while (scanf("%[^\n]%*c", buf) == 0) { //为0表示只输入了换行
			printf("sh> ");
			while (getchar() != '\n');  //到获得了一个‘\n'
		}
		do_parse(buf);
	}
	return 0;
}