(deffunction citl ()
  "Citește și returnează o listă de numere întregi"
  (printout t "citl: Introduceti dimensiunea listei: ")
  (bind ?dim (read t))

  (printout t "citl: Introduceti lista de elemente!" crlf)
  (bind ?i 1)
  (bind ?l (list))

  (while (<= ?i ?dim) do
    (printout t "- elementul #" ?i ": ")
    (bind ?l (create$ ?l (read t)))
    (bind ?i (+ ?i 1))
  )

  (return ?l)
)
