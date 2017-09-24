int strlen(char const * pstr)
{
	char const *p = pstr;
	while(*p++)
		;
	return p - pstr - 1;
}

#include <iostream>
int main()
{
	char aString[] = "the long tring";
	int len = strlen(aString);
	std::cout<<len<<std::endl;
}