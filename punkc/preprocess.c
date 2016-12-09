#include <stdio.h>
#include <math.h> //NAN

#define SET_LIST(name, ...)			\
	double *name ## _list = (double []){__VA_ARGS__,NAN};	\
	int name ## _len = 0;					\
	for(name ## _len =0;!isnan(name ## _list[name ## _len]); )\
		name ## _len ++;				\


int main()
{
	SET_LIST(items,1,2,4,8);
	double sum = 0;

	for(double *ptr= items_list; !isnan(*ptr); ptr++)
		sum += *ptr;
	printf("total for items list: %g\n",sum);


	#define LEN(in) in ## _len

	sum = 0;
	SET_LIST(next_set,-1,2.2,4.8,0.1);
	for(int i=0; i<LEN(next_set); i++)
		sum += next_set_list[i];

	printf("total for net set list: %g\n",sum);

}

