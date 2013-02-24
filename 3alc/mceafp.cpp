/**
 * Mini compilator pentru expresii aritmetice simple.
 * (reprezentare în forma poloneză sau postfixată)
 *
 * Operanzi: numere întregi sau reale
 * Operatori:  +  -  *  /
 */

#define NDEBUG

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
//#include <stdlib.h>

#include <stack>
#include <string>
using namespace std;

stack<int> stiva;
string sirexp;

char *nume;			// nume program
FILE *fisier;
bool err;			// cel puțin o eroare
int nrlin = 0;			// numărul liniei curente
int nrcol;			// numărul coloanei curente

double yylval;			// operandul din stânga

void yyerror(char const *mesaj);
int yylex(void);		// analiza lexicală ↦ atom
int yyexfp(void);		// expresie ↦ forma postfixată
int yyparse(void);		// analiza sintactică
int cmpop(int op1, int op2);


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
		yyexfp();

		if (!err) {
			if (!sirexp.empty())
				printf("%d:%s\n\n", nrlin, sirexp.c_str());
		} else
			fputc('\n', stdout);
		//yyparse();
	};
	return 0;
}


// compară prioritățile operatorilor
int cmpop(int op1, int op2)
{
#ifndef NDEBUG
	printf("~ compar %c cu %c\n", (char)op1, (char)op2);
#endif
	switch (op1) {
	case '$':
	case '(':
	case ')':
		// prioritatea cea mai mică (0 ≤ 0|1|2)
		return 0;
	case '+':
	case '-':
		// prioritatea medie (0 < 1 < 2)
		switch (op2) {
		case '$':
		case '(':
		case ')':
			// prioritate mai mare (1 > 0)
			return 1;
		default:
			// aceeași prioritate sau mai mică (1 ≤ 1|2)
			return 0;
		}
	case '*':
	case '/':
		// prioritatea cea mai mare (2 ≥ 0|1|2)
		switch (op2) {
		case '*':
		case '/':
			// aceeași prioritate (2 = 2)
			return 0;
		default:
			// prioritate mai mare (2 > 0|1)
			return 1;
		}
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
 * Două excepții importante:
 * - returnează $ la sfârșit de linie pentru a semnala sfârșitul expresiei;
 * - returnează EOF când se ajunge la sfârșitul fișierului de intrare.
 */
int yylex(void)
{
	int c;

	// ignoră spațiile albe
	do {
		c = fgetc(fisier);
		++nrcol;
	} while (c == ' ' || c == '\t');

	// sfârșit expresie aritmetică
	if ('\n' == c)
		return '$';

	// sfârșit fișier de intrare
	if (EOF == c)
		return EOF;

	// citește un număr pozitiv
	//'+' == c || '-' == c ||
	if ('.' == c || isdigit(c)) {
		ungetc(c, fisier);
		fscanf(fisier, "%lf", &yylval);
		return 0;
	}
	return c;		// returnează caracterul citit
}


// expresie ↦ forma postfixată
int yyexfp(void)
{
	char yylstr[200];
	int op;				// operatorul citit (sau paranteză)

	nrcol = 0;
	err = false;
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
			sprintf(yylstr, " %lg", yylval);
			sirexp += yylstr;
			printf("::%s\n", sirexp.c_str());
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
			if (stiva.empty() || (cmpop(op,stiva.top()) > 0)) {
#ifndef NDEBUG
				printf("~ adaug %c în stivă\n", (char)op);
#endif
				stiva.push(op);
			} else {
				ungetc(op, fisier);	// banda de intrare
				op = stiva.top();
				stiva.pop();
				sirexp += " ";
				sirexp += op;		// banda de ieșire
#ifndef NDEBUG
				printf("~ mutat %c din stivă la expresia postfixată\n", (char)op);
#endif
			}
			break;
		case ')':
			while (!stiva.empty()) {
				op = stiva.top();
				stiva.pop();
				if ('(' != op) {
					sirexp += " ";
					sirexp += op;	// banda de ieșire
#ifndef NDEBUG
					printf("~ mutat %c din stivă la expresia postfixată\n", (char)op);
#endif
					continue;
				}
				break;
			}
			if ('(' != op) {	// eroare sintactică
				err = true;
				yyerror("')' fără pereche");
			}
			break;
		case EOF:
		case '$':
			// am terminat de prelucrat banda de intrare
			while (!stiva.empty()) {
				op = stiva.top();
				stiva.pop();
				sirexp += " ";
				sirexp += op;		// banda de ieșire
#ifndef NDEBUG
				printf("~ mutat %c din stivă la expresia postfixată\n", (char)op);
#endif
			}
			op = '$';		// rescris în buclă
			break;
		default:
			err = true;
			yyerror("operator invalid");
		}
	} while (('$' != op) && (EOF != op));
	return 0;
}
