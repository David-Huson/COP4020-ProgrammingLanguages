(setq fsa '((0 0 x) (0 1 y) (1 2 x) (2 2 x) (2 3 y) (3 3 x) (3 4 z) (4 4 x) (4 2 y) (4 1 a)))
(setq input '(x x x x x y x x x y x x x z x x x a))
(setq acceptStates '(1 3))
(setq alphabet '(x y z a))
(setq initialState '(0))
(setq state (car initialState))
(dolist (c input)
  (setq input (cdr input)) 
  (dolist (trans fsa)
    (setq tState (car trans))
    (setq token (caddr trans))
    (setq nState (cadr trans))
    (format t "tState: ~a, token: ~a, nState: ~a, state: ~a, c: ~a\n" tState token nState state c)
    ;; (cond (eq NIL (member c alphabet))((print "Not accepted") (return NIL)))
    (cond 
      ((eq state tState)
      (cond 
        ((eq c token)
        (setq state nState)))
      ))
  )  
  (format t "State is: ~a after ~a\n" state c)
  (cond ((null input)(return state)))
)
(cond ((member state acceptStates)(print "The string is accepted in this language!")))


  