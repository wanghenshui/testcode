#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    int arr[] = { 1, 2, 3, 777, 1, 2, 3 };
    int ret = 0;
    int len = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < len; i++)
    {
        ret ^= arr[i];
    }
    printf("出现奇数次的数为:> %d\n", ret);
    return 0;
}
 