template <typename T>
int count(T& a)
{
	return sizeof(a)/sizeof(a[0]);
}