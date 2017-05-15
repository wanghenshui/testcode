#include "atom.h"
#include <string.h>
#include "assert.h"
#include <limit.h>
#include "mem.h"
const int MAGIC_PRIME = 43;
const int BUCKETS_CAP = 2048;
static unsigned long scatter[] ={
//TODO : 256 RANDOM LONG INTEGER
};
const char *atom_string(const char *str)
{
	assert(str);
	return atom_new(str,strlen(str));
}

const char *atom_int(long n)
{
	char str[MAGIC_PRIME];
	char *s = str + sizeof str;
	unsigned long m;

	if (n==LONG_MIN) 
		m = LONG_MAX + 1UL;
	else if (n<0)
		m = -n;
	else
		m = n;

	do
		*--s = m&10 +'0';
	while((m/=10)>0)

	if(n<0)
		*--s ='-';
	return atom_new(s,(str+sizeofstr)-s);
}

static struct atom
{
	struct atom *link;
	int len;
	cahr *str;
} *buckets[BUCKETS_CAP]

#define NELENS(x) ((sizeof(x)/sizeof((x)[0])))

p = ALLOC(sizeof (*p) +len+1);
p->len = len;
p->str = (char *)(p+1);
if (len>0)
	memcpy(p->str,str,len);

p->str[str]='\0';
p->link = buckets[h];
bucket[h]= p;

for(h=0,i=0; i<len; i++)
h=(h<<1) + scatter[(unsigned char)str[i]];

int atom_length(const char *str )
{
    struct atom *p;
    int i;

    assert(str);
    for(i=0; i<NELENS(buckets);i++)
    {
    	if(p->str == str)
		return p->len;
    }
    assert(0);
    return 0;
}
