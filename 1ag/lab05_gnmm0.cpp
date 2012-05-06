/*
 * Operații cu matricea de muchii a unui graf neorientat.
 *
 * Programul se compilează și se apelează astfel:
 * $ ./lab05_gnmm0 < gnmm3_13.txt
 *   sau
 * $ ./lab05_gnmm0 gnmm3_13.txt
 *
 * "gnmm3_13.txt" este un fișier ce conține pe prima linie numărul nodurilor
 * și pe celelalte linii matricea de adiacență (0 sau 1 separate prin spațiu)
 * Obs: fișierul trebuie să se termine cu \n (new line)
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "gn.h"
#include "gn.c"
#include "gnmm.h"
#include "gnmm.cpp"

// operații cu matricea de muchii a unui graf neorientat
int main(int argc, char *argv[])
{
	int i, nrvarf, nrmuchii;
	FILE *fisier;
	int *mat;

	if (argc < 2) {
		printf("Introduceți numărul muchiilor și matricea de muchii a grafului neorientat:\n");
		nrmuchii = citire_gnmm(&mat);
	} else {
		printf("%d %s %s\n", argc, argv[0], argv[1]);
		fisier = fopen(argv[1], "r");
		if (NULL == fisier) {
			fprintf(stderr, "E: fișierul «%s» nu a putut fi deschis\n", argv[1]);
			return errno;
		}
		nrmuchii = fcitire_gnmm(fisier, &mat);
	}
	if (NULL == mat) {
		fprintf(stderr, "E: memorie insuficientă pentru matricea de muchii\n");
		return errno;
	}

	nrvarf = nrvarf_gnmm(mat, nrmuchii);		// indexul cel mai mare
	for (i = 1; i <= nrvarf; i++) {
		printf("Vizitare în lățime GNMM de la vârful «%d»:\n", i);
		vizlat_gnmm(mat, nrmuchii, i);
		printf("Vizitare în adâncime GNMM de la vârful «%d»:\n", i);
		vizad_gnmm(mat, nrmuchii, i);
		putchar('\n');
	}
	return 0;
}
