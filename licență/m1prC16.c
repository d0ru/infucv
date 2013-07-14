#include <stdio.h>

void main()
{
	int array[3][] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
	int s = 0, i, j;

	for (i = 0; i < 3; ++i) {
		for (j = 2; j < 3; j++) {
			s += array[i][j];
		}
	}
	printf("%d", s);
}
