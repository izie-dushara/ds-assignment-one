#ifndef WORDS_HPP
#define WORDS_HPP

#include <iostream>
#include <string>
#include <fstream>

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
};

#endif