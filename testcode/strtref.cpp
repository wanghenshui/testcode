#include <iostream>

struct sysop
{
	char name[26];
	char quote[64];
	int used;
};

const sysop& use(sysop& sysopref)
{
	std::cout << sysopref.name  << std::endl;
	std::cout << sysopref.quote << std::endl;
	sysopref.used++;
	return sysopref	;

}

int main()
{
	sysop looper =
	{
		"rick \"fortran\" looper",
		"i', a goto kind of guy",
		0
	};

	use(looper);
	sysop copycat;
	copycat = use(looper);
	
	std::cout << "looper.used" <<looper.used << std::endl;
	std::cout << "copycat.used" <<copycat.used << std::endl;
	std::cout << "use(looper)" <<use(looper).used << std::endl;
	return 0;
}