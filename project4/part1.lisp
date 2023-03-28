
(setq fsa '((0 0 x) (0 1 y) (1 2 x) (2 2 x) (2 3 y) (3 3 x) (3 4 z) (4 4 x) (4 2 y) (4 1 a)))
(setq input '(x x x x x y x x x y x x x z x x x a))
(setq acceptStates '(1 3))
(setq alphabet '(x y z a))
(setq initialState '(0))

(defun testFSA (inputStringAsList fsaDescription acceptingStatesList alphabetList initialStateAsList)
(setq state (car initialStateAsList))
(dolist (c inputStringAsList)
  ;; (setq input (cdr input)) 
  (dolist (trans fsaDescription)
    (setq tState (car trans))
    (setq token (caddr trans))
    (setq nState (cadr trans))
    ;; (format t "tState: ~a, token: ~a, nState: ~a, state: ~a, c: ~a\n" tState token nState state c)
    (unless ;; if c is not in the alphabet, print "Not Accepted" and exit exicution
      (member c alphabetList)
      (setq state -1) (return NIL) 
      
    )
    (cond 
      ((eq state tState)
      (cond 
        ((eq c token)
        (setq state nState)))
      ))
  )  
  ;; (format t "State is: ~a after ~a\n" state c)
  (cond ((null inputStringAsList)(return state)))
)
(if (member state acceptingStatesList)
    (format nil "The string is accepted in this language!")
  ;else
    (format nil "Not Accepted!")
)   
)