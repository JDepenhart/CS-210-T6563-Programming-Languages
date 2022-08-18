#include "FileData.h"
#include <string>

using namespace std;

void FileData::SetItemName(string itemName)
{
	this->itemName = itemName;
}

void FileData::SetItemFrequency(int itemFrequency)
{
	this->itemFrequency = itemFrequency;
}

string FileData::GetItemName()
{
	return itemName;
}

int FileData::GetItemFrequency()
{
	return itemFrequency;
}
