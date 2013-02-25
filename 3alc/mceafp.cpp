/**
 * Mini compilator pentru expresii aritmetice simple.
 * (reprezentare în forma poloneză sau postfixă)
 *
 * Operanzi: numere (pozitive) întregi sau cu virgulă
 * Operatori binari:  +  -  *  /
 */

#define NDEBUG
#define NINFO

#ifdef NINFO
#  define NDEBUG
#endif

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
//#include <stdlib.h>
#include <ctype.h>

#include <stack>
#include <string>
using namespace std;

struct operand {
	double val;		// valoare operand (sau termen)
	int id;			// operand (0) sau termen (1..)
};

stack<struct operand> snr;	// stiva temporară cu operanzi
stack<int> sop;			// stiva temporară cu operatori
string sirexp;			// expresia în forma postfixă

char *nume;			// nume program
FILE *fisier;
int nrlin = 0;			// numărul liniei curente
int nrcol;			// numărul coloanei curente
int nrterm;			// număr termeni (cod ASM)

struct operand yylval;		// ultimul operand citit din expresie

void yyerror(char const *mesaj);
int yylex(void);		// analiza lexicală ↦ atom
bool yyexfp(void);		// expresie ↦ forma postfixă


// mini compilator expresii aritmetice simple
int main(int argc, char *argv[])
{
	nume = argv[0];
	if (argc < 2)
		fisier = stdin;		// citire de la consolă
	else
		fisier = fopen(argv[1], "r");

	if (NULL == fisier) {
		fprintf(stderr, "%s: eroare: fișierul «%s» nu a putut fi deschis pentru citire\n", argv[0], argv[1]);
		return errno;
	}

	yylval.id = 0;		// întotdeauna operand, nu termen
	// extrage câte o linie și analizează expresia aritmetică
	while (!feof(fisier)) {
		++nrlin;
		if (yyexfp()) {
			if (!sirexp.empty())
				printf("%d:%s  (%lg)\n\n", nrlin, sirexp.c_str(), snr.top().val);
		} else {
			putchar('\n');		// o linie liberă între expresii
		}

		while (!snr.empty())		// golește stiva cu operanzi
			snr.pop();
		while (!sop.empty())		// golește stiva cu operatori
			sop.pop();
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
		fscanf(fisier, "%lf", &yylval.val);
		return 0;
	}
	return c;		// returnează caracterul citit
}


// calculează o singură operație aritmetică
int yycalc(int op, FILE *fisier)
{
	struct operand nr1, nr2;		// operanzi
	struct operand rez;			// rezultat evaluare expresie

	if (snr.size() < 2) {
		yyerror("lipsește cel puțin un operand");
		return 2;
	}
	nr2 = snr.top(); snr.pop();
	nr1 = snr.top(); snr.pop();

	if (0 == nr1.id)
		fprintf(fisier, "LOD %lg\n", nr1.val);
	else
		fprintf(fisier, "LOD T%d\n", nr1.id);

	switch (op) {
	case '+':
		rez.val = nr1.val + nr2.val;
		fprintf(fisier, "ADD");
		break;
	case '-':
		rez.val = nr1.val - nr2.val;
		fprintf(fisier, "SUB");
		break;
	case '*':
		rez.val = nr1.val * nr2.val;
		fprintf(fisier, "MUL");
		break;
	case '/':
		rez.val = nr1.val / nr2.val;
		fprintf(fisier, "DIV");
		break;
	default:
		yyerror("operator invalid");
		return 3;
	}
	if (0 == nr2.id)
		fprintf(fisier, " %lg\n", nr2.val);
	else
		fprintf(fisier, " T%d\n", nr2.id);

	rez.id = ++nrterm;
	snr.push(rez);
	fprintf(fisier, "STO T%d\n\n", rez.id);
#ifndef NINFO
	printf(":: %lg %c %lg = %lg\n", nr1.val, (char)op, nr2.val, rez.val);
#endif

	return 0;
}


// expresie ↦ forma postfixă
bool yyexfp(void)
{
	char yylstr[200];
	int opc;			// operatorul citit (sau paranteză)
	int ops;			// operatorul din vârful stivei
	bool err = false;		// cel puțin o eroare
	bool gasit;			// găsit pereche ()
	FILE *fasm;			// codul „assembler” generat
	char nasm[20];

	sprintf(nasm, "exp%d.asm", nrlin);
	fasm = fopen(nasm, "w+");
	if (NULL == fasm) {
		fprintf(stderr, "%s: eroare: fișierul «%s» nu a putut fi deschis pentru scriere\n", nume, nasm);
		return errno;
	}

	nrcol = 0;
	nrterm = 0;
	sirexp.clear();			// eliberează memoria ocupată

	// construiesc expresia în forma postfixă
	do {
		opc = yylex();		// analiza lexicală
#ifndef NDEBUG
		//printf("~ yylex -> %d\n", opc);
#endif
		switch (opc) {
		case 0:
#ifndef NDEBUG
			printf("~ adaug %lg la expresia postfixă\n", yylval.val);
#endif
			snr.push(yylval);
			sprintf(yylstr, " %lg", yylval.val);
			sirexp += yylstr;
#ifndef NINFO
			printf("::%s\n", sirexp.c_str());
#endif
			break;
		case '(':
#ifndef NDEBUG
			printf("~ adaug %c în stivă\n", (char)opc);
#endif
			sop.push(opc);
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			while (!sop.empty()) {
				ops = sop.top();
#ifndef NDEBUG
				printf("~ compar opc%c cu ops%c\n", (char)opc, (char)ops);
#endif
				if (prop(opc) > prop(ops))
					break;
				sop.pop();
				sirexp += " ";
				sirexp += ops;		// banda de ieșire
#ifndef NDEBUG
				printf("~ mutat %c din stivă la expresia postfixă\n", (char)ops);
#endif
				if (!err && yycalc(ops, fasm))
					err = true;		// eroare sintactică
			}
#ifndef NDEBUG
			printf("~ adaug %c în stivă\n", (char)opc);
#endif
			sop.push(opc);
			break;
		case ')':
			gasit = false;
			while (!sop.empty()) {
				ops = sop.top();
				sop.pop();
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
					printf("~ mutat %c din stivă la expresia postfixă\n", (char)ops);
#endif
					if (!err && yycalc(ops, fasm))
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
			while (!sop.empty()) {
				ops = sop.top();
				sop.pop();
				if ('(' == ops) {
					err = true;		// eroare sintactică
					yyerror("'(' fără pereche");
				} else {
					sirexp += " ";
					sirexp += ops;		// banda de ieșire
#ifndef NDEBUG
					printf("~ mutat %c din stivă la expresia postfixă\n", (char)ops);
#endif
					if (!err && yycalc(ops, fasm))
						err = true;		// eroare sintactică
				}
			}
			break;
		default:
			err = true;		// eroare semantică
			yyerror("operand sau operator invalid");
		}
	} while (('\n' != opc) && (EOF != opc));

	if (!sirexp.empty() && (snr.size() != 1)) {
		err = true;		// eroare sintactică
		yyerror("lipsește cel puțin un operand");
	}
	fclose(fasm);			// închide fișierul ASM
	return !err;
}
