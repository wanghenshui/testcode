#include "algostuff.hpp"

class mean_value
{
    private:
	    long num;
	    long sum;
    public:
	    mean_value():num(0),sum(0){}

	    void operator() (int elem)
	    {
	    	num++;
		sum+=elem;
	    }

	    operator double (){	return static_cast<double>(sum) / static_cast<double>(num);}
};

int main()
{
    std::vector<int> coll;
    INSERT_ELEMENTS(coll,1,8);

    double mv = std::for_each(coll.begin(),coll.end(),mean_value());
    std::cout<<mv<<std::endl;
}

