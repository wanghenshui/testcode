#include <vector>
#include <algorithm>
template<typename Msg>
struct helper;

template<typename Msg>
class subject;

template<typename Msg>
class observer
{
	friend struct helper<Msg>;
protected:
	observer() :psbj_(NULL)
	{}
public:
	virtual ~observer()
	{
		if (psbj_)
			psbj_->detach(*this);
	}

	virtual void update(const Msg&) = 0;
private:
	subject<Msg>* psbj_;
};

template<typename Msg>
class subject
{
	friend struct helper<Msg>;
public:
	virtual ~subject()
	{
		typename std::vector<observer<Msg>*>::iterator begin = obsvrvec_.begin();
		typename std::vector<observer<Msg>*>::iterator end = obsvrvec_.end();

		for (; begin != end; ++begin)
			helper<Msg>::attachtosubject(NULL, *begin);
	}
	void attach(observer<Msg>& rhs) //register
	{
		obsvrvec_.push_back(&rhs);
		helper<Msg>::attachtosubject(this, &rhs);
	}

	void detach(observer<Msg>& rhs) //unregister
	{
		typename std::vector<observer<Msg>*>::iterator matched = find(obsvrvec_.begin(), obsvrvec_.end(), &rhs);
		if (matched != obsvrvec_.end())
			obsvrvec_.erase(matched);
	}

	void notify() //notify all observers
	{
		typename std::vector<observer<Msg>*>::iterator begin = obsvrvec_.begin();
		typename std::vector<observer<Msg>*>::iterator end = obsvrvec_.end();

		for (; begin != end; ++begin)
			(*begin)->update(message_);
	}

protected:
	Msg& message()
	{
		return message_;
	}

	const Msg& message() const
	{
		return message_;
	}

	void message(const Msg& rhs)
	{
		message_ = rhs;
	}
private:
	Msg message_;
	std::vector<observer<Msg>*> obsvrvec_;
};

template<typename Msg>
struct helper
{
	static void attachtosubject(subject<Msg>* sbj, observer<Msg>* obsv)
	{
		obsv->psbj_ = sbj;
	}
};
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;
class ConcreteObserver1 :public observer<string>
{
public:
	void update(const string& message)
	{
		cout << message << endl;
	}
};

class ConcreteObserver2 :public observer<string>
{
public:
	void update(const string& message)
	{
		copy(message.rbegin(), message.rend(), ostream_iterator<string::value_type>(cout));
		cout << endl;
	}
};

class ConcreteSubject :public subject<string>
{
public:
	void set(const string& str)
	{
		message(str);
	}
};

int main()
{
	ConcreteSubject subject;
	ConcreteObserver1 o1;
	ConcreteObserver2 o2;
	subject.attach(o1);
	subject.attach(o2);
	subject.set("show me the money");
	subject.notify();
}