#include <iostream>
#include <fstream>
#include <string>
#include "HotelReviews.hpp"

int main() 
{
	const int ARRAYSIZE = 20500;
	std::string hotelCsvFile = "tripadvisor_hotel_reviews.csv";

	HotelReviews reviewsCollection(ARRAYSIZE, hotelCsvFile);

	HotelReview reviewDescription = reviewsCollection.getReview(3);
	std::cout << reviewsCollection.getReview(3).getReview();

	reviewsCollection.getReview(3);
	


	return 0;
}