int main(void)
{
	float x = 10;
	int y = 7;
	float t[] = {3,4,1};
	float *q = &x;
	int *r = &y;
	void *p;

	q = t;		// A
	p = t;		// B
	p = &y;		// C
	p = r;		// D
	x = &t[2];	// E
	return 0;
}
