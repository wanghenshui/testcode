#ifndef __scanner__
#define __scanner__ 1
#include "fwd.hpp"

const int maxSymLen = 1000;

class scanner
{
public:
	scanner(char const * buf);
	EToken token() const {return _token;}
	void get_symbolname(char * str, int & len);
	void accept();
	double number()
	{
		assert(_token == tNumber);
		return _number;
	}
	//~scanner();
private:

	char const * const _buf;
	void eat_white();
	int _iLook;
	EToken _token;
	double _number;	
	int _lenSymbol;
	int _iSymbol;
};

scanner::scanner(char const * buf)
:_buf(buf),_iLook(0)
{
	std::cout << "scanner with \" "<< buf << "\"" << std::endl;
	accept();
}

void scanner::eat_white()
{
	while(std::isspace(_buf[_iLook]))
		++_iLook;
}

void scanner::accept()
{
	eat_white();
	switch(_buf[_iLook])
	{
		case '+':
			_token = tPlus;
			++_iLook;
			break;

		case '*':
			_token = tMult;
			++_iLook;
			break;

		case '\\':
			_token = tDivide;
			++_iLook;
			break;

		case '-':
			_token = tMinus;
			++_iLook;
			break;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			//fall throught
			_token = tNumber;
			_number = std::atoi(&_buf[_iLook]);
			while(std::isdigit(_buf[_iLook]))
				++_iLook;
			break;

		case '.':
			_token = tNumber;
			char *p;
			_number = std::strtod(&_buf[_iLook],&p);
			_iLook= p -_buf;
			break;

		case '\0':
			_token = tEnd;
			break;
		default:
			if ((std::isalpha(_buf[_iLook]))|| _buf[_iLook] == '_')
			{
				_token = tIdent;
				_iSymbol = _iLook;

				int cLook;

				do{
					++_iLook;
					cLook = _buf[_iLook];
				}while(std::isalnum(cLook)||cLook== '_');

				_lenSymbol = _iLook - _iSymbol;

				if(_lenSymbol>=maxSymLen)	_lenSymbol = maxSymLen-1;
			}
			else
				_token = tError;
			break;
	}
}
void scanner::get_symbolname(char * str, int & len)
{
	assert(len>=maxSymLen);
	assert(_lenSymbol<=maxSymLen);

	std::strncpy(str,&_buf[_iSymbol],_lenSymbol);

	str[_lenSymbol]= '\0';
	len = _lenSymbol;
}

#endif //:define guard end