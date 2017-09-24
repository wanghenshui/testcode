#ifndef __string_buffer__
#define __string_buffer__

#include <cstring> // for strcmp

const int maxBufSize = 500;

class StringBuffer
{
	char _buf[maxBufSize];
	int _curOffset;
public:
	 StringBuffer()
	 :_curOffset(0){}
	 bool WillFit (int len) const
	 {
	 	return _curOffset + len +1 < maxBufSize;
	 }
	 void Add(char const * str)
	 {
	 	// std::strcpy(_buf + _curOffset, str)
	 	std::strcpy(&_buf[_curOffset], str);
	 	_curOffset += std::strlen(str) + 1;
	 }

	 int GetOffset() const
	 {
	 	return _curOffset;
	 }
	 bool IsEqual(int offStr, char const * str) const
	 {
	 	//char const * strStored = _buf + offStr
	 	char const * strStored = &_buf[offStr];
	 	//if same strcmp return 0 
	 	return std::strcmp(str,strStored) == 0;
	 }
	 char const * GetString(int offStr) const
	 {
	 	//return _buf + offStr
	 	return &_buf[offStr];
	 }
	//~ StringBuffer();
	
};


#endif //:define guard end