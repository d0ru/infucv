/*
 * Operații pe lista de muchii a unui graf neorientat.
 * Într-o matrice 2x|E| se păstrează lista de muchii.
 *
 * Lista de muchii se dă în felul următor:
 *   u1 u2 ... um
 *   v1 v1 ... vm
 * unde (u1,v1), (u2,v2),.. (um,vm) sunt toate muchiile grafului neorientat.
 *
 * Programul se compilează și se apelează astfel:
 * $ ./lab05_gnlm0 < gnlm3_13.txt
 *   sau
 * $ ./lab05_gnlm0 gnlm3_13.txt
 *
 * "gnlm3_13.txt" este un fișier ce conține pe prima linie numărul nodurilor
 * și pe celelalte linii matricea de adiacență (0 sau 1 separate prin spațiu)
 * Obs: fișierul trebuie să se termine cu \n (new line)
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "gnlm.h"
#include "gnlm.cpp"

// operații cu lista de muchii a unui graf neorientat
int main(int argc, char *argv[])
{
	int i, nrvarf, nrmuchii;
	FILE *fisier;
	int *mat;

	if (argc < 2) {
		printf("Introduceți numărul muchiilor și matricea de muchii a grafului neorientat:\n");
		mat = citire_gnlm(&nrmuchii);
	} else {
		printf("%d %s %s\n", argc, argv[0], argv[1]);
		fisier = fopen(argv[1], "r");
		if (NULL == fisier) {
			fprintf(stderr, "E: fișierul «%s» nu a putut fi deschis\n", argv[1]);
		}
		mat = fcitire_gnlm(fisier, &nrmuchii);
	}
	if (NULL == mat) {
		fprintf(stderr, "E: memorie insuficientă pentru matricea de muchii\n");
		return errno;
	}

	nrvarf = nrvarf_gnlm(mat, nrmuchii);		// indexul cel mai mare
	for (i = 1; i <= nrvarf; i++) {
		printf("Vizitare în lățime GNLM de la vârful «%d»:\n", i);
		vizlat_gnlm(mat, nrmuchii, i);
		printf("Vizitare în adâncime GNLM de la vârful «%d»:\n", i);
		vizad_gnlm(mat, nrmuchii, i);
		putchar('\n');
	}
	return 0;
}
