/**
 * mapsu_cf1.c -- client pentru calcul f1()
 * Metoda aproximațiilor succesive pentru sisteme de ecuații.
 */

//#define NDEBUG

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// recv(), send()
#include <sys/types.h>

#if ((defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__)
#  define _WIN32_WINNT	0x501
#  include <winsock2.h>
#  include <ws2tcpip.h>
#else
#  include <sys/socket.h>
#endif

// log10()
#include <math.h>

#include "libmapsu.c"

#define BUF_SIZE	200		// max number of bytes we can get at once
#define HOST		"localhost"
#define PORT		"60001"		// the port client will be connecting to


// calcul f1()
int main(int argc, char *argv[])
{
	char buf[BUF_SIZE];
	char *shost, *sport;
	int sfd, nrpar;
	double x, y, z, f1;
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
	printf("I mapsu_cf1: utilizează server «%s:%s»\n", shost, sport);
#endif

	sfd = mkconn(shost, sport);
	if (-1 == sfd) {
		fprintf(stderr, "mapsu_cf1: conectarea la «%s:%s» a eșuat!\n",
			shost, sport);
		exit(EXIT_FAILURE);
	}

	nrpar = 0;
	while ((nread = recv(sfd, buf, BUF_SIZE-1, 0)) > 0) {
		if (buf[nread-1] == '\n')
			buf[nread-1] = '\0';
		else
			buf[nread] = '\0';
		if ('\0' == buf[0])
			continue;
#ifndef NDEBUG
		//printf("I mapsu_cf1: recv %s\n", buf);
#endif
		nread = sscanf(buf, "%lg %lg %lg", &x, &y, &z);
		if (3 == nread) {
			f1 = log10(y/z) + 1;
#ifndef NDEBUG
			if (1 == nrpar % 2)
				printf("I mapsu_cf1: send f1=%.26lf\n", f1);
			usleep(200000);
#endif
			sprintf(buf, "f1: %.26lf\n", f1);
			if (send(sfd, buf, strlen(buf), 0) == -1) {
				perror("send: ");
				exit(EXIT_FAILURE);
			}
			++nrpar;
#ifndef NDEBUG
		} else {
			printf("I mapsu_cf1: recv %s\n", buf);
			printf("W mapsu_cf1: nu am citit 3 coeficienți.. ignorat\n");
#endif
		}
	}
	return 0;
}
