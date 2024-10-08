#include <iostream>
#include <fstream>
#include <string>
#include "SizeConstants.hpp"
#include "HotelReviews.hpp"
#include "Words.hpp"

int main()
{
	std::string hotelCsvFile = "tripadvisor_hotel_reviews.csv";
	std::string positiveWordsTxt = "positive-words.txt";
	std::string negativeWordsTxt = "negative-words.txt";

	HotelReviews reviewsCollection(SizeConstants::CsvFileSize, hotelCsvFile);
	Words positiveWordsArray(positiveWordsTxt, SizeConstants::PositiveFileSize);
	Words negativeWordsArray(negativeWordsTxt, SizeConstants::NegativeFileSize);

    reviewsCollection.calculateWordFrequencies(positiveWordsArray, negativeWordsArray);
	return 0;
}