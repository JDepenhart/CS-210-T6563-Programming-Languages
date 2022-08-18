#pragma once

#include <string>

using namespace std;

class FileData
{
	public:
		void SetItemName(string itemName);
		void SetItemFrequency(int itemFrequency);
		string GetItemName();
		int GetItemFrequency();
	private:
		string itemName;
		int itemFrequency;
};

