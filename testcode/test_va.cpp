#define AA(_fmt,...) printf(_fmt,##__VA_ARGS__) 


#define PRINT(...) printf(__VA_ARGS__)

#define BB(_fmt,...) PRINT(_fmt,##__VA_ARGS__) 


#define PRINT2(_fmt,...) printf(_fmt,##__VA_ARGS__)

#define CC(_fmt,...) PRINT2(_fmt,##__VA_ARGS__) 
#include <cstdio>
int main()
{
	AA("goodday"); // 成功
	BB("goodday"); // ！报错  
	CC("goodday"); // 成功  
	AA("%s", "goodday"); // 成功
	BB("%s", "goodday"); // 成功 
}