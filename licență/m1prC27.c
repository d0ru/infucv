#include <stdio.h>

void X(char *a, char *b)
{
	FILE *f, *g;
	char s[255];

	f = fopen(a, "a");
	g = fopen(b, "r");
	while (!feof(g)) {
		fgets(s, 255, g);
		fputs(s, f);
	}
	fclose(f);
	fclose(g);
}

int main(void)
{
	char f1[] = "f1.txt";
	char f2[] = "f2.txt";

	X(f1, f2);
	return 0;
}
