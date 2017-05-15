#ifndef __ATOM__
#define __ATOM__

extern 		 int atom_length(const char *str);
extern const char *atom_new(const char *str, int len);
extern const char *atom_string(const char *str);
extern const char *atom_int(long n);

#endif
