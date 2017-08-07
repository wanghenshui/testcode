#ifndef  __strtab__
#define __strtab__

#include "string_buffer.hpp"
#include "link.hpp"
#include "hash_table.hpp"

const int idNotFound = -1;//EOF
const int maxStrings = 100;


class StringTable
{
public:
	StringTable();
	int ForceAdd(char const * str);
	int Find(char const * str) const;
	char const * GetString(int id) const;
private:
	HTable _htab;				//char* 	-> 		IDs
	int _offStr[maxStrings];	//IDs   	-> 		offsets
	int _curId;
	StringBuffer _strBuf;		//offsets	->		char*
};

StringTable::StringTable()
:_curId(0){}

int StringTable::ForceAdd(char const * str)
{
	int len = std::strlen(str);
	//space?
	if(_curId == maxStrings || !_strBuf.WillFit(len))
		return idNotFound;

	_offStr[_curId] = _strBuf.GetOffset();

	_strBuf.Add(str);

	_htab.Add(str, _curId);

	++_curId;
	return _curId-1;
}

int StringTable::Find(char const * str) const
{
	list const & pList = _htab.Find(str);

	for(link const * plink = pList.get_head();
		plink != NULL;
		plink = plink->next())
	{
		int id = plink->id();
		int offStr = _offStr[id];
		if(_strBuf.IsEqual(offStr,str))
			return id;
	}
	return idNotFound;
}

char const * StringTable::GetString(int id) const
{
	assert (id>=0);
	assert (id <_curId);

	int offStr =_offStr[id];
	return _strBuf.GetString(offStr);
}


#endif //:define guard end 