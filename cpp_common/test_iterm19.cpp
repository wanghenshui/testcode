#include <memory>
using std::auto_ptr;

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;
struct action
{
	virtual ~action();
	virtual void operator()() = 0;
	virtual action * clone() const = 0;
};

class button
{
	string label_;
	action *action_;
public:
	button(const string & label) :label_(label_),action_(nullptr){}

	void set_action(const action * new_action)
	{
		delete action_;
		action_ = new_action->clone();
	}

	void click() const
	{
		if(action_) (*action_)();
	}
};

class play_music : public action
{
	string song_;
public:
	play_music(const string& song):song_(song){}
	void operator()();
};


int main()
{
	button *b = new button("music button");
	auto_ptr<play_music > song(new play_music("blahblahblah"));
	b->set_action(song.get());
	return 0;
}

