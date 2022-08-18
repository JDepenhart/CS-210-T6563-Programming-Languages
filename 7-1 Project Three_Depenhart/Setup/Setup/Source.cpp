#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include "FileData.h"

using namespace std;
/*
* Jeremy Depenhart 
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// Used the fill an area with a character
string nCharString(size_t n, char c) {
	string fillString;
	fillString = string(n, c); // makes fill string the length of n and fills with with c

	return fillString;
}

// Reads the .dat file generated by def CreateHistogram(v) in python
void ReadFile(vector<FileData>& item) {
	ifstream inFS;
	string itemName;
	int itemFrequency;
	FileData currentData;

	inFS.open("frequency.dat"); // Opens file

	// checks if the file didnt open (does not exist)
	if (!inFS.is_open()) { 
		cout << "Could not open file" << endl;
	}

	// loops unitle the end of the file is reached
	while (!inFS.eof()) {
		inFS >> itemName; // gets item name from current item in the file
		inFS >> itemFrequency; // gets item frequency from current item in the file

		// if inFS does not fail
		if (!inFS.fail()) {
			currentData.SetItemName(itemName); // sets Item Name for currentData
			currentData.SetItemFrequency(itemFrequency); // sets Item Frequency for currentData

			item.push_back(currentData); 
		}
	}

	inFS.close(); //closes file
}

// Displays the Histogram
void DisplayHistogram(vector<FileData> item) {
	// loops through each item in the FileData Vector
	for (int i = 0; i < item.size(); ++i) {
		cout << item[i].GetItemName() << " "; // Outputs item name followed by a space
		cout << nCharString(item[i].GetItemFrequency(), '*') << endl; // Outputs a line of *'s equal in width to the item frequency
	}
}

// Main Menu
void menu() {
	vector<FileData> item;
	int selection;
	bool displayMenu = true;

	// Loops untils displayMenu bool is set to false
	while (displayMenu) {
		// Outputs menu options
		cout << "1: Veiw list of all purchased items" << endl;
		cout << "2: Search for an Item" << endl;
		cout << "3: View histogram of all purchased items" << endl;
		cout << "4: Exit program" << endl;
		cout << "Enter a number: ";

		cin >> selection; // Gets input from user
		
		// Checks if user enters proper input variable
		if (!cin.good()) { // If user does not enter a number
			cout << endl;
			cin.clear();
			cin.ignore();
			cout << "error, please enter a Valid menu option" << endl; // error message for input
			cout << endl;
		}
		else {
			// Handles cases based on user input 
			switch (selection) {
			default: // Happens if any input is entered other than 1, 2, 3, or 4
				cout << endl;
				cout << "error, please enter a Valid menu option" << endl; // error message for input
				cout << endl;
				break;
			case 1: // happens if 1 is entered
				cout << endl;
				callIntFunc("DisplayList", "Input.txt"); // calls DisplayList() in python
				cout << endl;
				break;
			case 2: // happens if 2 is entered
				cout << endl;
				callIntFunc("CountItem", "Input.txt"); // calls CountItem() in python
				cout << endl;
				break;
			case 3: // happens if 3 is entered
				cout << endl;
				callIntFunc("CreateHistogram", "Input.txt"); // calls CreateHistogram() in python
				ReadFile(item); // Calls ReadFile() 
				DisplayHistogram(item); // Calls DisplayHistogram()
				cout << endl;
				break;
			case 4: // happens if 4 is entered
				cout << "Have a nice day!" << endl;
				displayMenu = false; // Exits loop
				break;
			}
		}
	}
}

void main()
{
	system("Color 0A"); // Makes output color Green
	menu();
}