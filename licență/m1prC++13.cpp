#include <iostream>
using namespace std;


class B {
protected:
	int x;
public:
	B(int x=0){ this->x=x; }
	virtual void f() { x=x+1; }
	void print() { cout<<x<<" "; }
};

class D1: public B {
public:
	void f() { x=x+5; }
};

class D2: public B {
public:
	void f() { x=x+2; }
};


int main(void)
{
	int i;
	B *b[] = { new B(2), new D1(), new D2(), new B };

	for (i=3; i > 0; i--) { (*b[i]).f(); }
	for (i=0; i <= 3; i++) b[i]->print();
}
