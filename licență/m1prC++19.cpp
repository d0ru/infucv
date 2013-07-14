#include <iostream>
using namespace std;


struct A {
	virtual int f(int x = 5) {
		return x * 2;
	}
};

struct B: public A {
	int f(int x = 10) {
		return x * 3;
	}
};


int main(void)
{
	A* a = new B;
	cout << a->f();
}
