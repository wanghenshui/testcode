#ifndef __PRODUCT__TO__BUILD__HPP
#define __PRODUCT__TO__BUILD__HPP

class product
{
public:
	product(){}
	~product(){}

	void produce_part();
};

class product_part
{
public:
	product_part(){}
	~product_part(){}
	product_part* build_part(){}
};

#endif
