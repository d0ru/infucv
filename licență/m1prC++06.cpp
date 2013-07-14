#include <iostream>
using namespace std;


class Test {
	int n;

public:
	Test(int x):n(x){}
	int f(int n, int &x, int *p)
	{
		n = this->n;
		x = n++;
		*p = this->n + n;
		return n;
	}
};


int main(void)
{
	Test t(2);
	int n=6, x=0x10, p=1;

	cout << t.f(n,x,&p) << " ";
	cout << n << " " << x << " " << p;
}
