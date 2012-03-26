/*
 * Operații pe lista de adiacență a unui graf neorientat.
 * Pentru fiecare nod se reține lista vecinilor săi într-o listă simplu
 * înlânțuită. Capul de listă pentru fiecare nod se reține într-un vector
 * de pointeri către structura «nod».
 *
 * Lista de adiacență se dă în felul următor:
 * nod: listă vecini 0
 */

#ifndef INFUCV_GNLA
#define INFUCV_GNLA
// GNLA - graf neorientat, listă de adiacență

struct nod {
	int nr;				// numărul vârfului în graf
	struct nod *urm;		// următorul nod vecin
};

// nrvarf = |V|, numărul vârfurilor grafului neorientat
struct nod *fcitire_gnla(FILE *fisier, int *nrvarf);
// citire de la STDIN
#define citire_gnla(N)	fcitire_gnla(stdin, N)

// afișare listă de adiacență
void fafisare_gnla(FILE *fisier, const struct nod varf[], int nrvarf);
// afișare la STDOUT
#define afisare_gnla(V,N)	fafisare_gnla(stdout, V, N)

// returnează numărul de vecini ai nodului dat
// (1 ≤ nod ≤ nrvarf)
int nrvec_gnla(const struct nod varf[], int nrvarf, int nod);

// afișează toți vecinii nodului dat
// (1 ≤ nod ≤ nrvarf)
void afvec_gnla(const struct nod varf[], int nrvarf, int nod);

// returnează true dacă nodurile sunt adiacente (formează o muchie)
// (1 ≤ nod1 < nod2 ≤ nrvarf)
bool muchie_gnla(const struct nod varf[], int nrvarf, int nod1, int nod2);


// afisare componenta conexă de la «nod» cu parcurgere în lățime
// (1 ≤ nod ≤ nrvarf)
void afcclatviz_gnla(const struct nod varf[], int nrvarf, int nod, bool *vizitat);

// afișare componente conexe folosind parcurgerea în lățime
void afcclat_gnla(const struct nod varf[], int nrvarf);

// parcurgere/vizitare în lățime (BFS)
// (1 ≤ nod ≤ nrvarf)
void vizlat_gnla(const struct nod varf[], int nrvarf, int nod);


// afisare componenta conexă de la «nod» cu parcurgere în adâncime
// (1 ≤ nod ≤ nrvarf)
void afccadviz_gnla(const struct nod varf[], int nrvarf, int nod, bool *vizitat);

// afișare componente conexe folosind parcurgerea în adâncime
void afccad_gnla(const struct nod varf[], int nrvarf);

// parcurgere/vizitare în adâncime (DFS)
// (1 ≤ nod ≤ nrvarf)
void vizad_gnla(const struct nod varf[], int nrvarf, int nod);
#endif
