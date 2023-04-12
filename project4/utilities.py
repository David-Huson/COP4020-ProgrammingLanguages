###############################################################################
# David Huson                                                                 #
# Project 3                                                                   #
# utilities.py                                                                #
# 3/20/23                                                                     #
#                                                                             #
# Some helper functions to get the tokenized fsa description and text string. #
###############################################################################

from re import sub

def tokenize(filename):
  with open(filename) as fsaFile:
    rawData = fsaFile.read()

  fsaData = rawData.split(";")
  numStates = fsaData[0]
  alphabetString = fsaData[1].strip()
  alphabet = alphabetString.replace(",", " ")
  
  formattedTransitionData = sub("[()]", "", fsaData[2])
  transitionSet = "(" + formattedTransitionData.replace(",", ") (") + ")"
  transitionSet = transitionSet.replace(":", " ")
  startState = fsaData[3]
  acceptingStateString = fsaData[4]
  acceptingStateSet = acceptingStateString.replace(",", " ")
  # for i, state in enumerate(acceptingStateSet):
  #   acceptingStateSet[i] = int(state)
  return (numStates, alphabet, startState, transitionSet, acceptingStateSet)

def getSentenceFromFile(filename) -> str:
  with open(filename) as file:
    sentence = file.read()
  return sentence.strip()

def generateLispProgram(numStates, alphabet, startState, transitionSet, acceptingStateSet):
  banner = """;###################################################################
;# David Huson                                                     #
;# Programming Languages - COP 4020                                #
;# Project 4                                                       #
;# part2.lisp                                                      #
;# the python-generated lisp program to test strings with an fsa   #
;###################################################################\n"""
  fsaAssignment = f"(setq fsa '({transitionSet}))\n"
  initialStateAssignment = f"(setq initialState '({startState}))\n"
  acceptStatesAssignment = f"(setq acceptStates '({acceptingStateSet}))\n"
  alphabetAssignment = f"(setq alphabet '({alphabet}))\n\n"
  baseProgram = """(defun testFSA(inputStringAsList state)
  (cond 
    ((null inputStringAsList) 
      (if (member state acceptStates)
        (format nil "Accepted!")
      ;else
      (format nil "Not Accepted!"))
    )
    (t 
      (dolist (transition fsa)
        (setq c (car inputStringAsList))
        (setq tState (car transition))
        (setq token (caddr transition))
        (setq nState (cadr transition))
        (unless ;; if c is not in the alphabet, print "Not Accepted" and exit exicution
          (member c alphabet)
          (setq state -1) (return NIL) 
        )
        (if (eq T (applyTransition state))
            (setq state nState)
            ; else
            (format nil "Not Accepted!")
        )
      ) 
      (testFSA (cdr inputStringAsList) state)
    )
  )
)

(defun applyTransition (state)
  (if (and (eq state tState) (eq c token))
      ;; (setq state nState)
      (return-from applyTransition T)
      ; else
      (return-from applyTransition nil)
  )
)
(defun demo()
  (setq fp (open "theString.txt" :direction :input))
  (setq input (read fp nil))
  (princ "processing ")
  (princ input)
  (testFSA input (car initialState))
)"""

  program = banner + fsaAssignment + initialStateAssignment + acceptStatesAssignment + alphabetAssignment + baseProgram

  with open("part2.lsp", "w") as progFile:
    progFile.write(program)