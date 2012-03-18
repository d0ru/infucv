/*
 * Operații cu matricea de adiacență a unui graf neorientat.
 * a[i,j] = 0 dacă NU există o muchie între vârfurile i și j
 *
 * Programul se compilează și se apelează astfel:
 * $ ./lab04_matrice_adiacenta < graf1.in
 *
 * "graf1.in" este un fișier text ce conține pe prima linie numărul nodurilor
 * și pe celelalte linii matricea de adiacență (0 sau 1 separate prin spațiu)
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// citire de la STDIN
// nrvarf = |V|, numărul vârfurilor grafului neorientat
int *citire_matrice_adiacenta(int nrvarf)
{
	int i, j;
	int *matrice;

	if (nrvarf <= 0)
		return NULL;
	matrice = (int *) malloc(sizeof(int) * nrvarf * nrvarf);
	if (NULL == matrice)
		return NULL;

	for (i = 0; i < nrvarf; i++)
		for (j = 0; j < nrvarf; j++)
			scanf("%d", matrice + i*nrvarf + j);
	return matrice;
}

// afișare de la STDOUT
void afisare_matrice_adiacenta(int *matrice, int nrvarf)
{
	int i, j;

	for (i = 0; i < nrvarf; i++) {
		for (j = 0; j < nrvarf; j++)
			printf(" %d", matrice[i*nrvarf + j]);
		putchar('\n');
	}
}

// returnează numărul de vecini ai nodului dat
int nr_vecini(int *matrice, int nrvarf, int nod)
{
	int i, vecini;

	vecini = 0;
	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	for (i = 0; i < nrvarf; i++)
		if (0 != matrice[nod*nrvarf + i])
			vecini++;
	return vecini;
}

// afișează toți vecinii nodului dat
void afisare_vecini(int *matrice, int nrvarf, int nod)
{
	int i;

	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	for (i = 0; i < nrvarf; i++)
		if (0 != matrice[nod*nrvarf + i])
			printf(" %d;", i+1);
	putchar('\n');
}

// returnează true dacă nodurile sunt adiacente
bool este_muchie(int *matrice, int nrvarf, int nod1, int nod2)
{
	nod1--;					// nodurile sunt numărate de la 1, nu de la 0
	nod2--;
	if (0 != matrice[nod1*nrvarf + nod2])
		return true;
	else
		return false;
}


// operații cu matricea de adiacență a unui graf neorientat
int main(void)
{
	int i, j, v, nr;
	int *mat;

	printf("Introduceți numărul vârfurilor din graful neorientat: ");
	scanf("%i", &nr);

	printf("Introduceți matricea de adiacență a grafului neorientat:\n");
	mat = citire_matrice_adiacenta(nr);
	if (NULL == mat) {
		fprintf(stderr, "E: memorie insuficientă pentru matricea de adiacență\n");
		return errno;
	}

	printf("Matricea de adiacență a grafului neorientat:\n");
	afisare_matrice_adiacenta(mat, nr);
	putchar('\n');

	for (i = 1; i <= nr; i++) {
		v = nr_vecini(mat, nr, i);
		if (0 != v) {
			printf("Nodul «%d» are %d vecini:", i, v);
			afisare_vecini(mat,nr,i);
		}
	}
	putchar('\n');

	printf("Graful neorientat are următoarele muchii:");
	for (i = 1; i <= nr; i++) {
		for (j = 1; j <= nr; j++) {
			if (este_muchie(mat,nr,i,j))
				printf(" [%d;%d]", i, j);
		}
	}
	putchar('\n');
	return 0;
}
