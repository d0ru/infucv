#include <stdio.h>

int main(void)
{
	int a[6] = { 1, 2, 3, 4, 5, 6};
	int i = 2;
	printf("a[i] = %d\n", a[i]);
	printf("*(a+i) = %d\n", *(a+i));
	printf("*(i+a) = %d\n", *(i+a));
	printf("i[a] = %d\n", i[a]);
	return 0;
}
