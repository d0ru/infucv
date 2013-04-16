(deffunction prscalarl (?l1 ?l2)
  "Returnează produsul scalar a două liste: suma de produse l1[i] x l2[i]"
  ; dimensiunea minimă a celor două liste
  (bind ?n1 (length$ ?l1))
  (bind ?n2 (length$ ?l2))
  (if (< ?n1 ?n2) then
    (bind ?n ?n1)
   else
    (bind ?n ?n2)
  )

  ; calculează produsul scalar
  (bind ?pr 0)
  (bind ?i 1)
  (while (<= ?i ?n)
    (bind ?e1 (nth$ ?i ?l1))
    (bind ?e2 (nth$ ?i ?l2))
    (bind ?pi (* ?e1 ?e2))
    (bind ?pr (+ ?pr ?pi))
    ; continuare (++i)
    (bind ?i (+ ?i 1))
  )
  (return ?pr)
)
