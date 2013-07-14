void main(void)
{
	int a[2] = {1,2};
	int b[3] = {3};
	int* x = a;
	int* const y = a;
	b = x;
	b = y;
}
