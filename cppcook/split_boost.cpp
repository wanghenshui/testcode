#include <iostream>
#include <string>
#include <list>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

int main()
{
	string s="one,two,three,four";

	list<string> res;

/*
tp<typename Seq,typename Coll,typename Pred>
Seq& split(Seq& s,Coll& c, Pred p,token_compress_mode_type e = token_compress_off)

*/
	split(res,s,is_any_of(","));
/*

is_any_of
bool b=is_any_of("abc")('a'); //true

*/

	for(auto i:res)
		cout<<i<<endl;

	bool b=is_any_of("abc")('a');
	cout<<b<<endl;
}