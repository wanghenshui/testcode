static inline char* strcpy(char *strDest, const char *strSrc)
{
	assert(strDest && strSrc);

	char *p = strDest;
	while (*p++ = *strSrc++);
	return strDest;
}