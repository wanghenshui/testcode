#include <cstddef>

template<size_t R, size_t C, typename T>
void init(T a[R][C])
{
	for(size_t i=0; i<R; ++i)
		for(size_t j=0; j<C; ++j)
			a[i][j] = T();
}

template<size_t R, size_t C, typename T>
void init_ref(T (&a)[R][C])
{
	for(size_t i=0; i<R; ++i)
		for(size_t j=0; j<C; ++j)
			a[i][j] = T();
}

int main()
{
	int a[10][20];
	init<10,20>(a);
	init_ref(a);
}
