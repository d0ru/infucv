(deffunction difl (?l1 ?l2)
  "Returnează diferența dintre două liste: elementele ce sunt doar în prima listă"
  ; inițializare lista vidă
  (bind ?l (list))

  (foreach ?e ?l1
    ; adaugă doar elementele ce nu se găsesc în cealaltă listă
    (if (not (member$ ?e ?l2)) then
      ; l = l + e
      (bind ?l (create$ ?l ?e))
    )
  )
  (return ?l)
)
