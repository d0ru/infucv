/*
 * Operații cu matricea de adiacență a unui graf neorientat.
 * a[i,j] = 0 dacă NU există o muchie între vârfurile i și j
 *
 * Programul se compilează și se apelează astfel:
 * $ ./lab04_main0 < gn3_13.txt
 *
 * "gn3_13.txt" este un fișier ce conține pe prima linie numărul nodurilor și
 * pe celelalte linii matricea de adiacență (0 sau 1 separate prin spațiu)
 * Obs: fișierul trebuie să se termine cu \n (new line)
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "gnma.h"
#include "gnma.c"

// operații cu matricea de adiacență a unui graf neorientat
int main(void)
{
	int i, j, v, nr;
	int *mat;

	printf("Introduceți numărul vârfurilor și matricea de adiacență a grafului neorientat:\n");
	mat = citire_gnma(&nr);
	if (NULL == mat) {
		fprintf(stderr, "E: memorie insuficientă pentru matricea de adiacență\n");
		return errno;
	}

	printf("Matricea de adiacență a grafului neorientat:\n");
	afisare_gnma(mat, nr);
	putchar('\n');

	for (i = 1; i <= nr; i++) {
		v = nrvec_gnma(mat, nr, i);
		if (0 != v) {
			printf("Nodul «%d» are %d vecini:", i, v);
			afvec_gnma(mat,nr,i);
		}
	}
	putchar('\n');

	printf("Graful neorientat are următoarele muchii:");
	for (i = 1; i <= nr; i++) {
		for (j = 1; j <= nr; j++) {
			if (muchie_gnma(mat,nr,i,j))
				printf(" [%d;%d]", i, j);
		}
	}
	putchar('\n');
	return 0;
}
