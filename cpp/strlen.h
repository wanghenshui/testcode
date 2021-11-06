static inline unsigned int strlen(const char * s)
{
	assert(s);
	int len = 0;
	while (*s++) len++;
	return len;
}