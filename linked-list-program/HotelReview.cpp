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

int HotelReview::getIndex() const
{
	return this->reviewIndex;
}

std::string HotelReview::getReview() const
{
	return this->reviewDescription;
}
int HotelReview::getRating() const
{
	return this->reviewRating;
}

HotelReview::~HotelReview()
{
}