#include <iostream>
using namespace std;


class B {
public:
	//B(){ cout << "B "; }
	//B(const B &o) { cout << "CB "; }
	//~B(){ cout << "DB "; }
	virtual void f() { cout << "B::f() "; }
};

class D1: public B {
public:
	//D1(){ cout << "D1 "; }
	//D1(const D1 &o) { cout << "CD1 "; }
	//~D1(){ cout << "DD1 "; }
	void f() { cout << "D1::f() "; }
};

class D2: public B {
public:
	void f() { cout << "D2::f() "; }
};


int main(void)
{
	int i;
	B b[] = { B(), D1(), D2() };

	for (i=2; i >= 0; i--) { b[i].f(); }
}
