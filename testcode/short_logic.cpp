#include <iostream>
//invalid operands of types 'int' and 
//'<unresolved overloaded function type>' to binary 'operator<<'
int main()
{
	int a,b,c;

	for(a=0; a<2; a++)
		for(b=0;b<2;b++)
			for(c=0;c<2;c++)
	{
		std::cout<<"a&&(b||c),a,b,c"<<(a&&(b||c))<<"||"<< a<<b<<c<<std::endl;
		std::cout<<"  b||c&&a,a,b,c"<<(b||c&&a)<<"||"<< a<<b<<c<<std::endl;
	}
	return 0;
}

