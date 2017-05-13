template <typename T>
T inner_product(T a[],T b[],T n)
{
	T sum=0;
	for (int i = 0; i != n; i++)
	{
		sum += a[i]*b[i];
	}
	return sum;
}