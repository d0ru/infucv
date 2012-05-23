(defun liord (li)
  "verificați dacă o listă este ordonată crescător"
  (cond ((null li) t)
    ((null (rest li)) t)
    ((<= (first li) (second li)) (liord (rest li)))
    (t  nil)
  )
)

(defun rmelem (li p)
  "să se șteargă elementul aflat pe o poziție dată într-o listă"
  (cond ((null li) '())
    ((<= p 1) (rest li))
    (t  (append (list (first li)) (rmelem (rest li) (- p 1))))
  )
)

(defun nrpoz (li)
  "să se numere câte elemente pozitive sunt într-o listă"
  (cond ((null li) 0)
    ((< (first li) 0) (nrpoz (rest li)))
    (t  (+ 1 (nrpoz (rest li))))
  )
)

(defun caplista (l1 l2)
  "lista l1 este capul listei l2"
  (cond
    ((null l1) t)
    ((null l2) nil)
    ((= (first l1) (first l2)) (caplista (rest l1) (rest l2)))
    (t  nil)
  )
)

(defun coadalista (l1 l2)
  "lista l1 este coada la lista l2"
  (cond
    ((null l1) t)
    ((null l2) nil)
    ((equal l1 l2) t)
    (t  (coadalista l1 (rest l2)))
  )
)

(defun sublista (l1 l2)
  "verificați dacă o listă este sublistă pentru o altă listă"
  (cond
    ((null l2) nil)
    ((caplista l1 l2) t)
    ((coadalista l1 l2) t)
    (t  (sublista l1 (rest l2)))
  )
)

(defun prscalar (v1 v2)
  "produsul scalar a doi vectori ∑xi•yi, i=1,n"
  (if (or (null v1) (null v2)) 0
    (+ (* (first v1) (first v2)) (prscalar (rest v1) (rest v2)))
  )
)

(defun intercl (l1 l2)
  "interclasarea a două liste ordonate crescător"
  (cond ((null l1) l2)
    ((null l2) l1)
    ((< (first l1) (first l2)) (append (list (first l1)) (intercl (rest l1) l2)))
    ((> (first l1) (first l2)) (append (list (first l2)) (intercl l1 (rest l2))))
    (t  (intercl l1 (rest l2)))
  )
)
