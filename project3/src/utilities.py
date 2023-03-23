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
  alphabet = alphabetString.split(",")
  
  formattedTransitionData = sub("[()]", "", fsaData[2])
  transitionSet = formattedTransitionData.split(",")
  startState = int(fsaData[3])
  acceptingStateString = fsaData[4]
  acceptingStateSet = acceptingStateString.split(",")
  for i, state in enumerate(acceptingStateSet):
    acceptingStateSet[i] = int(state)
  return (numStates, alphabet, startState, transitionSet, acceptingStateSet)

def getSentenceFromFile(filename) -> str:
  with open(filename) as file:
    sentence = file.read()
  return sentence.strip()