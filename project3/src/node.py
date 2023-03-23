###############################################################################
# David Huson                                                                 #
# Project 3                                                                   #
# node.py                                                                     #
# 3/20/23                                                                     #
# Class file to define a Circle and a Node. A node is a Circle, and also has  #
# the ability to be an accepting node, and/or an initial node. This class     #
# also provides getters for the position of the node on the canvas, as well   #
# as its radius and label.                                                    #
###############################################################################

class Circle:
  def __init__(self, x:int, y:int, r:float) -> None:
    self.x = x
    self.y = y
    self.r = r
    
class Node(Circle):
  def __init__(self, label:str, x:int, y:int, r:float, acceptingState:bool = False, initialState:bool = False) -> None:
    self.label = label
    self.isAcceptingState = acceptingState
    self.isInitialState = initialState
    super().__init__(x, y, r)
  
  def setAsAcceptingState(self) -> None:
    self.acceptingState = True
    
  def setAsInitialState(self) -> None:
    self.acceptingState = True
    
  def pos(self) -> list:
    return self.x, self.y
  
  def getLabel(self) -> str:
    return self.label
  
  def getRadius(self) -> float:
    return self.r