#include "scanner.hpp"
#include "parser.hpp"
#include "symbol_table.hpp"
const int maxBuf = 100;

int main()
{
	char buf [maxBuf];
	status ss;
	//symbol_table st;
	do
	{
		std::cout<< "> ";
		std::cin.getline(buf,maxBuf);
		scanner sc(buf);
		parser pr(sc,st);
		status = pr.eval();
	}while(ss!=stQuit);
}