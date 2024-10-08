#include <iostream>
#include <fstream>
#include <string>
#include "SizeConstants.hpp"
#include "HotelReviews.hpp"
#include "Words.hpp"

int main()
{
	std::string hotelCsvFile = "tripadvisor_hotel_reviews.csv";

	HotelReviews reviewsCollection(SizeConstants::CsvFileSize, hotelCsvFile);

	HotelReview reviewDescription = reviewsCollection.getReview(3);
	std::cout << reviewsCollection.getReview(3).getReview();

	reviewsCollection.getReview(3);
	std::cout << reviewsCollection.getCount();

	const int ARRAYSIZE = 100;
	std::string filename = "positive-words.txt";
	Words positivieWords(filename, SizeConstants::PositiveFileSize);

	// for (size_t i = 0; i < positivieWords.getSize(); i++)
	// {
	// 	std::cout << positivieWords.getWord(i) << std::endl;
	// }

	return 0;
}