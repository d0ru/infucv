;; 1) Evaluați expresiile:
;; - (4 * (12 + 3 + 7)) / (2 * sqrt(2))
(/ (* 4 (+ 12 3 7)) (* 2 (sqrt 2)))
;31.1127

;; - (sqrt(2^2 + 3^2)) / (7 + 4 * 5)
(/ (sqrt (+ (* 2 2) (* 3 3))) (+ 7 (* 4 5)))
;0.13353893

;; - ((3.29 * 9)/5 sqrt(19) 13/2) — listă
(cons '(/ (* 3.29 9) 5) '((sqrt (19)) (/ 13 2)))
;((/ (* 3.29 9) 5) (SQRT (19)) (/ 13 2))

(cons (/ (* 3.29 9) 5) '((sqrt (19)) (/ 13 2)))
;(5.922 (SQRT (19)) (/ 13 2))

(cons (/ 13 2) '())
;(13/2)

(cons (sqrt 19) (cons (/ 13 2) '()))
;(4.358899 13/2)

(cons (/ (* 3.29 9) 5)
  (cons (sqrt 19)
    (cons (/ 13 2) '())
  )
)
;(5.922 4.358899 13/2)

(cons (/ (* 3.29 9) 5)
  (cons (sqrt 19)
    (list (/ 13 2))
  )
)
;(5.922 4.358899 13/2)


;; 2) Adunarea primelor 2 elemente ale unei liste.
(+ (first '(1 2 3 4 5)) (second '(1 2 3 4 5)))
;3
(+ (first '(4 3 3 4 5)) (second '(2 5 3 4 5)))
;9


;; 3) Radical din primul element al unei liste.
(sqrt (first '(34 2 3 4)))
;5.8309517


;; 4) Să se colecteze primele 3 elemente ale unei liste și să se construiască o nouă listă formată din acestea.
(cons (first '(6 5 2 4 5))
  (cons (second '(6 5 2 4 5))
    (list (third '(6 5 2 4 5)))
  )
)
;(6 5 2)

;; 5) Să se construiască o listă cu suma și produsul primelor 2 elemente dintr-o listă dată.
(cons (+ (first '(6 5 2 4 5)) (second '(6 5 2 4 5)))
  (list (* (first '(6 5 2 4 5)) (second '(6 5 2 4 5))))
)
;(11 30)


;; 4) Să se determine ultimul element dintr-o listă de 4 numere.
(fourth '(1 2 3 30))
;30
(last '(1 2 3 30))
;(30)
(first (last '(1 2 3 30)))
;30


;; 7) Să se inverseze o listă dată de 3 elemente.
(cons (third '(4 6 8))
  (cons (second '(4 6 8))
    (list (first '(4 6 8)))
  )
)
;(8 6 4)


;; 8) Să se calculeze produsul primelor 3 numere dintr-o listă și să se ridice la pătrat.
(* (first '(4 6 8)) (second '(4 6 8)) (third '(4 6 8)))
;192
(expt (* (first '(4 6 8)) (second '(4 6 8)) (third '(4 6 8))) 2)
;36864


;; 9) Să se întoarcă un caracter de pe poziția 3 și unul de pe poziția 7 dintr-un string de 9 caractere.
(char "sir de caractere" 3)
;#\Space
(char "sir de caractere" 7)
;#\c


;; 10) Media numerelor unei liste de 3 elemente.
(/ (+ (first '(6 15 21)) (second '(6 15 21)) (third '(6 15 21))) 3)
;14
