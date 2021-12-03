#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

enum class Direction
{
	forward,
	down,
	up,
};

struct Move
{
	const Direction direction;
	const int		magnitude;
};

struct SubState
{
	int64_t pos;
	int64_t depth;
	int64_t aim;
};

constexpr Move g_data1[] = {{Direction::forward, 2}};

constexpr Move g_dataTest[] = {
	{Direction::forward, 5}, {Direction::down, 5}, {Direction::forward, 8}, {Direction::up, 3}, {Direction::down, 8}, {Direction::forward, 2},
};

static int64_t Task1(const Move data[], size_t length)
{
	SubState result = {};

	for (size_t i = 0; i < length; i++)
	{
		switch (data[i].direction)
		{
			case Direction::forward:
				result.pos += data[i].magnitude;
				break;
			case Direction::down:
				result.depth += data[i].magnitude;
				break;
			case Direction::up:
				result.depth -= data[i].magnitude;
				break;
		}
	}

	return result.pos * result.depth;
}

static int64_t Task2(const Move data[], size_t length)
{
	SubState result = {};

	for (size_t i = 0; i < length; i++)
	{
		switch (data[i].direction)
		{
			case Direction::forward:
				result.pos += data[i].magnitude;
				result.depth += result.aim * data[i].magnitude;
				break;
			case Direction::down:
				result.aim += data[i].magnitude;
				break;
			case Direction::up:
				result.aim -= data[i].magnitude;
				break;
		}
	}

	return result.pos * result.depth;
}

void Day4()
{
	//std::cout << "From test1, combined position was " << Task1(g_dataTest, std::size(g_dataTest)) << "\n";

	//std::cout << "From task1, combined position was " << Task1(g_data1, std::size(g_data1)) << "\n";

	//std::cout << "From test2, combined position was " << Task2(g_dataTest, std::size(g_dataTest)) << "\n";

	//std::cout << "From task2, combined position was " << Task2(g_data1, std::size(g_data1)) << "\n";
}
