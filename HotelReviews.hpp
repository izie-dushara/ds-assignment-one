#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "HotelReview.hpp"
#include "Words.hpp"

class HotelReviews
{
private:
	HotelReview *hotelReviews;
	int arraySize;
	int count;
	const int MAXWORDS = 10000;

public:
	HotelReviews(int size, const std::string &hotelCsvFile);
	~HotelReviews();
	HotelReview getReview(int index) const;
	int getCount() const;
	void displayReviews(int numberOfReviews = 10) const;
	void calculateWordFrequencies(const Words &positiveWords, const Words &negativeWords);
	int findWordIndex(const std::string &word, std::string wordList[], int wordCount);
	void insertionSort(std::string wordList[], int frequencies[], int count);
};