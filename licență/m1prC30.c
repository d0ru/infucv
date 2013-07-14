#include <stdio.h>

FILE *f, *g;
int x;

void main()
{
	f=fopen("m1prC30_nr.txt", "r+");
	g=fopen("m1prC30_nr2.txt", "w+");

	while (!feof(f)) {
		fscanf(f, "%d", &x);
		if (x%2==0)
			fprintf(g, "%d \n", x);
	}
	fclose(f);
	fclose(g);
}
