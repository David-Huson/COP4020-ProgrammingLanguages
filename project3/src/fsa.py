###############################################################################
# David Huson                                                                 #
# Project 3                                                                   #
# fsa.py                                                                      #
# 3/20/23                                                                     #
# The Automoaton class defines a finite state automoaton, given the necessary #
# attributes. The class provides a method of validating a word/sentence in    #
# given language, as well as a method to draw the graph representation of the #
# automaton.                                                                  #
###############################################################################

from transition import *
from gui import *
from node import *


class Automaton:
    def __init__(self, numStates: int, alphabet: list[str], transitions: list, initialState: int, acceptingStates: list[int]):
        self.alphabet = alphabet
        self.initialState = initialState
        self.acceptingStates = acceptingStates
        self.transitions = transitions
        self.nodes: list[Node] = []
        self.numStates = int(numStates)
        self.transitionLabels: list[str] = []
        self.transitionList = self.createTransitionList()
        self.createAdjacencyList()
        y_offset = 100
        x_offset = 150
        for i in range(numStates):
            isAcceptingState = (i in self.acceptingStates)
            isInitialState = i == initialState
            label = f'q{i}'
            self.nodes.append(Node(label, x_offset, (i + 1) * y_offset, 50, isAcceptingState, isInitialState))

    def createTransitionList(self):
        transitionsList = []
        for transitionString in self.transitions:
            transitionString = transitionString.split(":")
            startState = int(transitionString[0])
            endState = int(transitionString[1])
            transitionToken = transitionString[2]
            if(startState < 0 or startState >= self.numStates):
                print("Error, the start state is not a valid state for this FSA! Please try again.")
                return []
            if(endState < 0 or endState >= self.numStates):
                print("Error, the end state is not a valid state for this FSA! Please try again.")
                return []
            if(transitionToken not in self.alphabet):
                print("Error, the transition token is not in the alphabet! Please try again.")
                return []
            transitionsList.append(Transition(startState, endState, transitionToken))
        return transitionsList

    def addEdge(self, s: int, d: int):
        self.adjacencyList[int(s)].append(int(d))

    def createAdjacencyList(self):
        self.adjacencyList = [0]* self.numStates
        for i in range(0, self.numStates):
            self.adjacencyList[i] = []

        for edge in self.transitionList:
            self.addEdge(edge.getStartState(), edge.getEndState())

    def drawGraph(self):
        self.graph = Graph(self.numStates, self.nodes, self.adjacencyList, self.transitionLabels)

    def testSentence(self, sentence):
        currentState = self.initialState
        for char in sentence:
            # if the character is not in the alphabet, the sentence is not contained in the language
            if char not in self.alphabet:
                currentState = -1
                # return False
                break
            
            for transition in self.transitionList:
                # if there is a transition defined from the current state and token, perform it
                self.transitionLabels.append(transition.getTransitionToken())
                if currentState == transition.getStartState() and char == transition.getTransitionToken():
                    currentState = transition.getEndState()
                    break

        # print(currentState)
        # if we are in an accepting state after parsing the whole sentence, the sentence is contained in the language
        if currentState in self.acceptingStates:
            print(f"'{sentence}' is accepted in the given language!")
        else:
            print(f"'{sentence}' is *not* accepted in the given language!")
