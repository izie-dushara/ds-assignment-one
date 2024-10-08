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

void HotelReviews::calculateWordFrequencies(const Words &positiveWords, const Words &negativeWords)
{
	int positiveCountOverall = 0;
	int negativeCountOverall = 0;

	for (size_t i = 0; i < HotelReviews::getCount(); i++)
	{
		std::string hotelReview = hotelReviews[i].getReview();
		std::istringstream iss(hotelReview);
		std::string targetWord;
		while (iss >> targetWord)
		{
			targetWord.erase(remove_if(targetWord.begin(), targetWord.end(), ispunct), targetWord.end());

			if (positiveWords.contains(targetWord))
				positiveCountOverall++;
			else if (negativeWords.contains(targetWord))
				negativeCountOverall++;
		}
	}

	std::cout << "Total Reviews: " << HotelReviews::getCount() - 2;
	std::cout << "Total Counts of Positive Words Used = " << positiveCountOverall << "\n";
	std::cout << "Total Counts of Negative Words Used = " << negativeCountOverall << "\n";
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