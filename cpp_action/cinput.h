#ifndef C_INPUT_H
#define C_INPUT_H 1
namespace calc_cl_naive{
const int maxbuf (100);
const int tokNumber (1);
const int tokError (2);

class cinput
{
	int ci_token;
	char ci_buf[maxbuf];
public:
	cinput();
	~cinput();
	int token() const ;
	int number () const ;
};
}		//:end of namespace calc_cl_naive
#endif //: end of C_INPUT_H