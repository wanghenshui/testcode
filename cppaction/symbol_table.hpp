#ifndef __symbol_table__
#define __symbol_table__

const int idNotFound = -1;

class symbol_table
{
	HTable _htab;
	int _maxID;
	int * _offstr;
	int _curId;
	StringBuffer _strBuf;

public:
	explicit symbol_table(int size);

	~symbol_table();	

	int force_add(char const * str, int len);
	int find(char const * str) const;
	char const * get_string(int id) const;
};

symbol_table::symbol_table(int size)
:_curId(0),_maxID(size),_htab(size+1),_strBuf(size*10)
{
	_offstr = new int [size];
}


symbol_table::~symbol_table()
{
	delete [] _offstr;
}
#endif //: define guard end