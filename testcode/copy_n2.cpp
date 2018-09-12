#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename InputIter, typename OutputIter,typename Size>	
inline
OutputIter copy_n1(InputIter first,Size n, OutputIter target)
{
	for ( ; n > 0; --n, ++first, ++target )
		*target = *first;
	return target;
}

template<typename InputIter, typename OutputIter,typename Size>	
inline
OutputIter copy_n2(InputIter first,Size n, OutputIter target)
{
	while(n--)
			*target++ = *first++;
	return target;
}
int main()
{    
    vector<int>  a={1,2,3,4,5};
    vector<int>  b(5,0);
    vector<int>  c(5,0);
    
    copy_n1(a.begin(),a.size(),b.begin());
    copy_n2(a.begin(),a.size(),c.begin());
    
    for(auto v1 : b)
        cout<< v1<<" ";
    cout<<"\n";
    for(auto v1 : c)
        cout<< v1<<" ";
    cout<<"\n";

}