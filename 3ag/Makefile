

libcrmz.o: libcrmz.h libcrmz.cpp
	g++ -Wall libcrmz.cpp -c

libcrmzla.o: libcrmzla.h libcrmzla.cpp
	g++ -Wall libcrmzla.cpp -c


lab01: libcrmz.o lab01~inpo.cpp
	g++ -Wall libcrmz.o lab01~inpo.cpp -o lab01~inpo

lab03: libcrmzla.o lab03~covo.cpp
	g++ -Wall libcrmzla.o lab03~covo.cpp -o lab03~covo


all: lab01 lab03

clean:
	rm -vf *.o lab01~inpo lab03~covo
