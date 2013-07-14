//#include <conio.h>
#include <stdio.h>

FILE *f;
int i=0, a[10]={20,11,17,4,5,10,14,34,23,11};

void main()
{
	f=fopen("numere.txt", "w");
	for (i=0; i<5; i++) {
		if (a[i]%2!=0)
			fprintf(f,"%d \n",a[i]);
	}
	fclose(f);
}
