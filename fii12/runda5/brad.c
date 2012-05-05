/**
 * Soluție
 * -------
 * Avem o progresie aritmetică de puteri ale lui 2:
 *   2⁰ + 2¹ + 2²+ 2³ + .. + 2^(k-1) = S
 * astfel încât S <= N și (N - S) < 2^k.
 *
 * Reduc N = N - S. Dacă N = 1 procesul se oprește.
 * Altfel, reduc N = N - 1, actualizez B = 2 • B și reiau procesul
 * cât timp N > 2.
 *
 * Teste extreme
 * -------------
 * 1) N=1 ↦ B=1
 * 2) N=2 ↦ B=1
 * 3) N=2^k ↦ B = 1
 * 4) N=2^(k+1) - 1 ↦ B = 2^k
 * 9) N=1000000000 ↦ B = 2¹²
 */

//#define NDEBUG

#include <assert.h>
#include <errno.h>
#include <stdio.h>

#define MAX_N	1000000000

// COMPLEXITATE timp O(lgN) | spațiu θ(1)
int main(void)
{
	FILE *fintrare;				// "r" din «brad.in»
	FILE *fiesire;				// "w" în «brad.out»
	int n;					// număr secundă
	int b, p;

	fintrare = fopen("brad.in", "r");
	if (NULL == fintrare) {
		fprintf(stderr, "E: fișierul «brad.in» nu a putut fi deschis pentru citire\n");
		return errno;
	}

	fiesire = fopen("brad.out", "w");
	if (NULL == fiesire) {
		fprintf(stderr, "E: fișierul «brad.out» nu a putut fi deschis pentru scriere\n");
		return errno;
	}

	// citesc numărul de secunde
	if (1 != fscanf(fintrare, "%d", &n))
		return errno;			// eroare de citire
	// verificare sanitară
	assert(1 <= n && n <= MAX_N);

	b = 1;					// număr beculețe
	while (n > 2) {
		for (p = 1; p < n; p *= 2)
			n -= p;
		if (1 == n--)
			break;
		b *= 2;
	}

	fprintf(fiesire, "%d", b);
	return 0;
}
