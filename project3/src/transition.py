###############################################################################
# David Huson                                                                 #
# Project 3                                                                   #
# transition.py                                                               #
# 3/20/23                                                                     #
# The Transition class defines a state change from one state to another and a #
# Token needed to transition from the start state to the end State. The class #
# Provides methods to get all this data.                                      #
###############################################################################

class Transition:
    def __init__(self, startState, endState, transitionToken):
        self.__startState = int(startState)
        self.__endState = int(endState)
        self.__transitionToken = str(transitionToken)
    
    """
    Returns the starting state for this transition

    """
    def getStartState(self) -> int:
        return self.__startState
    
    """
    returns the end state for this transition  
    """
    def getEndState(self) -> int:
        return self.__endState
    
    """
    [return]: returns the token to trigger this transition  
    """
    def getTransitionToken(self) -> str:
        return self.__transitionToken