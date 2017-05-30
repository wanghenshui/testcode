#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdarg>
#include <fstream>

using namespace std;

class logger
{
    bool _bOn;
    bool _bForceFlush;
    string _sMessage;
    string _sFileName;
    ofstream _file;

public:
    logger(void)
    {
    	_bOn = false;
	_bForceFlush = false;
    }
    
    logger(const char * strfFileName)
    {
    	_sFileName = strfFileName;
	_bOn = false;
	_bForceFlush = false;
    }
	
    logger(const logger& aCopy)
    {
    	_sFileName = aCopy._sFileName;
	setOn( aCopy._bOn);
	_bForceFlush = aCopy._bForceFlush;

    }

    virtual ~logger()
    {
    	Flush();
	if (_bOn)
	{
	    _file.close();
	}
    }

    void setOn(bool flag)
    {
    	_bOn = flag;
	if(_bOn) 
	    _file.open(_sFileName.c_str());
    }

    bool getOn(){return _bOn;}

    void setForceFlush(bool flag) {_bForceFlush = flag;}

    bool getForchFlush() {return _bForceFlush;}

    void setFileName(const char *str) {_sFileName = str;}

    string getFileName(){return _sFileName;}

    void log(const char *strMessage)
    {
    	_sMessage+= strMessage;
	_sMessage += '\n';
	if(_bForceFlush)
		Flush();
    }

    void log_string(chonst char *fmt,...)
    {
    	char szBuffer[256];
	va_list marker;

	va_start(marker,fmt);

	vsprintf(szBuffer,fmt,marker);

	_sMessage==szBuffer;
	_sMessage+='\n';
	
	if(_bForceFlush) Flush();
    }

    void Flush()
    {
    	if(_bOn)
		_file <<_sMessage <<endl;
	_sMessage="";
    }
};

