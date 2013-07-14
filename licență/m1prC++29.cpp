#include <iostream>
using namespace std;


class B {
	int a;
protected:
	int b;
public:
	int c;
	void set_a(int x){a = x;}
	void set_b(int y){b = y;}
	void set_c(int z){c = z;}
};

class D: protected B {
	int d;
public:
	void set_b(int y){b = y;}
	void set_c(int z){c = z;}
};


int main(void)
{
	D o;

	//o.a = 1;		// (1)
	//o.B::set_a(2);		// (2)
	//o.b = 3;		// (3)
	//o.B::set_b(4);		// (4)
	o.c = 5;		// (5)
	o.set_c(5);
}
