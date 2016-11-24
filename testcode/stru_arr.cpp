#include <iostream>
#include <cstring>
using namespace std;

typedef struct info_stru
{
	uint8_t          a;
	uint8_t          b;
	uint8_t          c
}info_stru;

typedef struct box_stru
{
	uint8_t                infono;
	info_stru     		   Info[32];

}box_stru;

int main()
{
	
	box_stru *p;
	memset(p,0xff,sizeof(box_stru));

	p->Info->a = 5;

	cout<<

}