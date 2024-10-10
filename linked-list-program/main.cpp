#include <iostream>
#include <fstream>
#include <string>
#include "SizeConstants.hpp"
#include "HotelReviews.hpp"
#include "Words.hpp"

int main()
{
	const std::string hotelCsvFile = "tripadvisor_hotel_reviews.csv";
	const std::string positiveWordsTxt = "positive-words.txt";
	const std::string negativeWordsTxt = "negative-words.txt";

	HotelReviews reviewsCollection(hotelCsvFile);
	Words positiveWordsArray(positiveWordsTxt);
	Words negativeWordsArray(negativeWordsTxt);

	int choice = 0;

	do
	{

		std::cout << "\nWhat do you want to do?\n";
		std::cout << "1. Read Reviews with Sentiment Score\n";
		std::cout << "2. Display Review Based on Total Count of Positive and Negative Words\n";
		std::cout << "3. Exit\n";
		std::cout << "Enter your choice: ";

		if (!(std::cin >> choice) || choice < 1 || choice > 3)
		{

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid choice! Choice should be between 1 to 3.\n";
		}
		else
		{
			switch (choice)
			{
			case 1:
				reviewsCollection.analyzeSingleReview(positiveWordsArray, negativeWordsArray);
				break;
			case 2:
				reviewsCollection.calculateWordFrequencies(positiveWordsArray, negativeWordsArray);
				break;
			case 3:
				std::cout << "Exiting program. Hava a good day!\n";
				break;
			default:
				std::cout << "Invalid choice. Please try again \n";
				break;
			}
		}

	} while (choice != 3);

	return 0;
}