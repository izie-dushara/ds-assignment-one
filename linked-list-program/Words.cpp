#include "Words.hpp"

Words::Words(const std::string &wordsFile, int arraySize)
	: size(arraySize)
{
	words = new std::string[size];
	std::ifstream wordsTxtFile(wordsFile);
	std::string line;
	int index = 0;

	if (wordsTxtFile.is_open())
	{
		while (std::getline(wordsTxtFile, line) && index < size)
		{
			words[index] = line;
			index++;
		}
		wordsTxtFile.close();
	}
	else
	{
		std::cout << "Error: Could not open file" << wordsFile << "\n";
		return;
	}
}

Words::~Words()
{
	delete[] words;
}

std::string Words::getWord(int index) const
{
	if (index >= 0 && index < size)
	{
		return words[index];
	}
	return "";
}

int Words::getSize() const
{
	return size;
}

bool Words::contains(const std::string &words) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (Words::getWord(i) == words)
			return true;
	}
	return false;
}