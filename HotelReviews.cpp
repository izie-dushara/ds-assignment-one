#include "HotelReviews.hpp"
#include "HotelReview.hpp"

HotelReviews::HotelReviews(int size, const std::string &hotelCsvFile)
	: arraySize(size), count(0)
{
	hotelReviews = new HotelReview[arraySize];

	std::ifstream reviewCsvFile(hotelCsvFile);
	if (!reviewCsvFile.is_open())
	{
		std::cout << "Error: Could not open file" << hotelCsvFile << "\n";
		return;
	}

	std::string reviewWholeLine;
	std::string reviewDescription;
	std::string reviewRating;

	std::string csvHeader;
	getline(reviewCsvFile, csvHeader);

	while (getline(reviewCsvFile, reviewWholeLine) && count < arraySize)
	{
		size_t lastCommaPositon = reviewWholeLine.find_last_of(',');

		if (lastCommaPositon != std::string::npos)
		{
			reviewDescription = reviewWholeLine.substr(0, lastCommaPositon);
			reviewRating = reviewWholeLine.substr(lastCommaPositon + 1);

			hotelReviews[count].setHotelReview(count + 1, reviewDescription, std::stod(reviewRating));
			count++;
		}
	}
	reviewCsvFile.close();
}

HotelReviews::~HotelReviews()
{
	delete[] hotelReviews;
}

HotelReview HotelReviews::getReview(int index) const
{
	if (index >= 0 && index < count)
		return hotelReviews[index];
	return HotelReview();
}

int HotelReviews::getCount() const
{
	return count;
}

int HotelReviews::findWordIndex(const std::string &targetWord, std::string wordList[], int wordCount)
{
	for (int i = 0; i < wordCount; i++)
	{
		if(wordList[i] == targetWord)
			return i;
	}

	return -1;
}

void HotelReviews::calculateWordFrequencies(const Words &positiveWords, const Words &negativeWords)
{
	int positiveCountOverall = 0;
	int negativeCountOverall = 0;

	std::string positiveWordsList[10000];
	int positiveWordFrequencies[10000] = {0};
	int uniquePositiveWordCount = 0;

	std::string negativeWordsList[10000];
	int negativeWordFrequencies[10000] = {0};
	int uniqueNegativeWordCount = 0;

	for (size_t i = 0; i < HotelReviews::getCount(); i++)
	{
		std::string hotelReview = hotelReviews[i].getReview();
		std::istringstream iss(hotelReview);
		std::string targetWord;
		while (iss >> targetWord)
		{
			targetWord.erase(remove_if(targetWord.begin(), targetWord.end(), ispunct), targetWord.end());

			if (positiveWords.contains(targetWord))
			{
				int wordIndex = findWordIndex(targetWord, positiveWordsList, uniquePositiveWordCount);
				if (wordIndex != -1)
				{
					positiveWordFrequencies[wordIndex]++;
				} 
				else
				{
					if (uniquePositiveWordCount < 10000)
					{
						positiveWordsList[uniquePositiveWordCount] = targetWord;
						positiveWordFrequencies[uniquePositiveWordCount] = 1;
						uniquePositiveWordCount++;
						std::cout << uniquePositiveWordCount;
					}
					else
					{
						std::cout << "Warning: Maximum positive word limit reached.\n";
					}
				}
				positiveCountOverall++;
			}
			else if (negativeWords.contains(targetWord))
			{
				int wordIndex = findWordIndex(targetWord, negativeWordsList, uniqueNegativeWordCount);
				if (wordIndex != -1)
				{
					negativeWordFrequencies[wordIndex]++;
				}
				else
				{
					if (uniqueNegativeWordCount < 10000)
					{
						negativeWordsList[uniqueNegativeWordCount] = targetWord;
						negativeWordFrequencies[uniqueNegativeWordCount] = 1;
						uniqueNegativeWordCount++;
					}
					else
					{
						std::cout << "Warning: Maximum negative word limit reached'\n";
					}
				}
				// std::cout << targetWord;
				negativeCountOverall++;
			}
		}
	}

	system("cls");
	std::cout << "Total Reviews: " << HotelReviews::getCount() - 2 << "\n";
	std::cout << "Total Counts of Positive Words Used = " << positiveCountOverall << "\n";
	std::cout << "Total Counts of Negative Words Used = " << negativeCountOverall << "\n";

	std::cout << "Positive Word Frequencies: \n";
	for (int i = 0; i < uniquePositiveWordCount; i++)
	{
		std::cout << positiveWordsList[i] << " is used " << positiveWordFrequencies[i] << " times \n";
	}
	std::cout << "Negative Word Frequencies: \n";
	for (int i = 0; i < uniqueNegativeWordCount; i++)
	{
		std::cout << negativeWordsList[i] << " is used " << negativeWordFrequencies[i] << " times \n";
	}

}

// Display reviews (for debugging or output)
void HotelReviews::displayReviews(int numberOfReviews) const
{
	for (size_t i = 0; i < std::min(count, numberOfReviews); i++)
	{
		std::cout << hotelReviews[i].getIndex() << ": "
				  << hotelReviews[i].getReview() << " - Rating: "
				  << hotelReviews[i].getRating() << "\n";
	}
}