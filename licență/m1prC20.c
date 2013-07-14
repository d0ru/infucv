#include <stdio.h>

void main()
{
	int v[]={0, 1, 2, 3, 4, 5, 6, 0};
	int i=0, n=0;

	do{
		if (i == v[i])
			n++;
	}while (i<6 && v[i++]);
	printf("n: %d", n);
}
