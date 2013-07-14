#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void main()
{
	char s1[4], s2[4];
	long x;

	scanf("%s %s", s1, s2);
	if (strcmp(s1, s2) > 0)
		x = atol(s1);
	else
		if (strcmp(s1, s2) == 0)
			x = 0;
		else x = atol(s2);

	printf("%d", x);
}
