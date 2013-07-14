#include <iostream>
using namespace std;


class B1 {
public:
	B1(){ cout << "B1 "; }
	~B1(){ cout << "DB1 "; }
};

class B2 {
public:
	B2(){ cout << "B2 "; }
	~B2(){ cout << "DB2 "; }
};

class D: public B1, public B2 {
public:
	D():B2(),B1(){ cout << "D "; }
	D(const D &o){ cout <<"CD "; }
	~D(){ cout << "DD "; }
};


int main(void)
{
	D *d1 = new D;
	D *d2 = d1;
	delete d1;
}
