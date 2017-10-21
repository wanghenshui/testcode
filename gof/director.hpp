#ifndef __DIRECTOR__HPP
#define __DIRECTOR__HPP

#include "builder.hpp"
class builder;

class director
{
	builder* builder_;
public:
	explicit director(builder* bid) :builder_(bid){}
	~director(){}
	void construct()
	{
		builder_->build_part_a("user-defined");
		builder_->build_part_b("user-defined");
		builder_->build_part_c("user-defined");
	}
};


#endif
