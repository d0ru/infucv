/**
 * Algoritmi genetici — cromozom, codificare liste de adiacență.
 * - fiecare genă este codificată printr-un întreg (32 biți)
 * Traseu: 1 ↦ 2 ↦ 4 ↦ 3
 * ListăA: (2, 4, 1, 3)
 */

#ifndef INFUCV_CRMZLA
#define INFUCV_CRMZLA

#include <iostream>

// CRMZLA — clasa cromozom codificare listă adiacență
class crmzla
{
private:
	int id;			// identificator
protected:
	int nr;			// număr gene
	int *g;			// vector gene [nr+1]
public:
	crmzla(int nrgene = 0, int idgene = 0);
	~crmzla();
	crmzla(const crmzla& cr);	// ctor copiere

	int getId(void) { return id; };
	void init();		// inițializare aleatoare
	void readg(const char *mesaj = NULL);	// citire traseu
	void decodg(const char *mesaj = NULL);	// decodificare traseu

	crmzla& operator=(const crmzla& cr);
	friend std::ostream& operator<<(std::ostream& out, const crmzla& cr);
};

#endif
