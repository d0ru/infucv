#include <stdio.h>

void main()
{
	int a[] = {0, 1, 2, 3, 0, 4, 5, 6};
	int i = 0, x = 9;

	do {
		a[i++] = x;
	} while (i<6&&a[i]);

	printf("a[]:");
	for (i = 0; i < 8; ++i)
		printf(" %d", a[i]);
}
