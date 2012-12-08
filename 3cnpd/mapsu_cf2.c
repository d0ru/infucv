/**
 * mapsu_cf2.c -- client pentru calcul f2()
 * Metoda aproximațiilor succesive pentru sisteme de ecuații.
 */

//#define NDEBUG

#include <assert.h>
#include <stdio.h>

// recv(), send()
#include <sys/types.h>
#include <sys/socket.h>

// close()
#include <unistd.h>

// log10()
#include <math.h>

#include "libmapsu.c"

#define BUF_SIZE	200		// max number of bytes we can get at once
#define HOST		"localhost"
#define PORT		"60002"		// the port client will be connecting to


// calcul f2()
int main(int argc, char *argv[])
{
	char buf[BUF_SIZE];
	char *shost, *sport;
	int sfd, nrpar;
	double x, y, z, f2;
	ssize_t nread;

	// stăpân: nume sau adresă IP
	if (argc < 2)
		shost = HOST;
	else
		shost = argv[1];

	// stăpân: număr port TCP
	if (argc < 3)
		sport = PORT;
	else
		sport = argv[2];
#ifndef NDEBUG
	printf("I mapsu_cf2: utilizează server «%s:%s»\n", shost, sport);
#endif

	sfd = mkconn(shost, sport);
	if (-1 == sfd) {
		fprintf(stderr, "mapsu_cf2: conectarea la «%s:%s» a eșuat!\n",
			shost, sport);
		exit(EXIT_FAILURE);
	}

	nrpar = 1;
	while ((nread = recv(sfd, buf, BUF_SIZE-1, 0)) > 0) {
		if (buf[nread-1] == '\n')
			buf[nread-1] = '\0';
		else
			buf[nread] = '\0';
		if ('\0' == buf[0])
			continue;
#ifndef NDEBUG
		//printf("I mapsu_cf2: recv %s\n", buf);
#endif
		nread = sscanf(buf, "%lg %lg %lg", &x, &y, &z);
		if (3 == nread) {
			f2 = -2*x*x + z*z + 0.4;
#ifndef NDEBUG
			if (1 == nrpar % 2)
				printf("I mapsu_cf2: send f2=%.26lf\n", f2);
			usleep(200000);
#endif
			sprintf(buf, "f2: %.26lf\n", f2);
			if (send(sfd, buf, strlen(buf), 0) == -1) {
				perror("send: ");
				exit(EXIT_FAILURE);
			}
			++nrpar;
#ifndef NDEBUG
		} else {
			printf("I mapsu_cf2: recv %s\n", buf);
			printf("W mapsu_cf2: nu am citit 3 coeficienți.. ignorat\n");
#endif
		}
	}
	close(sfd);
	return 0;
}
