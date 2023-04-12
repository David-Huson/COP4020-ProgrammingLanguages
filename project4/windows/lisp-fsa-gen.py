###############################################################################
# David Huson                                                                 #
# Project 3                                                                   #
# driver.py                                                                   #
# 3/20/23                                                                     #
#                                                                             #
# The entry point for the program. Gets the fsa definition string from the    #
# file specified in the first command line argument after the program name    #
# tests the string given in the text file passed in the second command line   #
# argument, and calls the drawGraph function to create the gui representation #
###############################################################################
from utilities import *
import sys

if __name__ == "__main__":
  fsaDescriptionFile = sys.argv[1]
  numStates, alphabet, startState, transitions, acceptingStates = tokenize(fsaDescriptionFile)
  generateLispProgram(numStates, alphabet, startState, transitions, acceptingStates)