libcrmz.o: libcrmz.h libcrmz.cpp
	g++ -Wall libcrmz.cpp -c

lab01~inpo: libcrmz.o lab01~inpo.cpp
	g++ -Wall libcrmz.o lab01~inpo.cpp -o lab01~inpo

all: lab01~inpo

clean:
	rm -vf *.o lab01~inpo
