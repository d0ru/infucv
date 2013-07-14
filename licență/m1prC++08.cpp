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
	static int idGen;
	int id;
public:
	D():B2(),B1(){ id=idGen++;cout << "D(" << id << ") "; }
	D(const D &o){ id=idGen++;cout << "CD(" << id << ") "; }
	~D(){ cout << "DD "; }
};
int D::idGen = 0;


int main(void)
{
	D d1;
	D d2=d1;
}
