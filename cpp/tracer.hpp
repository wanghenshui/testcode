#include <iostream>
class sort_tracer{
	
	int value;
	int generation;
	static long n_created;
	static long n_destroyed;
	static long n_assigned;
	static long n_compared;
	static long n_max_live;
	static void update_max_live()
	{
		if(n_created-n_destroyed>n_max_live)
			n_max_live = n_created - n_destroyed;
	}

public:
	//static 成员函数是全局的，没有this，所以不能用const修饰
	static long creations() {
		return n_created;
	}

	static long destructions() {
		return n_destroyed;
	}

	static long assignments() {
		return n_assigned;
	}

	static long comparisons() {
		return n_compared;
	}

	static long max_live() {
		return n_max_live;
	}



	sort_tracer(int v=0):value(v),generation(1)
	{
		++n_created;
		update_max_live();
		std::cerr<<"SortTracer # "
			 <<n_created<<" created generation (total : "
			 <<n_created-n_destroyed<<")\n";
	}

	sort_tracer(const sort_tracer& s):value(s.value),generation(s.generation+1)
	{
		++n_created;
		update_max_live();
		std::cerr<<"SortTracer # "
			 <<n_created<<" created generation (total : "
			 <<n_created-n_destroyed<<")\n";
	}
	
	~sort_tracer()
	{
		++n_destroyed;
		update_max_live();
		std::cerr<<"SortTracer generation "
			 <<generation<<" destoryed (total : "
			 <<n_created-n_destroyed<<")\n";
	}

	sort_tracer& operator=(const sort_tracer& b)
	{
		++n_assigned;
		std::cerr<<"SortTracer assignment # "
			 <<n_assigned<<"( generation "
			 <<generation<<" = : "
			 <<b.generation<<")\n";
		value = b.value;
		return *this;
	}

	friend bool operator <(sort_tracer const & a, sort_tracer const & b)
	{
		++n_compared;
		std::cerr<<"SortTracer comparison # "
			 <<n_compared<<"( generation "
			 <<a.generation<<" < "
			 <<b.generation<<")\n";
		return a.generation<b.generation;
	}

	int val() const
	{
		return value;
	}
};
