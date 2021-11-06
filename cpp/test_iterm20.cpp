#include <string>
using std::string;
#include <algorithm>

struct state{
	int population() const{
	return population_}
private:
	int population_;
};
inline bool impl_popless(const state& a,const state& b)
{
	return a.population()<b.population();
}

struct pop_less :public std::binary_function<state,state,bool>
{
	bool operator ()(const state & a ,const state & b)
	{
		return impl_popless(a,b);
	}
};

state Union[50];

int main()
{
	sort(Union,Union+50,pop_less());
	return 0;
}
