def getFsaData(filename):
  with open(filename) as fsaFile:
    data = fsaFile.read()
  print(data)
  splitData = data.split(";")
  numStates = splitData[0]
  print(numStates)
  alphabet = splitData[1].strip()
  print(alphabet)
  transitionSet = splitData[2].split(",")
  print(transitionSet)
  startState = splitData[3]
  print(startState)
  acceptingStateSet = splitData[4]
  print( acceptingStateSet)
			
getFsaData("./fsa.txt")