#ifndef __hash_table__
#define __hash_table__
#include <cassert>
#include "link.hpp"

const int sizeHTable = 127;//must be prime

class HTable
{
	int hash (char const * str) const;
	list _alist[sizeHTable];
public:
	 //HTable();
	//~ HTable();
	list const & Find(char const * str) const;
	void Add (char const * str, int id);
};

list const & HTable::Find(char const * str) const
{
	int i = hash(str);
	return _alist[i];
}

void HTable::Add(char const * str, int id)
{
	int i=hash(str);
	_alist[i].add(id);
}

int HTable::hash(char const * str) const
{
	//Can not empty 
	assert(str!=0 && str[0]!= NULL);
	unsigned h = str[0];
	for (int i = 0; str[i]!=NULL; ++i)
		h=(h<<4)+str[i];
	return h%sizeHTable;
}



#endif // define guard end