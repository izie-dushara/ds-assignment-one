#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "LinkedListCustom.hpp"

class Words
{
private:
	LinkedListCustom<std::string> words;
	int size;

public:
	Words(const std::string &wordsFile);
	~Words();
	std::string getWord(int index) const;
	int getSize() const;
	bool contains(const std::string &words) const;
};