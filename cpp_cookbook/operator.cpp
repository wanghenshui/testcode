#include <iostream>
using namespace std;
class score
{
public:
	score():score_(0) {};
	score(int i):score_(i){}

	score& operator ++ ()
	{
		++score_;
		return *this;
	}

	const score operator ++(int)
	{
		score tmp(*this);
		++(*this);
		return tmp;
	}
	int get_score(){return score_;}
private:
	int score_;
};

int main()
{
	score p(60);
	p++;
	cout << p.get_score()<<endl;
	++p;
	cout << p.get_score()<<endl;
	(++p)++;
	cout << p.get_score()<<endl;
}
