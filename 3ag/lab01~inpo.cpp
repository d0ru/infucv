/**
 * Algoritmi genetici — codificare binară
 * Inițializarea unei populații cu parametrii:
 * - n: dimensiunea cromozomului
 * - m: dimensiunea populației
 */

//#define NDEBUG

#include "libcrmz.h"
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <list>
using namespace std;

int main(void)
{
	int i, n, m;
	list<crmz> pocz;		// populație cromozomi
	time_t t;

	srand(time(&t));
	cout << "Introduceți dimeniunea cromozomului: ";
	cin >> n;
	cout << "Introduceți dimeniunea populației: ";
	cin >> m;

	// inițializare populație
	for (i = 0; i < m; ++i)
		pocz.push_back(crmz(n,i));

	// afișare populație
	cout << endl
	     << "Ce cromozomi au fost generați automat?" << endl;
	for (list<crmz>::iterator icz = pocz.begin(); icz != pocz.end(); ++icz) {
		icz->init();
		cout << icz->getId() << ": " << *icz << endl;
	}
	return 0;
}
