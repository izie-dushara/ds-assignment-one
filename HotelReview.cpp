#include "HotelReview.hpp"
#include <iostream>

HotelReview::HotelReview()
{
	reviewIndex = 0;
	reviewDescription = "";
	reviewRating = 0;
}

HotelReview::HotelReview(int reviewIndex, std::string reviewDescription, int reviewRating)
{
	this->reviewIndex = reviewIndex;
	this->reviewDescription = reviewDescription;
	this->reviewRating = reviewRating;
}

void HotelReview::setHotelReview(int reviewIndex, std::string reviewDescription, int reviewRating)
{
	this->reviewIndex = reviewIndex;
	this->reviewDescription = reviewDescription;
	this->reviewRating = reviewRating;
}

void HotelReview::displayHotelReview()
{
	std::cout << "Hotel Review: " << reviewDescription;
}

HotelReview::~HotelReview()
{
	std::cout << "Deleted: " << this->reviewIndex;
}