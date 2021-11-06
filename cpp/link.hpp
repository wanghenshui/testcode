#ifndef __link__
#define __link__

class link
{
	link* _pNext;
	int _id;
public:
	link(link* pNext, int id)
	:_pNext(pNext),_id(id){}

	link* next() const{return _pNext;}
	int id() const {return _id;}
	//~link();	
};

class list
{
	link * _pHead;
public:
	list():_pHead(0){}
	~list();
	void add (int id);
	link const * get_head() const {return _pHead;}
};

void list::add(int id)
{
	//prepending
	link * plink = new link(_pHead,id);
	_pHead = plink;
}
list::~list()
{
	while(_pHead!=NULL)
	{
		link * ptmp = _pHead;
		_pHead = _pHead->next();
		delete ptmp;
	}
}

#endif //:define guard end