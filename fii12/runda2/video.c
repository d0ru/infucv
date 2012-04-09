/**
 * Compania VideoDava oferă prin intermediul rețelei globale Internet
 * un nou serviciu - filme video la comandă.
 *
 * Cerință
 * -------
 * Elaborați un program care, cunoscând durata «t» a filmului video,
 * parametrii «b», «d» și durata total admisibilă a pauzelor «p»,
 * calculează o capacitate «s» a memoriei tampon pentru care numărul
 * de pauze va fi minim.
 *
 * În scopuri didactice, se consideră că timpul și cantitățile de
 * informație sunt mărimi continue sau, prin alte cuvinte, sunt admise
 * și părți fracționare de secundă și octet.
 */

//#define NDEBUG

#include <assert.h>
#include <errno.h>
#include <stdio.h>

/**
 * Soluție
 * -------
 * b - viteza de transmisie a informației pentru redare fără întreruperi
 * d - viteza reală de transmisie a informației (d < b)
 * t - timpul de redare a filmului fără pauze
 * p - durata total admisibilă a fiecărie pauze în parte
 *
 * t2 - timpul de redare a filmului cu pauze
 *   t2 = t · b / d
 *
 * np - numărul minim de pauze
 *   np = ⌈(t2 - t) / p⌉ = ⌈t · (b/d - 1) / p⌉ = ⌈t · (b-d) / (d · p)⌉
 *   np < t · (b / d) / p = t2 / p ≤ t2
 *
 * ti - timpul per interval (pauză+redare)
 *   ti = t2  / np = t · (b/d) / np
 *
 * tr - timpul de redare a filmului pe fiecare din cel «np» intervale
 *   tr · b = ti · d  ⇒  tr = ti · d/b = t / np = d · p / (b-d)
 *
 * tp - timpul de pauza a filmului pe fiecare din cel «np» intervale
 *   tp = ti - tr = ti · (b-d) / b = t · (b-d) / (d · np)
 *
 * s - capacitate memorie tampon
 * ⇒  s = tp · d = t · (b-d) / np
 *    s < t2 · b ≤ 14400 · 2⁵⁰ < 2⁶⁴
 */
int main(void)
{
	FILE *fintrare;				// "r" din «video.in»
	FILE *fiesire;				// "w" în «video.out»
	double b, d;				// 2¹⁰ ≤ d < b ≤ 2³⁰
	short int t;				// 1 ≤ t ≤ 14400
	short int p;				// 1 ≤ p ≤ 3600
	double t2;				// t < t2 ≤ 14400 · 2²⁰ (> 2³³)
	long long int np;			// np < t2 < 2³⁴
	double s;				// s < t2 · b < 2⁶⁴
#ifndef NDEBUG
	double ti, tp, tr;			// t* < t2 < 2³⁴
#endif

	fintrare = fopen("video.in", "r");
	if (NULL == fintrare) {
		fprintf(stderr, "E: fișierul «video.in» nu a putut fi deschis pentru citire\n");
		return errno;
	}

	fiesire = fopen("video.out", "w");
	if (NULL == fiesire) {
		fprintf(stderr, "E: fișierul «video.out» nu a putut fi deschis pentru scriere\n");
		return errno;
	}

	// citesc datele de intrare
	if (4 != fscanf(fintrare, "%lf %lf %hi %hi", &d, &b, &t, &p))
		return errno;			// eroare de citire

	//depanare: verific datele de intrare
	assert(1024 <= d);
	assert(d <= 1073741823);
	assert(d < b);
	assert(b <= 1073741824);
	assert(1 <= p);
	assert(p <= 3600);
	assert(1 <= t);
	assert(t <= 14400);

	t2 = t * b / d;
	np = (long long int)(t * (b - d) / (d * p));
	if ((np * p) < (t2 - t))
		++np;
	//depanare: numărul de pauze trebuie să fie cel puțin 1
	assert(np > 0);

#ifndef NDEBUG
	fprintf(stdout, "I: b-d=%lg t=%hi, t2=%lg\n", (b-d), t, t2);
	tp = t2 - t;				// timpul total pauze
	fprintf(stdout, "I: tp=%lg, p=%hi, np=%lli\n", tp, p, np);
	ti = t2 / np;				// timpul per interval (pauză+redare)
	tr = t / np;				// timpul de redare a filmului
	tp = ti - tr;
	fprintf(stdout, "I: ti=%lg, tp=%lg tr=%lg\n", ti, tp, tr);
#endif
	s = t * (b-d) / np;			// s = tp · d = t · (b-d) / np
	if (s == (long long int)s)
		fprintf(fiesire, "%.0lf\n", s);
	else
		fprintf(fiesire, "%lf\n", s);
	return 0;
}
