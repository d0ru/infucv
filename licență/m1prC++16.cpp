#include <iostream>
using namespace std;


struct A {
	int x;
	operator double() { return 21.4; }
};


int main(void)
{
	A a;
	a.x = 11;

	cout << (0?3:a) << endl;
	cout << (0?3.0:a);
}
