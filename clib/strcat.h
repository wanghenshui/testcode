inline static char* strcat(char *strDest, const char *strSrc)
{
	assert(strDest && strSrc);

	char *p = strDest;
	while (*p) p++;

	while (*p++ = *strSrc++);
	return strDest;
}