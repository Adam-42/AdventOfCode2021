#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cassert>

constexpr int g_data1[] = {
159, 170, 171, 170, 168,
};

constexpr int g_dataTest[] = {
199, 200, 208, 210, 200, 207, 240, 269, 260, 263,
};

static int Task1(const int data[], size_t length)
{
	int previous = data[0];
	int result = 0;
	for (size_t i = 1; i < length; i++)
	{
		if (data[i] > previous)
		{
			result++;
		}
		previous = data[i];
	}

	return result;
}

static int Task2(const int data[], size_t length)
{
	int window1 = data[0] + data[1] + data[2];
	int window2 = data[1] + data[2] + data[3];
	int result = window2 > window1;
	for (size_t i=4; i < length; i++)
	{
		window1 = window2;
		window2 -= data[i - 3];
		window2 += data[i - 0];

		if (window2 > window1)
		{
			result++;
		}
	}

	return result;
}

void Day2()
{
	//std::cout << "There were " << Task1(g_dataTest, std::size(g_dataTest)) << " test increases\n";

	//std::cout << "There were " << Task1(g_data1, std::size(g_data1)) << " increases\n";

	//std::cout << "There were " << Task2(g_dataTest, std::size(g_dataTest)) << " test windowed increases\n";

	//std::cout << "There were " << Task2(g_data1, std::size(g_data1)) << " windowed increases\n";
}
