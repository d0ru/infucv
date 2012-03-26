/*
 * Operații cu lista de adiacență a unui graf neorientat.
 *
 * Programul se compilează și se apelează astfel:
 * $ ./lab04_gnla0 < gnla3_13.txt
 *   sau
 * $ ./lab04_gnla0 gnla3_13.txt
 *
 * "gnla3_13.txt" este un fișier ce conține pe prima linie numărul nodurilor
 * și pe celelalte linii lista de adiacență a grafului neorientat
 * Obs: fișierul trebuie să se termine cu \n (new line)
 */

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "gn.h"
#include "gn.c"
#include "gnla.h"
#include "gnla.cpp"

// operații cu lista de adiacență a unui graf neorientat
int main(int argc, char *argv[])
{
	int i, j, v, nr;
	FILE *fisier;
	struct nod *liad;

	if (argc < 2) {
		printf("Introduceți numărul vârfurilor și lista de adiacență a grafului neorientat:\n");
		liad = citire_gnla(&nr);
	} else {
		printf("%d %s %s\n", argc, argv[0], argv[1]);
		fisier = fopen(argv[1], "r");
		if (NULL == fisier) {
			fprintf(stderr, "E: fișierul «%s» nu a putut fi deschis\n", argv[1]);
		}
		liad = fcitire_gnla(fisier, &nr);
	}
	if (NULL == liad) {
		fprintf(stderr, "E: memorie insuficientă pentru lista de adiacență\n");
		return errno;
	}

	printf("Lista de adiacență a grafului neorientat:\n");
	afisare_gnla(liad, nr);
	putchar('\n');

	for (i = 1; i <= nr; i++) {
		v = nrvec_gnla(liad, nr, i);
		if (0 != v) {
			printf("Nodul «%d» are %d vecini:", i, v);
			afvec_gnla(liad, nr, i);
		}
	}
	putchar('\n');

	printf("Graful neorientat are următoarele muchii:");
	for (i = 1; i <= nr; i++) {
		for (j = 1; j <= nr; j++) {
			if (muchie_gnla(liad, nr, i, j))
				printf(" [%d;%d]", i, j);
		}
	}
	putchar('\n');
	return 0;
}
