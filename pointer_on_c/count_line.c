/*
 * 第一章编程练习第二题与第四题，类型一致。实现类似
 * 第二题：从标准输入中读取几行输入并重新打印出来。前面加上行号，
 * 注意不能被行的长度限制，那就只能逐个读扫出\n来判断行数
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int ch;//getchar()返回值是int
	int line = 0;//用于打印行号
	int flag = 1;//一个标记，开关，用于换行


	while((ch = getchar()) != EOF)
	{
		if(flag)
		{
			flag = !flag;
			line +=1;
			printf("%d ",line);
		}
		putchar(ch);

		if(ch == '\n')
			flag = 1;
	}
	
	return 0;
}

