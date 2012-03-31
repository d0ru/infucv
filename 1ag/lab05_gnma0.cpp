/*
 * Operații cu matricea de adiacență a unui graf neorientat.
 * a[i,j] = 0 dacă NU există o muchie între vârfurile i și j
 *
 * Programul se compilează și se apelează astfel:
 * $ ./lab05_gnma0 < gnma3_13.txt
 *   sau
 * $ ./lab05_gnma0 gnma3_13.txt
 *
 * "gnma3_13.txt" este un fișier ce conține pe prima linie numărul nodurilor
 * și pe celelalte linii matricea de adiacență (0 sau 1 separate prin spațiu)
 * Obs: fișierul trebuie să se termine cu \n (new line)
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "gnma.h"
#include "gnma.cpp"

// operații cu matricea de adiacență a unui graf neorientat
int main(int argc, char *argv[])
{
	int i, nr;
	FILE *fisier;
	int *mat;

	if (argc < 2) {
		printf("Introduceți numărul vârfurilor și matricea de adiacență a grafului neorientat:\n");
		mat = citire_gnma(&nr);
	} else {
		printf("%d %s %s\n", argc, argv[0], argv[1]);
		fisier = fopen(argv[1], "r");
		if (NULL == fisier) {
			fprintf(stderr, "E: fișierul «%s» nu a putut fi deschis\n", argv[1]);
			return errno;
		}
		mat = fcitire_gnma(fisier, &nr);
	}
	if (NULL == mat) {
		fprintf(stderr, "E: memorie insuficientă pentru matricea de adiacență\n");
		return errno;
	}

	for (i = 1; i <= nr; i++) {
		printf("Vizitare în lățime GNMA de la vârful «%d»:\n", i);
		vizlat_gnma(mat, nr, i);
		printf("Vizitare în adâncime GNMA de la vârful «%d»:\n", i);
		vizad_gnma(mat, nr, i);
		putchar('\n');
	}
	return 0;
}
