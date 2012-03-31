/*
 * Operații cu matricea de muchii a unui graf neorientat.
 *
 * Programul se compilează și se apelează astfel:
 * $ ./lab04_gnmm0 < gnmm3_13.txt
 *   sau
 * $ ./lab04_gnmm0 gnmm3_13.txt
 *
 * "gnmm3_13.txt" este un fișier ce conține pe prima linie numărul muchiilor
 * și pe celelalte linii matricea de muchii (0 sau 1 separate prin spațiu)
 * Obs: fișierul trebuie să se termine cu \n (new line)
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "gnmm.h"
#include "gnmm.cpp"

// operații cu matricea de muchii a unui graf neorientat
int main(int argc, char *argv[])
{
	int i, j, v, nrvarf, nrmuchii;
	FILE *fisier;
	int *mat;

	if (argc < 2) {
		printf("Introduceți numărul muchiilor și matricea de muchii a grafului neorientat:\n");
		mat = citire_gnmm(&nrmuchii);
	} else {
		printf("%d %s %s\n", argc, argv[0], argv[1]);
		fisier = fopen(argv[1], "r");
		if (NULL == fisier) {
			fprintf(stderr, "E: fișierul «%s» nu a putut fi deschis\n", argv[1]);
			return errno;
		}
		mat = fcitire_gnmm(fisier, &nrmuchii);
	}
	if (NULL == mat) {
		fprintf(stderr, "E: memorie insuficientă pentru matricea de muchii\n");
		return errno;
	}

	printf("Matricea de muchii a grafului neorientat:\n");
	afisare_gnmm(mat, nrmuchii);
	putchar('\n');

	nrvarf = nrvarf_gnmm(mat, nrmuchii);		// indexul cel mai mare
	for (i = 1; i <= nrvarf; i++) {
		v = nrvec_gnmm(mat, nrmuchii, i);
		if (0 != v) {
			printf("Nodul «%d» are %d vecini:", i, v);
			afvec_gnmm(mat, nrmuchii, i);
		}
	}
	putchar('\n');

	printf("Graful neorientat are următoarele muchii:");
	for (i = 1; i <= nrvarf; i++)
		for (j = 1; j <= nrvarf; j++)
			if (muchie_gnmm(mat, nrmuchii, i, j))
				printf(" [%d;%d]", i, j);
	putchar('\n');
	return 0;
}
