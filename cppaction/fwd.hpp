#ifndef __FWD__
#define __FWD__

#include <iostream> //:cout and endl
#include <cassert> //: assert
#include <cstdlib>
#include <cstring>


typedef enum status
{
	stOK,
	stQuit,
	stError,
}status;

typedef enum EToken
{
	tEnd,
	tError,
	tNumber,
	tPlus,		// +
	tMinus,		// -
	tMult,		// *
	tDivide,	// /
	tLParen,	// (
	tRParen,	// )
	tAssign,	// =
	tIdent 		// all
}EToken;


typedef enum status status;
typedef enum EToken EToken;


#endif //: FWD defination end