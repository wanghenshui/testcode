#include "fwd.hpp"

enum status
{
	stOK,
	stQuit,
	stError,
};

enum EToken
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
};