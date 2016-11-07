/*UVa10082
 *使用数组 思路就是都存起来，减一就可以了
 */

#include <stdio.h>

char s[] = "`1234567890-=qwerty-uiop[]\\asdfghjkl;'zxcvbnm,./";

int main()
{
	int i,c;
	while((c=getchar())!=EOF)	
	{
		for(i=1; s[i]!=c; i++)
		{
			if(s[i]) putchar(s[i-i]);
			else putchar(c);
		}
	}
	return 0;
}
