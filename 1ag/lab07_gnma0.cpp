/*
 * Operații cu matricea de adiacență a unui graf neorientat.
 * a[i,j] = 0 dacă NU există o muchie între vârfurile i și j
 *
 * Programul se compilează și se apelează astfel:
 * $ ./lab07_gnma0 < gnma4_3.txt
 *   sau
 * $ ./lab07_gnma0 gnma4_3.txt
 *
 * "gnma4_3.txt" este un fișier ce conține pe prima linie numărul nodurilor
 * și pe celelalte linii matricea de adiacență (0 sau 1 separate prin spațiu)
 * Obs: fișierul trebuie să se termine cu \n (new line)
 */

#include <errno.h>
#include <stdio.h>

#include "gn.h"
#include "gn.c"
#include "gnma.h"
#include "gnma.cpp"

// test pentru algoritmul lui Rosenstiehl
int main(int argc, char *argv[])
{
	int nr, *mat;
	FILE *fisier;

	if (argc < 2) {
		printf("Introduceți numărul vârfurilor și matricea de adiacență a grafului neorientat:\n");
		nr = citire_gnma(&mat);
	} else {
		printf("%d %s %s\n", argc, argv[0], argv[1]);
		fisier = fopen(argv[1], "r");
		if (NULL == fisier) {
			fprintf(stderr, "E: fișierul «%s» nu a putut fi deschis\n", argv[1]);
			return errno;
		}
		nr = fcitire_gnma(fisier, &mat);
	}
	if (NULL == mat) {
		fprintf(stderr, "E: memorie insuficientă pentru matricea de adiacență\n");
		return errno;
	}

	rosenstiehl_gnma(mat, nr, 1);
	return 0;
}
