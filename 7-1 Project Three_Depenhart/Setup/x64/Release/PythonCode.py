from collections import Counter
from fileinput import filename
import fileinput
import re
import string

def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

# Creates a list based on a file
def CreateList(v):
    itemList = [] # list declaration

    # Opens and reads the file
    with open(v, 'r') as rf:
        #Loops through each file line and adds it to the list
        for line in rf.readlines():
            lineTest = line.strip()
            itemList.append(lineTest)
    rf.close() # closes the file

    return itemList 

# Displays a list of each item and how many of them were purchased
def DisplayList(v): 
    myList = CreateList(v) # Sets myList to the return value of CreateList(v)

    # Loops through each item in myList, sorts them and adds them to a set
    for i in sorted(set(myList)):
        print(myList.count(i), i) # prints current Item purchase frequency and item name

    return 0

# Gets an item from the user and prints its purchase frequency
def CountItem(v):
    item = input("Enter the item name: ") # Gets item input from User
    myList = CreateList(v) # Sets myList to the return value of CreateList(v)

    print(item, "were purchased ", myList.count(item), " time(s)") #Prints the Item name and how many times it appears on mylist

    return 0

def CreateHistogram(v):
    myList = CreateList(v) # Sets myList to the return value of CreateList(v)
    
    with open('frequency.dat', 'w') as wf:
        for i in sorted(set(myList)):
            wf.write(i)
            wf.write(" ")
            stringNum = "{}".format(myList.count(i))
            wf.write(stringNum)
            wf.write("\n")
    wf.close()

    return 0
