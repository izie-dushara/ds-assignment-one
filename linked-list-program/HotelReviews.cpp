#include "HotelReviews.hpp"
#include "HotelReview.hpp"

HotelReviews::HotelReviews(const std::string &hotelCsvFile)
	: hotelReviews()
{
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

	int index = 0;
	while (getline(reviewCsvFile, reviewWholeLine))
	{
		size_t lastCommaPositon = reviewWholeLine.find_last_of(',');

		if (lastCommaPositon != std::string::npos)
		{
			reviewDescription = reviewWholeLine.substr(0, lastCommaPositon);
			reviewRating = reviewWholeLine.substr(lastCommaPositon + 1);

			HotelReview newReview;
			newReview.setHotelReview(index + 1, reviewDescription, std::stod(reviewRating));
			hotelReviews.add(newReview);
			index++;
		}
	}
	reviewCsvFile.close();
}

HotelReviews::~HotelReviews()
{
	hotelReviews.clear();
}

HotelReview HotelReviews::getReview(int index) const
{
	return hotelReviews.get(index);
}

int HotelReviews::getCount() const
{
	return hotelReviews.getSize();
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

	auto startSearching = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < HotelReviews::getCount(); i++)
	{
		std::string hotelReview = hotelReviews.get(i).getReview();
		std::istringstream iss(hotelReview);
		std::string targetWord;
		std::cout << "Processing information. Might take a while (around null minutes). Grab a cup of coffee first~ \n";
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
							std::cout << "Processing information. Might take a while (around null minutes). Grab a cup of coffee first~ \n";
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
	auto stopSearching = std::chrono::high_resolution_clock::now();

	auto startSorting = std::chrono::high_resolution_clock::now();
	// insertionSort(positiveWordsList, positiveWordFrequencies, uniquePositiveWordCount);
	// insertionSort(negativeWordsList, negativeWordFrequencies, uniqueNegativeWordCount);
	mergeSort(positiveWordsList, positiveWordFrequencies, 0, uniquePositiveWordCount - 1);
	mergeSort(negativeWordsList, negativeWordFrequencies, 0, uniqueNegativeWordCount - 1);
	auto stopSorting = std::chrono::high_resolution_clock::now();
	system("cls");
	std::cout << "Total Reviews: " << HotelReviews::getCount() - 1 << "\n";
	std::cout << "Total Counts of Positive Words Used = " << positiveCountOverall << "\n";
	std::cout << "Total Counts of Negative Words Used = " << negativeCountOverall << "\n";
	auto durationSorting = std::chrono::duration_cast<std::chrono::microseconds>(stopSorting - startSorting);
	// std::cout << "Total Time Sorting Word With Insertion Sort Ascending = " << durationSorting.count() << " microseconds\n";
	std::cout << "Total Time Sorting Word With Merge Sort Ascending = " << durationSorting.count() << " microseconds\n";

	auto durationSearching = std::chrono::duration_cast<std::chrono::seconds>(stopSearching - startSearching);
	std::cout << "Total Time Searching and Organizing = " << durationSearching.count() << " seconds\n";

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

double HotelReviews::calculateSentimentScore(int positiveWordCount, int negativeWordCount)
{
	/**
	 * Raw Sentiment Score = positiveWordCount - NegativeWordCount
	 * N = positvieWordCount + negativeWordCount
	 * Min Raw Score = -N
	 * Max Raw Score = +N
	 *
	 * Normalized Score = (Raw Sentiment Score - Min Raw Score) / (Max Raw Score - Min Raw Score)
	 */

	double rawSentimentScore = positiveWordCount - negativeWordCount;
	double N = positiveWordCount + negativeWordCount;
	double minRawScore = -N;
	double maxRawScore = N;
	double normalizedScore = (rawSentimentScore - minRawScore) / (maxRawScore - minRawScore);

	double sentimentScore = 1 + (4 * normalizedScore);

	return sentimentScore;
}

void HotelReviews::analyzeSingleReview(const Words &positiveWords, const Words &negativeWords)
{
	int userInput;
	int userSearchReview;

	std::string positiveWordsList[50];
	int uniquePositiveWordCount = 0;

	std::string negativeWordsList[50];
	int uniqueNegativeWordCount = 0;

	do
	{
		std::cout << "Enter which review you want: ";
		std::cin >> userInput;
		userSearchReview = userInput - 1;

		if (std::cin.fail() || userSearchReview < 0 || userSearchReview > HotelReviews::getCount())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid Input! Reviews available is in range of 1 to 20 491!\n\n";
		}
	} while (userSearchReview < 0 || userSearchReview > HotelReviews::getCount());

	std::string reviewDisplay = hotelReviews.get(userSearchReview).getReview();
	reviewDisplay.erase(std::remove(reviewDisplay.begin(), reviewDisplay.end(), '\"'), reviewDisplay.end());

	std::cout << reviewDisplay << "\n";
	std::istringstream iss(reviewDisplay);
	std::string targetWord;
	while (iss >> targetWord)
	{
		targetWord.erase(remove_if(targetWord.begin(), targetWord.end(), ispunct), targetWord.end());
		if (positiveWords.contains(targetWord))
		{
			if (uniquePositiveWordCount < 10000)
			{
				positiveWordsList[uniquePositiveWordCount] = targetWord;
				uniquePositiveWordCount++;
			}
			else
			{
				std::cout << "Warning: Maximum positive word limit reached.\n";
			}
		}
		else if (negativeWords.contains(targetWord))
		{
			if (uniqueNegativeWordCount < 10000)
			{
				negativeWordsList[uniqueNegativeWordCount] = targetWord;
				uniqueNegativeWordCount++;
			}
			else
			{
				std::cout << "Warning: Maximum negative word limit reached'\n";
			}
		}
	}

	std::cout << "Positive Word Frequencies = " << uniquePositiveWordCount << "\n";
	for (int i = 0; i < uniquePositiveWordCount; i++)
	{
		std::cout << "- " << positiveWordsList[i] << "\n";
	}

	std::cout << "Negative Word Frequencies = " << uniqueNegativeWordCount << "\n";
	for (int i = 0; i < uniqueNegativeWordCount; i++)
	{
		std::cout << "- " << negativeWordsList[i] << "\n";
	}

	int calculatedSentimentScore = calculateSentimentScore(uniquePositiveWordCount, uniqueNegativeWordCount);
	std::cout << "Sentiment Score (1 - 5): " << calculatedSentimentScore << "\n";
	std::cout << "Rating Given By User: " << hotelReviews.get(userSearchReview).getRating() << "\n";
	system("pause");
	std::cout << "Analysis Output:\n";
	if (hotelReviews.get(userSearchReview).getRating() == calculatedSentimentScore)
	{
		std::cout << "User's subjective evaluation matches the sentiment score provided by the analysis. \n";
		std::cout << "There is a consistency between the sentiment score generated by the analysis and the user's evaluation of the sentiment.\n";
	}
	else
	{
		std::cout << "User's subjective evaluation does not match the sentiment score provided by the analysis. There is an inconsistency between the sentiment score generated by the analysis.\n";
		std::cout << "There is an inconsistency between the sentiment score generated by the analysis and the user's evaluation of the sentiment.\n";
	}
}
