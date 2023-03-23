###############################################################################
# David Huson                                                                 #
# Project 3                                                                   #
# arrow.py                                                                    #
# 3/20/23                                                                     #
# This file defines a class for an arrow. The arrow is implemented using the  #
# tkinter canvas' create_line method. When initialized the arrow will draw    #
# a corresponding arrow from the given x1, y1 corrdinates, to the x2, y2      #
# coordinates. If the arrow needs to travel more than a single node length,   #
# an optional parameter may be passed to say it is to be curved and what 
# direction is is pointing. These methods calculate an intermediate point to  #
# send the line through and use the create_line method's optional smooth      #
# parameter to smoothly curve the line. This class also places the transition #
# label on the arrow at a constant offset from the line.
###############################################################################

# import tkinter as tk 
from tkinter import Canvas, LAST
class Arrow():
    def __init__(self, canvas:Canvas, x1:int, y1:int, x2:int=0, y2:int=0, r:int=0, label:str="", shapeOffset=50,
                 numArchedUp:int=1, numArchedDown:int=1, isPointedUp=False, isPointedDown=False, isCurvedDown=False, isCurvedUp=False, isLoop=False) -> None:
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.r = r
        self.label = label
        self.canvas = canvas
        self.textOffset = 10
        self.offset = shapeOffset
        self.numArchedDown = numArchedDown
        self.numArchedUp = numArchedUp
        if(isPointedDown):
            self.straightDown()
        elif(isLoop):
            self.loop()
        elif(isCurvedUp):
            self.curvedUp()
        elif(isCurvedDown):
            self.curvedDown()
        elif(isPointedUp):
            self.straightUp()
    
    def straightDown(self):
        coords = self.x1 + self.r/2, self.y1 + self.r, self.x2 + self.r/2, self.y2
        self.canvas.create_line(coords, fill="black", width=2, arrow=LAST)
        self.canvas.create_text(self.x2 + self.r/2 + self.textOffset, self.y1 + self.r/2 + (abs(self.y2 - self.y1)/2) - self.textOffset,text=self.label, fill="black")

    def straightUp(self):
        coords = self.x1 + self.r/2, self.y1, self.x2 + self.r/2, self.y2 + self.r
        self.canvas.create_line(coords, fill="black", width=2,  arrow=LAST)
        self.canvas.create_text( self.x2 + self.r/2 + self.textOffset, self.y2 + self.r/2 + (abs(self.y2 - self.y1)/2), text=self.label, fill="black")

    def curvedDown(self):
        print(f"offset = {self.offset * self.numArchedDown}")
        self.xm = self.x1 + self.r + self.offset * self.numArchedDown
        self.ym = (self.y1 - self.y2) / 2
        coords = self.x1 + self.r, self.y1 + self.r/2, self.xm, self.ym  + self.y2, self.x2 + self.r, self.y2 + self.r/2
        self.canvas.create_line(coords, fill="black", smooth=1, splinesteps=128, width=2, arrow=LAST)
        self.canvas.create_text(self.xm - self.textOffset * 3 * self.numArchedDown, self.ym  + self.y2 + self.textOffset, text=self.label, fill="black")

    def curvedUp(self):
        self.xm = self.x1 - (self.offset * self.numArchedUp)
        self.ym = (self.y1 - self.y2) / 2
        coords = self.x1, self.y1 + self.r/2, self.xm, self.ym  + self.y2, self.x2, self.y2 + self.r/2
        self.canvas.create_line(coords, fill="black", smooth=1, splinesteps=128, width=2, arrow=LAST)
        self.canvas.create_text(self.xm + self.textOffset * 3 * self.numArchedUp, self.ym  + self.y2 + self.textOffset,text=self.label, fill="black")

    def loop(self):
        coords = self.x1+self.r, self.y1 + self.r/2, self.x1 + (1.5 * self.r), self.y1 - self.r/2, self.x1 + self.r/2, self.y1
        self.canvas.create_line(coords, fill="black", smooth=1, splinesteps=128, width=2, arrow=LAST)
        self.canvas.create_text(self.x1 + (1.5 * self.r) - self.textOffset, self.y1 - self.r/2 + self.textOffset, text=self.label, fill="black")