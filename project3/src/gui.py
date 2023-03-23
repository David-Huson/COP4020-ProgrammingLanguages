###############################################################################
# David Huson                                                                 #
# Project 3                                                                   #
# gui.py                                                                      #
# 3/20/23                                                                     #
# Class file for a Graph gui. This class will create a gui representation of  #
# the Graph of a Finite automata. It takes parameters to define the number of #
# nodes to draw, the node objects themselves which define the coordinates of  #
# the node, the adjacency list for which nodes share an edge, and the list of #
# transition labels in the order of which they appear in the adjacency list.  #
# The gui is drawn using tkinter canvas and it's provided methods             #
###############################################################################

from transition import *
import tkinter as tk
from math import pi, sin, cos
from node import *
from arrow import Arrow

class Graph:

    def __init__(self, numNodes, nodes: list, adjacencyList: list, transitionLabels: list):
        self.root = tk.Tk()
        self.canvas = tk.Canvas(self.root, width=(
            150*numNodes) / 2, height=150 * numNodes, borderwidth=0, highlightthickness=0, bg="white")
        self.root.wm_title("Finite Automaton")
        self.adjacencyList = adjacencyList
        self.transitionLabels = transitionLabels
        self.labeledTransitions = 0
        self.numArchedUp = 0
        self.numArchedDown = 0
        self.nodes = nodes
        self.createEdges()
        for node in nodes:
            x, y = node.pos()
            self.createNode(node.getLabel(), x, y, node.getRadius(), node.isInitialState, node.isAcceptingState)
        self.canvas.pack()
        self.root.mainloop()
        
    def createEdges(self):
        for i in range(0, len(self.adjacencyList)):
            startNode = self.nodes[i]
            radius = startNode.getRadius()
            x1, y1 = startNode.pos()
            for j in  range(0, len(self.adjacencyList[i])):
                endNodeId = self.adjacencyList[i][j]
                x2, y2 = self.nodes[endNodeId].pos()
                # start node is above the end node
                diff = i - endNodeId
                if(diff == 0):
                    Arrow(self.canvas, x1=x1, y1=y1, r=radius, shapeOffset=radius, label=self.transitionLabels[self.labeledTransitions], isLoop=True)
                if(i < endNodeId and abs(diff) == 1):
                    Arrow(self.canvas, x1, y1, x2, y2, r=radius, shapeOffset=radius, label=self.transitionLabels[self.labeledTransitions], isPointedDown=True)
                # end node is above start node
                elif(i > endNodeId and abs(diff) == 1):
                    Arrow(self.canvas, x1, y1, x2, y2, r=radius, shapeOffset=radius, label=self.transitionLabels[self.labeledTransitions], isPointedUp=True)
                elif(diff > 1):
                    self.numArchedUp += 1
                    Arrow(self.canvas, x1, y1, x2, y2, r=radius, shapeOffset=radius, label=self.transitionLabels[self.labeledTransitions], numArchedUp=self.numArchedUp, isCurvedUp=True)
                elif(diff < -1):
                    self.numArchedDown += 1
                    Arrow(self.canvas, x1, y1, x2, y2, r=radius, shapeOffset=radius, label=self.transitionLabels[self.labeledTransitions], numArchedDown=self.numArchedDown, isCurvedDown=True)
                self.labeledTransitions += 1

    def createNode(self, id, x, y, r, initialNode=False, acceptingNode=False):
        self.canvas.create_oval(x, y, x + r, y+r, outline="black", fill="white")
        offset = 5
        if(acceptingNode):
            self.canvas.create_oval(x + offset, y + offset, x + r - offset, y+r - offset, outline="black", fill="white")
        if(initialNode):
            offset = 7
            self.canvas.create_polygon(x + offset, y + offset, x - r/2 - offset, y + offset, x + offset, y - r/2 - offset, fill="white", outline="black", width=2)
        self.canvas.create_text(x+r/2, y+r/2, text=id, fill="black")

