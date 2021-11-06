#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main(void)
{
    srand(time(NULL)); // 以当前时间为随机数生成器的种子
    int random_variable ;
    int i=257;
    while(i--)
    {
    	 
    	random_variable= rand();
    	printf("%d,", random_variable);
    }
}