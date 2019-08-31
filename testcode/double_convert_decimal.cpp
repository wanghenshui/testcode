#include <cstdio>
#include <iostream>
int main()
{  
    double m=0;
    int n=0;
    while(std::cin>>m >> n)
    {
        if(int (m) == 0 && n == 0) break;
    	int buf[10] ;
		int i;
		for (i = 0; i < 10; i++) {
			m *= n;
			buf[i] = (int)m ;
			if(m>=1.0) m -= buf[i];
		}
		printf("0.");
		for (i = 0; i < 10; i++)
			printf("%d", buf[i]);
		printf("\n");
    }
    return 0;
}
