#include <iostream>
using namespace std;


class A {
	int x, y;
public:
	A(int xi=0, int yi=0) {
		x = xi; y = yi;
	}
	void afis() {
		cout << x << " " << y;
	}

	A operator+ (A o2);
	friend A operator++ (A &a);
};

A A::operator+(A o2)
{
	A temp;
	temp.x=x+o2.x;
	temp.y=y+o2.y;
	return temp;
}

A A::operator++(A &a)
{
	++a.x; ++a.y;
	return a;
}


int main(void)
{
	A a1(20,30), a2(2,2), a3(0,0);
	a3=++a1+a2;
	a3.afis();
}
