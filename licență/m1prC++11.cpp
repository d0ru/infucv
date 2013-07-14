#include <iostream>
using namespace std;


class B {
public:
	virtual void f() { cout << "B::f() "; }
	void g() { cout << "B::g() "; }
};

class D1: public B {
public:
	void f() { cout << "D1::f() "; }
	void g() { cout << "D1::g() "; }
};

class D2: public B {
public:
	void g() { cout << "D2::g() "; }
};


int main(void)
{
	int i;
	B *b[] = { new B(), new D1(), new D2() };

	for (i=2; i >= 0; i--) { b[i]->f(); }
	for (i=0; i <= 2; i++) { b[i]->g(); }
}
