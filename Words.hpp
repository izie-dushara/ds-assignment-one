#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Words
{
private:
	std::string *words;
	int size;

public:
	Words(const std::string &wordsFile, int arraySize);
	~Words();
	std::string getWord(int index) const;
	int getSize() const;
	bool contains(const std::string &words) const;
};