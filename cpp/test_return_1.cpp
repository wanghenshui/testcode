#include <iostream>
using namespace std;
#include <cstdio>

unsigned char u8()
{
	return -1;
}

unsigned short u16()
{
	return -1;
}

unsigned int u32()
{
	return -1;
}

int main() {
	unsigned char a = u8();
	unsigned short b = u16();
	unsigned int c = u32();
	
	printf("u8=%d,u16=%d,u32=%d\n",a,b,c);
	printf("u8=%u,u16=%u,u32=%u\n",a,b,c);
	cout<<c<<endl;
	// your code goes here
	return 0;
}