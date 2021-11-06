#ifndef __praser__
#define __praser__

#include "fwd.hpp"

class parser
{
public:
	parser(scanner & sc, symbol_table & st);
	status p
	~parser();
	status eval();
private:
	scanner & _scanner;
	symbol_table & _symtab;
};

parser::parser(scanner & sc, symbol_table & st)
:_scanner(sc), _symtab(st)
{
	std::cout<<"parser created\n";
}
status parser::parse(scanner & sc, symbol_table & st)
{
	for(EToken token = _scanner.token();
		token!=tEnd;
		_scanner.accept())
	{
		token = _scanner.token();
		switch(token)
		{
			case tMult:
				std::cout<<"times \n";
				break;
			case tPlus:
				std::cout<<"plus \n";
				break;
			case tNumber:
				std::cout << "number "<<_scanner.number() << std::endl;
				break;
			case tEnd:
				std::cout <<"End \n";
				break;
			case tError:
				std::cout<<"Error \n";
				return stQuit;
			default:
				std::cout<<"ERROR: bad token\n";
				return stQuit;
		}
	}
	return stOK;
}

parser::~parser()
{
	std::cout<< "destroy parser\n";
}

status parser::eval()
{
	std::cout<< "parser eval\n";
	return stQuit;
}

#endif //: praser define guard end