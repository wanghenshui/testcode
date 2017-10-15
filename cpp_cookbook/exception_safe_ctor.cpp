#include <iostream>
#include <stdexcept>

using namespace std;

struct device{
	device(int devno){
		if(devno == 2){
			throw runtime_error("big problem");
		}
	}
	~device(){}
};

class broker{
	broker();
	device * dev1_;
	device * dev2_;
public:
	broker(int devno1, int devno2):dev1_(nullptr),dev2_(nullptr){
		try{
			dev1_ = new device(devno1);
			dev2_ = new device(devno2);
		}
		catch(...){
			delete dev1_;
			throw;
		}
	}
	~broker(){
		delete dev1_;
		delete dev2_;
	}
};

int main(){
	try{
		broker b(1,2);
	}
	catch(exception& e){
		cerr<<e.what()<<endl;
	}
}
