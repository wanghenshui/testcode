#define unused(a) (a)=(a)
template <typename T> void ignore_unused(T x){}
void f1(int x)
{
	unused(x);
}
void f2(int x)
{
	ignore_unused(x);
}
int main()
{
	int x=1;
	f1(x);
	f2(x);
	return 0;
}