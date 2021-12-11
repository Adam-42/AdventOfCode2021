#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

constexpr const char *g_data1[] = {
	"4764745784", "4643457176", "8322628477", "7617152546", "6137518165", "1556723176", "2187861886", "2553422625", "4817584638", "3754285662",
};

constexpr const char *g_dataTest[] = {
	"5483143223", "2745854711", "5264556173", "6141336146", "6357385478", "4167524645", "2176841721", "6882881134", "4846848554", "5283751526",
};

// Increment one octopus, and if it flashes then recursively increment all of the neighbours
// Returns the total number of flashes triggered by this increment
static int64_t Increment(std::vector<int8_t> &grid, size_t x, size_t y, size_t width, size_t length)
{
	// Because the values are unsigned, we don't need any >=0 tests to verify that we aren't out of bounds
	if (x < width && y < length)
	{
		int8_t &octopus = grid[y * width + x];

		// We use a value of 10 to indicate that the octopus has flashed this time, and therefore is locked in that state until the next step
		if (octopus < 10)
		{
			octopus++;
			if (octopus == 10)
			{
				// Flash! Return 1 + the sum of any neighbours that flashed.
				return 1 + Increment(grid, x + 1, y + 0, width, length) + Increment(grid, x - 1, y + 0, width, length) + Increment(grid, x + 0, y + 1, width, length) +
					   Increment(grid, x + 0, y - 1, width, length) + Increment(grid, x + 1, y + 1, width, length) + Increment(grid, x + 1, y - 1, width, length) +
					   Increment(grid, x - 1, y + 1, width, length) + Increment(grid, x - 1, y - 1, width, length);
			}
		}
	}
	return 0;
};

static int64_t Task1(const char *const data[], size_t length, int stepCount)
{
	int64_t flashes = 0;

	// Parse input
	const size_t width = strlen(data[0]);

	std::vector<int8_t> grid;
	grid.resize(width * length);

	for (size_t y = 0; y < length; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			grid[y * width + x] = data[y][x] - '0';
		}
	}

	for (int i = 0; i < stepCount; i++)
	{
		// Step forward by incrementing every cell
		for (size_t y = 0; y < length; y++)
		{
			for (size_t x = 0; x < width; x++)
			{
				int64_t flashesThisStep = Increment(grid, x, y, width, length);
				flashes += flashesThisStep;
			}
		}

		// Reset all of the ones that flashed to zero
		for (size_t y = 0; y < length; y++)
		{
			for (size_t x = 0; x < width; x++)
			{
				uint8_t octopus		= grid[y * width + x];
				grid[y * width + x] = (octopus == 10) ? 0 : octopus;
			}
		}
	}

	return flashes;
}

static size_t Task2(const char *const data[], size_t length)
{
	// Parse input
	const size_t width = strlen(data[0]);

	std::vector<int8_t> grid;
	grid.resize(width * length);

	for (size_t y = 0; y < length; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			grid[y * width + x] = data[y][x] - '0';
		}
	}

	for (int i = 0; true; i++)
	{
		// Step forward by incrementing every cell
		for (size_t y = 0; y < length; y++)
		{
			for (size_t x = 0; x < width; x++)
			{
				int64_t flashesThisStep = Increment(grid, x, y, width, length);
				if (flashesThisStep == width * length)
				{
					// Every octopus flashed - we are done
					return i + 1;
				}
			}
		}

		// Reset all of the ones that flashed to zero
		for (size_t y = 0; y < length; y++)
		{
			for (size_t x = 0; x < width; x++)
			{
				uint8_t octopus		= grid[y * width + x];
				grid[y * width + x] = (octopus == 10) ? 0 : octopus;
			}
		}
	}

	return -1;
}

void Day11()
{
	constexpr const char *resultName = " day 11 result is ";

	//std::cout << "From test1, " << resultName << Task1(g_dataTest, std::size(g_dataTest), 100) << "\n";

	std::cout << "From task1, " << resultName << Task1(g_data1, std::size(g_data1), 100) << "\n";

	//std::cout << "From test2, " << resultName << Task2(g_dataTest, std::size(g_dataTest)) << "\n";

	std::cout << "From task2, " << resultName << Task2(g_data1, std::size(g_data1)) << "\n";
}
