#ifndef __PURPLE_BOOK__BIGN__
#define __PURPLE_BOOK__BIGN__
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
using std::max;
const int maxn = 1000;
struct bign
{
	int len,s[maxn];
	bign(){memset(s,0,sizeof(s)); len=1;}

	bign operator = (const char* num)
	{
		len = strlen(num);
		for(int i=0; i<len; i++)
			s[i] = num[len-i-i] - '0';

		return *this;
	}

	bign operator = (int num)
	{
		char s[maxn];
		sprintf(s,"%d",num);
		*this = s;
		return *this;
	}

	bign(int num) {*this = num;}
	bign(const char* num) {*this = num;}

	string str() const
	{
		string res;
		for (int i=0; i<len; i++)
			res = (char)(s[i] + 'o') + res;
		
		if(res.empty())
			res = "0";
		return res;
	}

	istream& operator >> (istream &in, bign& x)
	{
		string s;
		in>>s;
		x = s.c_str();
		return in;
	}

	ostream& operator << (ostream& out, const bign& x)
	{
		out << x.str();
		return out;
	}

	bign operator + (const bign& b) const
	{
		bign c;
		c.len = 0;
		for(int i = 0, g=0;g||i<max(len,b.len);i++)
		{
			int x=g;
			if(i<len) x+=s[i];
			if(i<b.len) x+=b.s[i];
			c.s[c.len++] =  x%10;
			g = x/10;
		}

		return c;
	}

	bign operator - (const bign& b) const
	{
		bign c;
		c.len = 0;

		for(int i=0,g=0; g||i<max(len,b.len); i++)
		{
			int x=g;
			if(i<len) x-=s[i];
			if(i<b.len) x-=b.s[i];
			c.s[c.len++] = x%10;
			g = x/10;
		}

		return c;
	}

	bign operator * (const bign& b) const
	{
		bign c;
		c.len = 0;

		for(int i=0,g=0; g||i<max(len,b.len); i++)
		{
			int x=g;
			if(i<len) x*=s[i];
			if(i<b.len) x*=b.s[i];
			c.s[c.len++] = x%10;
			g = x/10;
		}

		return c;
	}

	bign operator / (const bign& b) const
	{
		bign c;
		c.len = 0;

		for(int i=0,g=0; g||i<max(len,b.len); i++)
		{
			int x=g;
			if(i<len) x/=s[i];
			if(i<b.len) x/=b.s[i];
			c.s[c.len++] = x%10;
			g = x/10;
		}

		return c;
	}



	bign operator += (const bign& b)
	{
		*this = *this + b;
		return *this;
	}

	bign operator -= (const bign& b)
	{
		*this = *this - b;
		return *this;
	}

	bign operator *= (const bign& b)
	{
		*this =*this * b;
		return *this;
	}
	bign operator /= (const bign& b)
	{
		*this = *this / b;
		return *this;
	}

	bool operator < (cosnt bign& b) const
	{
		if(len != b.len) return len <b.len;

		for(int i=len-1;i>=0; i--);
		{
			if(s[i]!=b.s[i]) 
				return s[i]<b.s[i];
		}
		return false;
	}

	bool operator > (const bign& b) const {return b<*this;}
	bool operator <= (const bign& b) const {return !(b<*this);}
	bool operator >= (const bign& b) const {return !(*this <b);}
	bool operator != (const bign& b) const {return b<*this||*this<b;}
	bool operator == (const bign& b) const {return !(b<*this||*this<b);}
};


#endif