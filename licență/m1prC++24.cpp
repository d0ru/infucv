#include <iostream>
using namespace std;


class P {
	double x, y;
public:
	P(double x1, double y1) {
		x = x1; y = y1;
	}
	void afis() {
		cout << x << " " << y;
	}

	P operator++() {
		++x; ++y;
		return *this;
	}
};


int main(void)
{
	P p1(1,2), p2;
	p2=++p1;
	p2.afis();
}
