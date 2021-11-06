#ifndef __BUILEDR__HPP
#define __BUILEDR__HPP

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include "product_to_build.hpp"
class product;

class builder
{
public:
	virtual ~builder(){}
	virtual void build_part_a(const string& msg)=0;
	virtual void build_part_b(const string& msg)=0;
	virtual void build_part_c(const string& msg)=0;
	virtual product* get_product()=0;
protected:
	builder(){}
};

class concrete_builder :public builder
{
public:
	concrete_builder(){}
	~concrete_builder(){}
	
	void build_part_a(const string& msg);
	void build_part_b(const string& msg);
	void build_part_c(const string& msg);
	product* get_product();
};

void concrete_builder::build_part_a(const string& msg)
{
	cout<<"build step A: "<<msg<<endl;
}
 
void concrete_builder::build_part_b(const string& msg)
{
	cout<<"build step B: "<<msg<<endl;
}

void concrete_builder::build_part_c(const string& msg)
{
	cout<<"build step C: "<<msg<<endl;
}

product * concrete_builder::get_product()
{
	build_part_a("pre-defined");
	build_part_b("pre-defined");
	build_part_c("pre-defined");
	return new product();
}


#endif
