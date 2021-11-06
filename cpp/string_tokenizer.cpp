#include <string>
#include <iostream>

using namespace std;

class stringTokenizer
{
	stringTokenizer(){};
	string delim_;
	string str_;
	int count_;
	int begin_;
	int end_;
public:
	stringTokenizer(const string& s,const char* delim = NULL):str_(s),count_(-1),begin_(0),end_(0)
	{
		if(!delim)
			delim_ = " \f\n\r\t\v";//default to thitespace
		else
			delim_ = delim;
	//point to the first token
		begin_ = str_.find_first_not_of(delim_);
		end_ = str_.find_first_of(delim_,begin_);
	}

	size_t countTokens()
	{
		if(count_ >= 0) return count_;
		//如果已经计算过就直接返回

		string::size_type n=0,i=0;

		for(;;)
		{
			if((i=str_.find_first_not_of(delim_,i))==string::npos)
				break;

			i=str_.find_first_of(delim_,i+1);
			n++;
			if(i==string::npos)
				break;
		}
		return (count_=n);//还可以这样写
	}

	bool has_more_tokens(){	return(begin_!=end_);}

	void next_token(string& s)
	{
		if(begin_!=string::npos && end_!=string::npos)	
		{
			s = str_.substr(begin_,end_-begin_);
			begin_ = str_.find_first_not_of(delim_,end_);
			end_ = str_.find_first_of(delim_,begin_);
		}
		else if(begin_!=string::npos&&end_==string::npos)
		{
			s=str_.substr(begin_,str_.length()-begin_);
			begin_ = str_.find_first_not_of(delim_,end_);
		}
	}
};

int main()
{
	string s = " razzle dazzle giddyup ";

	string tmp;

	stringTokenizer st(s);

	cout << "there are "<<st.countTokens()<<" tokens.\n";

	while(st.has_more_tokens())
	{
		st.next_token(tmp);
		cout<<"token = "<<tmp<<'\n';
	}
}

