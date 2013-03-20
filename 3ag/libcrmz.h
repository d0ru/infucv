/**
 * Algoritmi genetici — cromozom.
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
	virtual ~crmz();
	crmz(const crmz&);	// ctor copiere

	int getId(void) { return id; };
	void init(void);	// inițializare aleatoare

	virtual crmz& operator=(const crmz&);
	friend std::ostream& operator<<(std::ostream&, const crmz&);
};

#endif
