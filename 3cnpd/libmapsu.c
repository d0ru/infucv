/**
 * libmapsu.c -- funcții comune pentru client+server
 * Metoda aproximațiilor succesive pentru sisteme de ecuații.
 */

//#define NDEBUG

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

// memset()
#include <string.h>

// getaddrinfo(), socket()
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

// close()
#include <unistd.h>

#define BACKLOG		20		// how many pending connections queue will hold


// crează un server TCP care ascultă cereri pe *:lport
int mkserv(const char *lport)
{
	struct addrinfo hints;
	struct addrinfo *result, *pr;
	int sfd, e;

	// parametrii structură adrese
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;		// IPv4 sau IPv6
	hints.ai_socktype = SOCK_STREAM;	// TCP
	hints.ai_flags = AI_PASSIVE;		// ascultă la *:PORT
	hints.ai_protocol = 0;			// orice protocol
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	// construiește structură adrese pentru «*:lport»
	e = getaddrinfo(NULL, lport, &hints, &result);
	if (0 != e) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(e));
		return -1;
	}

	// buclă peste toate rezultatele, oprire la prima legare reușită
	for (pr = result; NULL != pr; pr = pr->ai_next) {
		sfd = socket(pr->ai_family, pr->ai_socktype, pr->ai_protocol);
		if (-1 == sfd)
			continue;

		if (bind(sfd, pr->ai_addr, pr->ai_addrlen) == 0 && \
				listen(sfd, BACKLOG) == 0) {
			break;		/* Success */
		}

		close(sfd);
	}
	freeaddrinfo(result);		/* No longer needed */
	return (NULL == pr) ? -1 : sfd;
}

// crează o conexiune TCP către shost:sport
int mkconn(char *shost, char *sport)
{
	struct addrinfo hints;
	struct addrinfo *result, *pr;
	int sfd, e;

	// parametrii structură adrese
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;		// IPv4 sau IPv6
	hints.ai_socktype = SOCK_STREAM;	// TCP
	hints.ai_flags = 0;
	hints.ai_protocol = 0;			// orice protocol

	// construiește structură adrese pentru «shost:sport»
	e = getaddrinfo(shost, sport, &hints, &result);
	if (0 != e) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(e));
		return -1;
	}

	// buclă peste toate rezultatele, oprire la prima conectare reușită
	for(pr = result; NULL != pr; pr = pr->ai_next) {
		sfd = socket(pr->ai_family, pr->ai_socktype, pr->ai_protocol);
		if (-1 == sfd)
			continue;

		if (connect(sfd, pr->ai_addr, pr->ai_addrlen) != -1)
			break;		/* Success */

		close(sfd);
	}
	freeaddrinfo(result);		/* No longer needed */
	return (NULL == pr) ? -1 : sfd;
}
