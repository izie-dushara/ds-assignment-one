#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include "HotelReview.hpp"
#include "Words.hpp"
#include "LinkedListCustom.hpp"

class HotelReviews
{
private:
	LinkedListCustom<HotelReview> hotelReviews;
	const int MAXWORDS = 10000;

public:
	HotelReviews(const std::string &hotelCsvFile);
	~HotelReviews();
	HotelReview getReview(int index) const;
	int getCount() const;
	void calculateWordFrequencies(const Words &positiveWords, const Words &negativeWords);
	void analyzeSingleReview(const Words &positiveWords, const Words &negativeWords);
	double calculateSentimentScore(int positiveWordCount, int negativeWordCount);
	int findWordIndex(const std::string &word, std::string wordList[], int wordCount);
	void insertionSort(std::string wordList[], int frequencies[], int count);
	void merging(std::string wordList[], int frequencies[], int left, int middle, int right);
	void mergeSort(std::string wordList[], int frequencies[], int left, int right);
};