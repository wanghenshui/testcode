#include "atom.h"
#include <string.h>
#include "assert.h"
#include <limit.h>

const int MAGIC_PRIME = 43;
const int BUCKETS_CAP = 2048;

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