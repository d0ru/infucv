[1lc] Logică computațională
---------------------------

ISO/IEC [JTC1/SC22/WG17][1] este grupul de lucru pentru standardizare internațională a limbajului de programare Prolog.

[1]: http://www.open-std.org/JTC1/SC22/


#### Lecturi esențiale

* _The Art of Prolog_


Unelte pentru dezvoltarea programelor Prolog:

* GNU Prolog compiler ([gprolog][4])
* SWI-Prolog interpreter ([swi-prolog-nox][5])

[4]: http://packages.debian.org/gprolog
[5]: http://packages.debian.org/swi-prolog-nox

Fișierele Prolog pot avea următoarele extensii:

* _.pl_ - fișierul este detectat de majoritatea editoarelor ca fiind un script Perl
* _.pro_ - fișierul este detectat de unele medii de dezvoltare ca fiind fișiere de tip "Project"
* _.prolog_ - detectat automat de editorul [Gedit][6]

[6]: http://packages.debian.org/gedit


Un fișier cod sursă Prolog poate fi compilat și executat astfel:

    u@H:~$ swipl -o PROGRAM -c FILE.prolog && ./PROGRAM
    ?-
    (apasă CTRL^D pentru a termina execuția)


#### Resurse suplimentare

* GNU Prolog [manual][2]
* SWI-Prolog [reference manual][3]

[2]: http://www.gprolog.org/manual/gprolog.html
[3]: http://www.swi-prolog.org/pldoc/refman/