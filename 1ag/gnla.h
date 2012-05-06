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
// (1 ≤ nod ≤ nrvarf)

// citire listă de adiacență
int fcitire_gnla(FILE *fisier, struct nod **graf);
// citire de la STDIN
#define citire_gnla(G)		fcitire_gnla(stdin, G)

// afișare listă de adiacență
void fafisare_gnla(FILE *fisier, const struct nod graf[], int nrvarf);
// afișare la STDOUT
#define afisare_gnla(G,N)	fafisare_gnla(stdout, G, N)

// returnează numărul de vecini ai nodului dat
int nrvec_gnla(const struct nod graf[], int nrvarf, int nod);

// afișează toți vecinii ai nodului dat
void afvec_gnla(const struct nod graf[], int nrvarf, int nod);

// returnează «true» dacă nodurile sunt adiacente (formează o muchie)
// (1 ≤ nod1 < nod2 ≤ nrvarf)
bool muchie_gnla(const struct nod graf[], int nrvarf, int nod1, int nod2);


// marcare componentă conexă de la «nod» cu parcurgere în lățime, afișare opțională
void cclatviz_gnla(const struct nod graf[], int nrvarf, int nod, bool *vizitat, bool afis);

// număr componente conexe folosind parcurgerea în lățime, afișare opțională
int cclat_gnla(const struct nod graf[], int nrvarf, bool afis);

// parcurgere/vizitare în lățime (BFS)
void vizlat_gnla(const struct nod graf[], int nrvarf, int nod);


// marcare componentă conexă de la «nod» cu parcurgere în adâncime, afișare opțională
void ccadviz_gnla(const struct nod graf[], int nrvarf, int nod, bool *vizitat, bool afis);

// număr componente conexe folosind parcurgerea în adâncime, afișare opțională
int ccad_gnla(const struct nod graf[], int nrvarf, bool afis);

// parcurgere/vizitare în adâncime (DFS)
void vizad_gnla(const struct nod graf[], int nrvarf, int nod);
#endif
