(bind ?m (nth$ 1 ?l))
?m
(foreach ?i ?l
  (if (> ?i ?m) then
    (bind ?m ?i))
)
(printout t "Elementul maxim este: ")
?m
