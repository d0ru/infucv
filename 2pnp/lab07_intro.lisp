(= 10 10.0)
;T
(equal 10 10.0)
;NIL
(eql 10 10.0)
NIL

"un sir de caractere.."
;"un sir de caractere.."

(length "un sir de caractere..")
;21

(string= "unu" "doi")
;NIL
(string= "unu" "unu")
;T
(string= "a" #\a)
;T

(char "selectare câte un caracter din șir" 11)
;#\LATIN_SMALL_LETTER_A_WITH_CIRCUMFLEX

(char= #\a #\a #\ă #\â)
;NIL
(char= #\a #\a)
;T


*read-base*
;10
*print-base*
;10
*package*
;#<PACKAGE COMMON-LISP-USER>

(find-package 'lisp)
;#<PACKAGE COMMON-LISP>

(symbol-name 'pi)
;"PI"

(type-of 'pi)
;SYMBOL
(type-of '10.0)
;SINGLE-FLOAT

(describe 'common-lisp-user::paul)
;PAUL is the symbol PAUL, lies in #<PACKAGE COMMON-LISP-USER>, is accessible in 1 package
;COMMON-LISP-USER.

(describe 'pi)
;PI is the symbol PI, lies in #<PACKAGE COMMON-LISP>


pi
;3.1415926535897932385L0
'pi
;PI
(eql 'pi 'PI)
;T

'p\aul
;|PaUL|
'p|au|l
;|PauL|


(cons 'e '())
;(E)
(cons 'a '(b c d))
;(A B C D)

(cons 'a (cons 'b (cons 'c '())))
;(A B C)
(cons 'a (cons 'b (list 'c)))
;(A B C)

(equal '(a b c) '(a b c))
;T
(equal '(a b c) '(a (b) c))
;NIL


(defun li3 (o1 o2 o3)
  "construieste o lista din cele 3 variabile"
  (cons o1 (cons o2 (list o3)))
)
(li3 1 2 3)
;(1 2 3)
(li3 "unu" "doi" "trei")
;("unu" "doi" "trei")

(defun listainv2 (l)
  "inversează elementele unei liste de 2 elemente"
  (cons (second l) (list (first l)))
)_
;LISTAINV2
(listainv2 '(6 9))
;(9 6)

(defun patrat (n)
  "calculeaza pătratul numărului dat"
  (* n n)
)
;PATRAT
(patrat 4)
;16

(defun listainv3 (l)
  "inverseaza ordinea celor 3 elemente dintr-o listă"
  (cons (third l)
    (cons (second l)
      (list (first l))
    )
  )
)
;LISTAINV3
(listainv3 '(6 5 3))
;(3 5 6)
(listainv3 '(a b c))
;(C B A)


(defpackage "lab7")
;#<PACKAGE |lab7|>
(in-package "lab7")
;#<PACKAGE |lab7|>

(defun last (list)
  "ultimul element"
  (third list)
)
;LAST
(last '(a b c))
;C
(lisp:last '(a b c))
;(C)


[1]> (compile-file "suma.lisp")
;; Compiling file /srv/prof/IT/github/infucv/2pnp/suma.lisp ...
;; Wrote file /srv/prof/IT/github/infucv/2pnp/suma.fas
0 errors, 0 warnings
#P"/srv/prof/IT/github/infucv/2pnp/suma.fas" ;
NIL ;
NIL
[2]> (load "suma")
;; Loading file /srv/prof/IT/github/infucv/2pnp/suma.fas ...
;; Loaded file /srv/prof/IT/github/infucv/2pnp/suma.fas
T
[3]> (suma3 1 2 3)
6


[4]> (if t 'yes 'no)
YES

[39]> (defun suma (n1 n2)
  (if (= n1 0) n2
    (+ 1 (suma (- n1 1) n2))
  )
)
SUMA
[40]> (suma 2 5)
7
[41]> (trace suma)
;; Tracing function SUMA.
(SUMA)
[42]> (suma 2 5)
1. Trace: (SUMA '2 '5)
2. Trace: (SUMA '1 '5)
3. Trace: (SUMA '0 '5)
3. Trace: SUMA ==> 5
2. Trace: SUMA ==> 6
1. Trace: SUMA ==> 7
7

[65]> (defun produs (n1 n2)
   (if (= n1 1) n2
     (+ (produs (- n1 1) n2) n2))
)
PRODUS
[70]> (produs 4 5)
1. Trace: (PRODUS '4 '5)
2. Trace: (PRODUS '3 '5)
3. Trace: (PRODUS '2 '5)
4. Trace: (PRODUS '1 '5)
4. Trace: PRODUS ==> 5
3. Trace: PRODUS ==> 10
2. Trace: PRODUS ==> 15
1. Trace: PRODUS ==> 20
20

[75]> (defun lungime (l)
  (if (null l) 0
    (+ (lungime(rest l)) 1))
)
LUNGIME
[77]> (lungime '(a b))
2

[85]> (defun membru (n li)
  "apartine N listei li?"
  (cond ((null li) nil)
    ((eql n (first li)) t)
    (t (membru n (rest li)))
  )
)
MEMBRU
[86]> (membru 3 '(1 2))
NIL
[87]> (membru 3 '(1 2 3))
T

[105]> (defun egalitateli (l1 l2)
  "egalitate lungime liste"
  (cond ((null l1) (null l2))
    ((null l2) nil)
    (t (egalitateli (rest l1) (rest l2)))
  )
)
EGALITATELI
[106]> (egalitateli '(1 2) '(1 2))
T
[107]> (egalitateli '(1 2) '(1 2 3))
NIL

[113]> (defun te1e2 (e1 e2 li)
  "testeaza daca e1 se afla inaintea lui e2"
  (cond ((null li) nil)
    ((and (eql (first li) e1) (member e2 (rest li))) t)
    (t  (te1e2 e1 e2 (rest li)))
  )
)
TE1E2
[134]> (te1e2 'b 2 '(1 a 2 b 3))
NIL
[135]> (te1e2 'a 2 '(1 a 2 b 3))
T

(defun aparitii (li n p)
  "numărul de apariții ale unui element într-o listă"
  (cond ((null li) p)
    ((= (first li) n) (aparitii (rest li) n (+ p 1)))
    (t  (aparitii (rest li) n p))
  )
)
[12]> (aparitii '(1 2 3 2 5 6 2) 2 0)
3
[13]> (aparitii '() 2 0)
0

(defun aparitii (n li)
  "numărul de apariții ale unui element într-o listă"
  (cond ((null li) 0)
    ((= (first li) n) (+ 1 (aparitii n (rest li))))
    (t  (aparitii n (rest li)))
  )
)
[12]> (aparitii 2 '(1 2 4 2 2 3))
3
[13]> (aparitii 2 '())
0
