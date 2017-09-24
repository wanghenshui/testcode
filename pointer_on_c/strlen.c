/*
		计算一个字符串的长度
*/

#include <stdlib.h>
#include <stdio.h>
size_t strlen_pc(char *string)
{
	int length = 0;

	while(*string++ != '\0')
		length+=1;
	return length;
}

int main()
{
	char *string = 0;
	scanf("%s",string);
	size_t ret = strlen_pc(string);
	printf("%d\n",ret);
	return 0;
}