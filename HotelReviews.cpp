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
		if (wordList[i] == targetWord)
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

						if (uniquePositiveWordCount % 100 == 0)
							std::cout << "Processing information. Might take a while. Grab a cup of coffee first~ \n";
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

	
	// insertionSort(positiveWordsList, positiveWordFrequencies, uniquePositiveWordCount);
	// insertionSort(negativeWordsList, negativeWordFrequencies, uniqueNegativeWordCount);
	mergeSort(positiveWordsList, positiveWordFrequencies, 0, uniquePositiveWordCount - 1);
	mergeSort(negativeWordsList, negativeWordFrequencies, 0, uniqueNegativeWordCount - 1);
	system("cls");
	std::cout << "Total Reviews: " << HotelReviews::getCount() - 2 << "\n";
	std::cout << "Total Counts of Positive Words Used = " << positiveCountOverall << "\n";
	std::cout << "Total Counts of Negative Words Used = " << negativeCountOverall << "\n";

	int limitPositive = std::min(uniquePositiveWordCount, 20);
	int limitNegative = std::min(uniqueNegativeWordCount, 20);

	std::cout << "Most Used Positive Words: ";
	for (size_t i = uniquePositiveWordCount - 1; i >= uniquePositiveWordCount - limitPositive; i--)
	{
		std::cout << positiveWordsList[i] << (i > uniquePositiveWordCount - limitPositive ? ", " : "\n");
	}

	std::cout << "Most Used Negative Words: ";
	for (size_t i = uniqueNegativeWordCount - 1; i >= uniqueNegativeWordCount - limitNegative; i--)
	{
		std::cout << negativeWordsList[i] << (i > uniqueNegativeWordCount - limitPositive ? ", " : "\n");
	}

	system("pause");

	std::cout << "Positive Word Frequencies: \n";
	for (int i = 0; i < uniquePositiveWordCount; i++)
	{
		std::cout << positiveWordsList[i] << " is used " << positiveWordFrequencies[i] << " times \n";
	}
	system("pause");
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

void HotelReviews::insertionSort(std::string wordList[], int frequencies[], int count)
{
	for (size_t i = 1; i < count; i++)
	{
		std::string targetWord = wordList[i];
		int wordFrequency = frequencies[i];
		int j = i - 1;

		while (j >= 0 && frequencies[j] > wordFrequency)
		{
			wordList[j + 1] = wordList[j];
			frequencies[j + 1] = frequencies[j];
			j--;
		}

		wordList[j + 1] = targetWord;
		frequencies[j + 1] = wordFrequency;
	}
}

void HotelReviews::merging(std::string wordList[], int frequencies[], int left, int middle, int right)
{
	int leftSize = middle - left + 1;
	int rightSize = right - middle;

	std::string *leftWords = new std::string[leftSize];
	int *leftFrequencies = new int[leftSize];
	std::string *rightWords = new std::string[rightSize];
	int *rightFrequencies = new int[rightSize];

	for (size_t i = 0; i < leftSize; i++)
	{
		leftWords[i] = wordList[left + i];
		leftFrequencies[i] = frequencies[left + i];
	}

	for (size_t j = 0; j < rightSize; j++)
	{
		rightWords[j] = wordList[middle + 1 + j];
		rightFrequencies[j] = frequencies[middle + 1 + j];
	}

	int i = 0;
	int j = 0;
	int k = left;

	while (i < leftSize && j < rightSize)
	{
		if (leftFrequencies[i] <= rightFrequencies[j])
		{
			wordList[k] = leftWords[i];
			frequencies[k] = leftFrequencies[i];
			i++;
		}
		else
		{
			wordList[k] = rightWords[j];
			frequencies[k] = rightFrequencies[j];
			j++;
		}
		k++;
	}

	while (i < leftSize)
	{
		wordList[k] = leftWords[i];
		frequencies[k] = leftFrequencies[i];
		i++;
		k++;
	}

	while (j < rightSize)
	{
		wordList[k] = rightWords[j];
		frequencies[k] = rightFrequencies[j];
		j++;
		k++;
	}

	delete[] leftWords;
	delete[] leftFrequencies;
	delete[] rightWords;
	delete[] rightFrequencies;
}

void HotelReviews::mergeSort(std::string wordList[], int frequencies[], int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int middle = left + (right - left) / 2;

	mergeSort(wordList, frequencies, left, middle);
	mergeSort(wordList, frequencies, middle + 1, right);

	merging(wordList, frequencies, left, middle, right);
}