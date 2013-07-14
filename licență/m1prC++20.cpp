#include <iostream>
using namespace std;


class A {
private:
	int x, y;
public:
	A() { x=0; y=0; }
	A(int xi, int yi) {
		x = xi; y = yi;
	}
	void afis() {
		cout << x " " << y;
	}
};


int main(void)
{
	A A1,A2(10,20);
	A1.afis();
	A2.afis();
}
