#include <iostream>
#include <fstream>
#include <string>
#include "HotelReview.hpp"

int main() 
{
	const int ARRAYSIZE = 20500;
	std::string reviewWholeLine;
	std::string reviewDescription;  	
	std::string reviewRating;
	

	HotelReview *hotelReviewArr = new HotelReview[ARRAYSIZE];

	std::ifstream hotelCsvFile("tripadvisor_hotel_reviews.csv");	

	int index = 0;

	std::string csvHeader;
	getline(hotelCsvFile, csvHeader);

	while (getline(hotelCsvFile, reviewWholeLine))
	{
		// Find lass comma in the line
		size_t lastCommaPosition = reviewWholeLine.find_last_of(',');

		if (lastCommaPosition != std::string::npos)
		{
			reviewDescription = reviewWholeLine.substr(0, lastCommaPosition);
			reviewRating = reviewWholeLine.substr(lastCommaPosition + 1);
		}
		else
		{
			continue;
		}

		// Process the review and rating
		hotelReviewArr[index].setHotelReview(index + 1, reviewDescription, std::stod(reviewRating));
		index++;

		if (index >= ARRAYSIZE)	
			break;
	}

	for (size_t i = 0; i < std::min(index, 10); i++)
	{
		hotelReviewArr[i].displayHotelReview();
	}
	return 0;
}