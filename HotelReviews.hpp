#ifndef HOTELREVIEWS_HPP
#define HOTELREVIEWS_HPP

#include <string>
#include "HotelReview.hpp"
class HotelReviews {
	private:
	HotelReview* hotelReviews;
	int arraySize;
	int count;	

	public:
	HotelReviews(int size, const std::string& hotelCsvFile);
	~HotelReviews();
	HotelReview getReview(int index) const;
	int getCount() const;
	void displayReviews(int numberOfReviews = 10) const;
};
#endif