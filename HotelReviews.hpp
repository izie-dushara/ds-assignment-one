#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "HotelReview.hpp"
#include "Words.hpp"

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
	void calculateWordFrequencies(const Words &positiveWords, const Words &negativeWords);
};