#include <stdio.h>

void f(int n, int x, int v[])
{
	int i, p;

	p = n;
	for (i = 0; i < n; i++)
		if (v[i] == x)
			p = i;

	for (i = p+1; i < n; i++)
		v[i-1] = v[i];

	for (i = 0; i < n-1; i++)
		printf("%3d", v[i]);
	printf("\n");
}

int main(void)
{
	int vA[] = { 5, 6, 2, 7, 1 };
	int vB[] = { 2, 1, 3, 1, 4 };

	printf("vA[]:");
	f(5, 3, vA);		// A
	printf("vB[]:");
	f(5, 1, vB);		// B
	return 0;
}
