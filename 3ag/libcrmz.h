/**
 * Algoritmi genetici — cromozom, codificare binară.
 * - fiecare genă este codificată pe un singur bit
 */

#ifndef INFUCV_CRMZ
#define INFUCV_CRMZ

#include <iostream>

// CRMZ — clasa cromozom
class crmz
{
private:
	int id;			// identificator
protected:
	int dim;		// dimensiune cromozom (în octeți)
	int nr;			// număr gene (codificare binară)
	unsigned char *g;	// șir de gene pe biți
public:
	crmz(int nrgene = 0, int idgene = 0);
	~crmz();
	crmz(const crmz&);	// ctor copiere

	int getId(void) { return id; };
	void init(void);	// inițializare aleatoare

	crmz& operator=(const crmz&);
	friend std::ostream& operator<<(std::ostream&, const crmz&);
};

#endif
