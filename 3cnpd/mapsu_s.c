/**
 * mapsu_s.c -- server pentru clienții f1(), f2() și f3()
 * Metoda aproximațiilor succesive pentru sisteme de ecuații.
 *
 * / x = lg(y/z) + 1
 * | y = -2•x² + z² + 0.4
 * \ z = x•y/20 + 2
 *
 * x0 = [1 2 2]
 * eps = 0.00000000000001
 *
 * În 62 iterații soluția aproximată calculată este:
 * x[1] = 1.08798166097262916096610752
 * x[2] = 2.62392202870348079102313932
 * x[3] = 2.14273895235257416658214424
 */


//#define NDEBUG

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

// memset()
#include <string.h>

// accept()
#include <sys/types.h>

#if ((defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__)
#  define _WIN32_WINNT	0x501
#  include <winsock2.h>
#  include <ws2tcpip.h>
#else
#  include <sys/socket.h>
#endif

#include "libmapsu.c"

#define BUF_SIZE	200		// max number of bytes we can get at once
#define PORT_CF1	"60001"		// portul de comunicare cu f1()
#define PORT_CF2	"60002"		// portul de comunicare cu f2()
#define PORT_CF3	"60003"		// portul de comunicare cu f3()

// soclu mapsu_cf1
double f1(int fd, double x, double y, double z)
{
	char buf[BUF_SIZE];
	ssize_t nread;

	sprintf(buf, "%.26lf %.26lf %.26lf\n", x, y, z);
	if (send(fd, buf, strlen(buf), 0) == -1) {
		perror("f1(): send: ");
		exit(EXIT_FAILURE);
	}

	while ((nread = recv(fd, buf, BUF_SIZE-1, 0)) > 0) {
		if (buf[nread-1] == '\n')
			buf[nread-1] = '\0';
		else
			buf[nread] = '\0';
		if ('\0' == buf[0])
			continue;
		break;
	}

	nread = sscanf(buf, "f1: %lg", &x);
	if (1 == nread)
		return x;
#ifndef NDEBUG
	printf("W mapsu_s f1(): nu am citit rezultatul.. ignorat\n");
#endif
	exit(EXIT_FAILURE);
}

// soclu mapsu_cf2
double f2(int fd, double x, double y, double z)
{
	char buf[BUF_SIZE];
	ssize_t nread;

	sprintf(buf, "%.26lf %.26lf %.26lf\n", x, y, z);
	if (send(fd, buf, strlen(buf), 0) == -1) {
		perror("f2(): send: ");
		exit(EXIT_FAILURE);
	}

	while ((nread = recv(fd, buf, BUF_SIZE-1, 0)) > 0) {
		if (buf[nread-1] == '\n')
			buf[nread-1] = '\0';
		else
			buf[nread] = '\0';
		if ('\0' == buf[0])
			continue;
		break;
	}

	nread = sscanf(buf, "f2: %lg", &x);
	if (1 == nread)
		return x;
#ifndef NDEBUG
	printf("W mapsu_s f2(): nu am citit rezultatul.. ignorat\n");
#endif
	exit(EXIT_FAILURE);
}

// soclu mapsu_cf3
double f3(int fd, double x, double y, double z)
{
	char buf[BUF_SIZE];
	ssize_t nread;

	sprintf(buf, "%.26lf %.26lf %.26lf\n", x, y, z);
	if (send(fd, buf, strlen(buf), 0) == -1) {
		perror("f3(): send: ");
		exit(EXIT_FAILURE);
	}

	while ((nread = recv(fd, buf, BUF_SIZE-1, 0)) > 0) {
		if (buf[nread-1] == '\n')
			buf[nread-1] = '\0';
		else
			buf[nread] = '\0';
		if ('\0' == buf[0])
			continue;
		break;
	}

	nread = sscanf(buf, "f3: %lg", &x);
	if (1 == nread)
		return x;
#ifndef NDEBUG
	printf("W mapsu_s f3(): nu am citit rezultatul.. ignorat\n");
#endif
	exit(EXIT_FAILURE);
}


// mapsu server
int main(int argc, char *argv[])
{
	int s1fd, s2fd, s3fd;
	int c1fd, c2fd, c3fd;
	struct sockaddr_storage peer_addr1, peer_addr2, peer_addr3;
	socklen_t peer_addr1_len, peer_addr2_len, peer_addr3_len;

	double x[4] = {0, 1, 2, 2};
	double eps = 0.00000000000001;
	double max2;
	int n, ITMAX = 200;

	s1fd = mkserv(PORT_CF1);
	s2fd = mkserv(PORT_CF2);
	s3fd = mkserv(PORT_CF3);
	if (-1 == s1fd || -1 == s2fd || -1 == s3fd) {
		fprintf(stderr, "mapsu_s: legarea la porturile TCP «60001-60003» a eșuat!\n");
		exit(EXIT_FAILURE);
	}

	// deschide conexiunile cu cei 3 clienți
	peer_addr1_len = sizeof(struct sockaddr_storage);
	peer_addr2_len = sizeof(struct sockaddr_storage);
	peer_addr3_len = sizeof(struct sockaddr_storage);
	c1fd = accept(s1fd, (struct sockaddr *)&peer_addr1, &peer_addr1_len);
	c2fd = accept(s2fd, (struct sockaddr *)&peer_addr2, &peer_addr2_len);
	c3fd = accept(s3fd, (struct sockaddr *)&peer_addr3, &peer_addr3_len);
	if (-1 == c1fd || -1 == c2fd || -1 == c3fd) {
		perror("mapsu_s: accept: ");
		exit(EXIT_FAILURE);
	}

	for (n = 1; n <= ITMAX; ++n) {
		x[1] = f1(c1fd, x[1], x[2], x[3]);
		x[2] = f2(c2fd, x[1], x[2], x[3]);
		x[3] = f3(c3fd, x[1], x[2], x[3]);

		max2 = fabs(x[1] - f1(c1fd, x[1], x[2], x[3]));

		if (max2 < fabs(x[2] - f2(c2fd, x[1], x[2], x[3])))
			max2 = fabs(x[2] - f2(c2fd, x[1], x[2], x[3]));

		if (max2 < fabs(x[3] - f3(c3fd, x[1], x[2], x[3])))
			max2 = fabs(x[3] - f3(c3fd, x[1], x[2], x[3]));
#ifndef NDEBUG
		printf("I mapsu_s %2d: %.26lf %.26lf %.26lf\n", n, x[1], x[2], x[3]);
#endif
		if (max2 <= eps)
			break;
	}

	printf ("\nÎn %d iterații ", n);
	if (n > ITMAX)
		printf ("nu a fost atinsă aproximarea dorită!\n");
	else
		printf ("soluția aproximată calculată este:\n");
	for(n = 1; n <= 3; n++)
		printf ("  x[%d] = %.26lf\n", n, x[n]);
	return 0;
}
