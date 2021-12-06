#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

struct Point
{
	int x;
	int y;

	constexpr auto operator<=>(const Point &p) const = default;
};

struct Line
{
	Point start;
	Point end;

	constexpr bool IsVerticalOrHorizontal() const
	{
		return start.x == end.x || start.y == end.y;
	}
};

constexpr Line g_data1[] = {
	{{432, 708}, {432, 160}}, {{579, 594}, {579, 448}}, {{351, 791}, {351, 595}}, {{520, 836}, {564, 880}}, {{30, 443}, {666, 443}}, {{868, 157}, {563, 157}}, {{112, 186}, {853, 927}},
};

// Replace: ([0-9]+),([0-9]+) -> ([0-9]+),([0-9]+)
// With: {{$1,$2}, {$3, $4}},
constexpr Line g_dataTest[] = {
	{{0, 9}, {5, 9}}, {{8, 0}, {0, 8}}, {{9, 4}, {3, 4}}, {{2, 2}, {2, 1}}, {{7, 0}, {7, 4}}, {{6, 4}, {2, 0}}, {{0, 9}, {2, 9}}, {{3, 4}, {1, 4}}, {{0, 0}, {8, 8}}, {{5, 5}, {8, 2}},
};

static int64_t Task1(const Line data[], size_t length)
{
	int64_t intersectionCount = 0;

	Point max = {};

	for (size_t i = 0; i < length; i++)
	{
		if (data[i].IsVerticalOrHorizontal())
		{
			max.x = std::max(max.x, data[i].start.x);
			max.x = std::max(max.x, data[i].end.x);
			max.y = std::max(max.y, data[i].start.y);
			max.y = std::max(max.y, data[i].end.y);
		}
	}
	max.x++;
	max.y++;

	std::vector<int> grid;
	grid.resize(max.x * max.y);

	for (size_t i = 0; i < length; i++)
	{
		if (data[i].IsVerticalOrHorizontal())
		{
			int xdir = data[i].end.x - data[i].start.x;
			xdir	 = xdir == 0 ? xdir : (xdir > 0 ? 1 : -1);
			int ydir = data[i].end.y - data[i].start.y;
			ydir	 = ydir == 0 ? ydir : (ydir > 0 ? 1 : -1);

			// The "end" here is one past the end, as lines are inclusive
			Point end = data[i].end;
			end.x += xdir;
			end.y += ydir;

			Point p = data[i].start;
			do
			{
				int &pixel = grid[p.y * max.x + p.x];
				pixel++;
				if (pixel == 2)
				{
					intersectionCount++;
				}

				p.x += xdir;
				p.y += ydir;
			} while (p != end);
		}
	}

#if 0
	// Debug grid display
	std::cout << '\n';
	for (int y = 0; y < max.y; y++)
	{
		for (int x = 0; x < max.x; x++)
		{
			int &pixel = grid[y * max.x + x];
			std::cout << (char)(pixel == 0 ? '.' : ('0' + pixel));
		}
		std::cout << '\n';
	}
#endif

	return intersectionCount;
}

static int64_t Task2(const Line data[], size_t length)
{
	int64_t intersectionCount = 0;

	Point max = {};

	for (size_t i = 0; i < length; i++)
	{
		max.x = std::max(max.x, data[i].start.x);
		max.x = std::max(max.x, data[i].end.x);
		max.y = std::max(max.y, data[i].start.y);
		max.y = std::max(max.y, data[i].end.y);
	}
	max.x++;
	max.y++;

	std::vector<int> grid;
	grid.resize(max.x * max.y);

	for (size_t i = 0; i < length; i++)
	{
		int xdir = data[i].end.x - data[i].start.x;
		xdir	 = xdir == 0 ? xdir : (xdir > 0 ? 1 : -1);
		int ydir = data[i].end.y - data[i].start.y;
		ydir	 = ydir == 0 ? ydir : (ydir > 0 ? 1 : -1);

		// The "end" here is one past the end, as lines are inclusive
		Point end = data[i].end;
		end.x += xdir;
		end.y += ydir;

		Point p = data[i].start;
		do
		{
			int &pixel = grid[p.y * max.x + p.x];
			pixel++;
			if (pixel == 2)
			{
				intersectionCount++;
			}

			p.x += xdir;
			p.y += ydir;
		} while (p != end);
	}

#if 0
	// Debug grid display
	std::cout << '\n';
	for (int y = 0; y < max.y; y++)
	{
		for (int x = 0; x < max.x; x++)
		{
			int &pixel = grid[y * max.x + x];
			std::cout << (char)(pixel == 0 ? '.' : ('0' + pixel));
		}
		std::cout << '\n';
	}
#endif

	return intersectionCount;
}

void Day7()
{
	constexpr const char *resultName = "day 7 result";

	//std::cout << "From test1, " << resultName << " was " << Task1(g_dataTest, std::size(g_dataTest)) << "\n";

	//std::cout << "From task1, " << resultName << " was " << Task1(g_data1, std::size(g_data1)) << "\n";

	//std::cout << "From test2, " << resultName << " was " << Task2(g_dataTest, std::size(g_dataTest)) << "\n";

	//std::cout << "From task2, " << resultName << " was " << Task2(g_data1, std::size(g_data1)) << "\n";
}
