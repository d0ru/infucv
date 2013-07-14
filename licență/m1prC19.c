#include <stdio.h>

void main()
{
	int v[20], i, n, D;

	printf("n = ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
		v[i] = i%2?i:-i;

	printf("v[]:");
	for (i=0; i<n; i++)
		printf(" %d", v[i]);
	printf("\n");

	for (D=1, i=0; i<n; D*=v[i++]);
		D++;
	printf("D: %d", D);
}
