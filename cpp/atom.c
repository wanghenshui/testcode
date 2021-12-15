#include "atom.h"
#include <string.h>
#include "assert.h"
#include <limit.h>
#include "mem.h"
const int MAGIC_PRIME = 43;
const int BUCKETS_CAP = 2048;
static unsigned long scatter[] =
{
	65714908,710034633,879421408,1458420996,1062670499,85805642,278328010,1986580714,246245022,315972112,
	1531676094,1466966614,1604246106,620509511,58499109,2089588113,1213923921,1400589356,32539395,1908989630,
	741723270,718341638,199680880,1567493775,1375030317,1100973788,1569077236,375035952,1357490110,1991935225,
	1357255662,1423205018,554486210,89193423,734142366,1617156709,174999065,1012470377,1456253775,421244088,
	1328442489,840446221,1888210702,785204948,1460955733,1946709811,727309413,527396006,1199815519,759848808,
	288901988,1941538790,1478190446,488582869,1361548917,705737116,1589556657,783142505,1080773068,799563119,
	627594082,290545083,75284490,1182080293,379738506,809426856,651753354,554737571,1821897233,2108007130,
	975981659,1002856075,800969703,716708714,1788061023,114441788,515934877,367886788,641837795,1715750397,
	1127735596,930739783,1509805539,458442394,1419322652,723870808,1164179510,861395661,1507013314,97468931,
	1660958781,2134607396,388014014,1736243271,1169204041,767752520,398186479,1820957396,1322490091,72600065,
	
	1781480878,150988103,1075456140,434966933,867696817,716033515,549408722,1383631694,1083920303,1191246517,
	951898443,64172251,2121986300,314220334,522614645,1393825305,1038091143,1686794156,107737318,397620809,
	1784263087,1768696099,384744557,24793453,1357455722,1553948599,792545973,1755642202,1227422347,2115036064,
	1828242267,861419577,118540519,756214759,1296386510,986237336,1472248274,1845795232,222385383,408684929,
	889558101,1174283826,472857180,864060754,1488504161,995471825,110402411,379111656,534782333,218139729,
	776732465,171561772,1986835829,1161477022,196355225,1196807903,567941973,988901198,804966457,1795364320,
	956453615,485725076,509300249,1074994134,1241939835,1805686760,2061231471,566704461,1503998344,136133206,
	975389390,246072798,1310417032,1448246570,1110133552,651437545,296234748,1220535963,1030549201,831017081,
	1438675692,1807281666,1002578854,1278027873,821275041,1198934079,327352129,1389217014,40351630,1132318586,
	1037097687,996805245,1618043663,1546397936,2071799379,712499850,1204601048,1985547202,1279204312,561115745,

	2121680408,107110054,807188543,1284613793,1555356625,1917322095,1936051338,1851591373,990374410,819116892,
	535124806,281566454,478914910,1537703660,1559594328,1300189951,589154092,1886946457,541923318,629505722,
	871781395,1579021005,1626310967,342341410,977935293,1550626698,1054841261,35052694,1388690253,186561925,
	596168439,1362887013,293671979,1403356982,500017158,1849028604,1173195429,288584849,1553136329,16086191,
	1107701741,2088261136,297652645,1586616651,1478481148,1857246973,739322955,2067635240,1596709782,1281246273,
	549657314,321007530,712783630,28484633,663348940,1690718923
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