/**
 * libmapsu.c -- funcții comune pentru client+server
 * Metoda aproximațiilor succesive pentru sisteme de ecuații.
 */

#include <stdio.h>

// memset()
#include <string.h>

// getaddrinfo(), socket()
#include <sys/types.h>

#if ((defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__)
#  define _WIN32_WINNT	0x501
#  include <winsock2.h>
#  include <ws2tcpip.h>
#else
#  include <sys/socket.h>
#  include <netdb.h>
#endif

// close()
#include <unistd.h>

#define BACKLOG		20		// how many pending connections queue will hold

// crează un server TCP care ascultă cereri pe *:lport
int mkserv(const char *lport)
{
	struct addrinfo hints;
	struct addrinfo *result, *pr;
	int sfd, e;

#if ((defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__)
	WSADATA wsaData;
	e = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (0 != e) {
		fprintf(stderr, "WSAStartup: %s\n", gai_strerror(e));
		WSACleanup();
		return -1;
	}
#endif

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

#if ((defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__)
		closesocket(sfd);
#else
		close(sfd);
#endif
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

#if ((defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__)
	WSADATA wsaData;
	e = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (0 != e) {
		fprintf(stderr, "WSAStartup: %s\n", gai_strerror(e));
		WSACleanup();
		return -1;
	}
#endif

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

#if ((defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__)
		closesocket(sfd);
#else
		close(sfd);
#endif
	}
	freeaddrinfo(result);		/* No longer needed */
	return (NULL == pr) ? -1 : sfd;
}
