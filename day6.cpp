#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

constexpr uint8_t g_data1[] = {1, 1, 1, 2, 1, 5, 1, 1, 2, 1, 4, 1, 4, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 4, 1, 1, 5, 1, 3, 1, 2, 1, 1, 1, 2, 1, 1, 1, 4, 1, 1, 3, 1, 5, 1, 1, 1, 1, 3,
							   5, 5, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 5, 4, 1, 1, 1, 1, 1, 3, 1, 1, 2, 4, 4, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 5, 1, 3, 1, 5, 1, 2, 1, 1, 5, 1,
							   1, 1, 5, 3, 3, 1, 4, 1, 3, 1, 3, 1, 1, 1, 1, 3, 1, 4, 1, 1, 1, 1, 1, 2, 1, 1, 1, 4, 2, 1, 1, 5, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1,
							   5, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 4, 1, 2, 1, 3, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 2, 1, 1, 4, 1, 1, 1, 5, 3, 2, 2, 1, 1, 3,
							   1, 5, 1, 5, 1, 1, 1, 1, 1, 5, 1, 4, 1, 2, 1, 1, 1, 1, 2, 1, 3, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 3, 1, 4, 3, 1, 4, 1, 3, 2, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1,
							   1, 1, 1, 1, 1, 1, 2, 1, 5, 1, 1, 1, 1, 2, 1, 1, 1, 3, 5, 1, 1, 1, 1, 5, 1, 1, 2, 1, 2, 4, 2, 2, 1, 1, 1, 5, 2, 1, 1, 5, 1, 1, 1, 1, 5, 1, 1, 1, 2, 1};

constexpr uint8_t g_dataTest[] = {
	3, 4, 3, 1, 2,
};

static int64_t Task(const uint8_t data[], size_t length, int days)
{
	// Count of fish of each age
	int64_t fishCount[9] = {};

	for (size_t i = 0; i < length; i++)
	{
		fishCount[data[i]]++;
	}

	// Simulate
	for (int i = 0; i < days; i++)
	{
		int64_t fishCountNew[9] = {};

		// All fish with zero on their timer, spawn new ones with 8 days on their timer
		fishCountNew[8] = fishCount[0];
		// For all other cases, decrement the timer by 1
		fishCountNew[7] = fishCount[8];
		// Fish with zero on their timer get reset to a timer of 6, and of course the ones with 7 on their timer also will end up with a count of 6
		fishCountNew[6] = fishCount[7] + fishCount[0];
		fishCountNew[5] = fishCount[6];
		fishCountNew[4] = fishCount[5];
		fishCountNew[3] = fishCount[4];
		fishCountNew[2] = fishCount[3];
		fishCountNew[1] = fishCount[2];
		fishCountNew[0] = fishCount[1];

		// fishCount = fishCountNew
		std::copy(std::begin(fishCountNew), std::end(fishCountNew), std::begin(fishCount));
	}

	int64_t totalFish = 0;
	for (int64_t c : fishCount)
	{
		totalFish += c;
	}

	return totalFish;
}

void Day6()
{
	constexpr const char *resultName = "lanternfish count";

	//std::cout << "From test1, " << resultName << " was " << Task(g_dataTest, std::size(g_dataTest), 80) << "\n ";

	std::cout << "From task1, " << resultName << " was " << Task(g_data1, std::size(g_data1), 80) << "\n ";

	//std::cout << "From test2, " << resultName << " was " << Task(g_dataTest, std::size(g_dataTest), 256) << "\n ";

	std::cout << "From task2, " << resultName << " was " << Task(g_data1, std::size(g_data1), 256) << "\n ";
}
