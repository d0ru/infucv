/**
 * Mini compilator pentru expresii aritmetice simple.
 * (reprezentare în forma poloneză sau postfixată)
 *
 * Operanzi: numere întregi sau reale
 * Operatori:  +  -  *  /
 */

#define NDEBUG
#define NINFO

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
//#include <stdlib.h>
#include <ctype.h>

#include <stack>
#include <string>
using namespace std;

stack<double> snr;		// stiva temporară cu operanzi
stack<int> stiva;		// stiva temporară cu operatori
string sirexp;			// expresia în forma postfixă

char *nume;			// nume program
FILE *fisier;
int nrlin = 0;			// numărul liniei curente
int nrcol;			// numărul coloanei curente

double yylval;			// operandul din stânga

void yyerror(char const *mesaj);
int yylex(void);		// analiza lexicală ↦ atom
bool yyexfp(void);		// expresie ↦ forma postfixă


// mini compilator expresii aritmetice simple
int main(int argc, char *argv[])
{
	nume = argv[0];
	if (argc < 2)
		fisier = stdin;			// citire de la consolă
	else
		fisier = fopen(argv[1], "r");

	if (NULL == fisier) {
		fprintf(stderr, "%s: eroare: fișierul «%s» nu a putut fi deschis pentru citire\n", argv[0], argv[1]);
		return errno;
	}

	// extrage câte o linie și analizează expresia aritmetică
	while (!feof(fisier)) {
		++nrlin;
		if (yyexfp()) {
			if (!sirexp.empty())
				printf("%d:%s  (%lg)\n\n", nrlin, sirexp.c_str(), snr.top());
		} else {
			putchar('\n');		// o linie liberă între expresii
		}

		while (!snr.empty())		// golește stiva cu operanzi
			snr.pop();
		while (!stiva.empty())		// golește stiva cu operatori
			stiva.pop();
	};
	return 0;
}


// prioritate operator
int prop(int op)
{
	switch (op) {
	case '(':
		return 1;
	case ')':
		return 2;
	case '+':
	case '-':
		return 3;
	case '*':
	case '/':
		return 4;
	}
	return 0;		// pentru siguranță
}


// funcție apelată la orice eroare întâlnită
void yyerror(char const *mesaj)
{
	fprintf (stderr, "%s:%d:%d: eroare: %s\n", nume, nrlin, nrcol, mesaj);
}


/* Analizorul lexical returnează 0 la citire operand (salvează numărul în
 * variabila globală yylval), sau codul numeric al caracterului citit.
 * Excepție importantă:
 * - returnează EOF când se ajunge la sfârșitul fișierului de intrare.
 */
int yylex(void)
{
	int c;

	// ignoră spațiile albe
	do {
		c = fgetc(fisier);
		++nrcol;
	} while (isblank(c));

	// sfârșit fișier de intrare
	if (EOF == c)
		return EOF;

	// citește un număr pozitiv
	if ('.' == c || isdigit(c)) {
		ungetc(c, fisier);
		fscanf(fisier, "%lf", &yylval);
		return 0;
	}
	return c;		// returnează caracterul citit
}


// calculează o singură operație aritmetică
int yycalc(int op)
{
	double nr1, nr2;		// operanzi
	double rez;			// rezultat evaluare expresie

	if (snr.size() < 2) {
		yyerror("lipsește cel puțin un operand");
		return 2;
	}
	nr2 = snr.top(); snr.pop();
	nr1 = snr.top(); snr.pop();
	switch (op) {
	case '+':
		rez = nr1 + nr2;
		break;
	case '-':
		rez = nr1 - nr2;
		break;
	case '*':
		rez = nr1 * nr2;
		break;
	case '/':
		rez = nr1 / nr2;
		break;
	default:
		yyerror("operator invalid");
		return 3;
	}
	snr.push(rez);
#ifndef NINFO
	printf(":: %lg %c %lg = %lg\n", nr1, (char)op, nr2, rez);
#endif

	return 0;
}


// expresie ↦ forma postfixă
bool yyexfp(void)
{
	char yylstr[200];
	int op;				// operatorul citit (sau paranteză)
	int ops;			// operatorul din vârful stivei
	bool err = false;		// cel puțin o eroare
	bool gasit;			// găsit pereche ()

	nrcol = 0;
	sirexp.clear();			// eliberează memoria ocupată

	// construiesc expresia în forma postfixată
	do {
		op = yylex();		// analiza lexicală
#ifndef NDEBUG
		//printf("~ yylex -> %d\n", op);
#endif
		switch (op) {
		case 0:
#ifndef NDEBUG
			printf("~ adaug %lg la expresia postfixată\n", yylval);
#endif
			snr.push(yylval);
			sprintf(yylstr, " %lg", yylval);
			sirexp += yylstr;
#ifndef NINFO
			printf("::%s\n", sirexp.c_str());
#endif
			break;
		case '(':
#ifndef NDEBUG
			printf("~ adaug %c în stivă\n", (char)op);
#endif
			stiva.push(op);
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			while (!stiva.empty()) {
				ops = stiva.top();
#ifndef NDEBUG
				printf("~ compar op%c cu ops%c\n", (char)op, (char)ops);
#endif
				if (prop(op) > prop(ops))
					break;
				stiva.pop();
				sirexp += " ";
				sirexp += ops;		// banda de ieșire
#ifndef NDEBUG
				printf("~ mutat %c din stivă la expresia postfixată\n", (char)ops);
#endif
				if (!err && yycalc(ops))
					err = true;		// eroare sintactică
			}
#ifndef NDEBUG
			printf("~ adaug %c în stivă\n", (char)op);
#endif
			stiva.push(op);
			break;
		case ')':
			gasit = false;
			while (!stiva.empty()) {
				ops = stiva.top();
				stiva.pop();
				if ('(' == ops) {
#ifndef NDEBUG
					printf("~ eliminat pereche paranteze ()\n");
#endif
					gasit = true;
					break;
				} else {
					sirexp += " ";
					sirexp += ops;		// banda de ieșire
#ifndef NDEBUG
					printf("~ mutat %c din stivă la expresia postfixată\n", (char)ops);
#endif
					if (!err && yycalc(ops))
						err = true;		// eroare sintactică
				}
			}
			if (!gasit) {
				err = true;		// eroare sintactică
				yyerror("')' fără pereche");
			}
			break;
		case EOF:
		case '\n':
			// am terminat de prelucrat banda de intrare
			while (!stiva.empty()) {
				ops = stiva.top();
				stiva.pop();
				if ('(' == ops) {
					err = true;		// eroare sintactică
					yyerror("'(' fără pereche");
				} else {
					sirexp += " ";
					sirexp += ops;		// banda de ieșire
#ifndef NDEBUG
				printf("~ mutat %c din stivă la expresia postfixată\n", (char)ops);
#endif
					if (!err && yycalc(ops))
						err = true;		// eroare sintactică
				}
			}
			break;
		default:
			err = true;		// eroare semantică
			yyerror("operand sau operator invalid");
		}
	} while (('\n' != op) && (EOF != op));

	if (!sirexp.empty() && (snr.size() != 1)) {
		err = true;		// eroare sintactică
		yyerror("lipsește cel puțin un operand");
	}
	return !err;
}
