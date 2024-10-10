#include "Words.hpp"

Words::Words(const std::string &wordsFile)
{
	std::ifstream wordsTxtFile(wordsFile);
	std::string line;
	int index = 0;

	if (wordsTxtFile.is_open())
	{
		while (std::getline(wordsTxtFile, line) && index < size)
		{
			words.add(line);
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
}

std::string Words::getWord(int index) const
{
	return words.get(index);
}

int Words::getSize() const
{
	return words.getSize();
}

bool Words::contains(const std::string &words) const
{
	for (size_t i = 0; i < Words::getSize(); i++)
	{
		if (Words::getWord(i) == words)
			return true;
	}
	return false;
}