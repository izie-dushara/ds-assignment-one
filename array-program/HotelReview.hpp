#pragma once

#include <string>

class HotelReview {
	private:
	int reviewIndex;
	std::string reviewDescription;
	int reviewRating;

	public:
	HotelReview();
	HotelReview(int reviewIndex, std::string reviewDescription, int reviewRating);
	~HotelReview();
	void setHotelReview(int reviewIndex, std::string reviewDescription, int viewRating);
	int getIndex() const;
	std::string getReview() const;
	int getRating() const;
};