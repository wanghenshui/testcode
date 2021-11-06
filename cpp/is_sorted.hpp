//operator <
//std::is_sorted c++11
template <typename ITER>
bool is_sorted(ITER first,ITER last)
{
	if(first == last) return true;

	ITER next = first;

	while(++next!=last)
	{
		if(*next<*first)
			return false;
		++first;
	}
	return true;
}