#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cassert>

enum class Direction
{
	forward,
	down,
	up,
};

struct Move
{
	const Direction direction;
	const int	magnitude;
};

struct SubState
{
	int64_t pos;
	int64_t depth;
	int64_t aim;
};

constexpr Move g_data1[] =
{
	{Direction::forward, 2}, {Direction::forward, 5}, {Direction::forward, 5}, {Direction::down, 4},	{Direction::forward, 8}, {Direction::down, 1},	  {Direction::forward, 2},
	{Direction::forward, 2}, {Direction::down, 9},	  {Direction::down, 2},	   {Direction::forward, 6}, {Direction::forward, 3}, {Direction::down, 9},	  {Direction::down, 2},
	{Direction::forward, 4}, {Direction::up, 2},	  {Direction::forward, 7}, {Direction::up, 6},		{Direction::forward, 8}, {Direction::forward, 4}, {Direction::up, 5},
	{Direction::forward, 3}, {Direction::down, 9},	  {Direction::forward, 5}, {Direction::forward, 8}, {Direction::forward, 6}, {Direction::forward, 6}, {Direction::forward, 8},
	{Direction::forward, 8}, {Direction::forward, 5}, {Direction::down, 2},	   {Direction::forward, 8}, {Direction::down, 4},	 {Direction::down, 6},	  {Direction::down, 6},
	{Direction::forward, 7}, {Direction::forward, 6}, {Direction::up, 3},	   {Direction::up, 5},		{Direction::down, 5},	 {Direction::down, 3},	  {Direction::up, 2},
	{Direction::down, 7},	 {Direction::down, 2},	  {Direction::forward, 1}, {Direction::forward, 6}, {Direction::up, 1},		 {Direction::down, 7},	  {Direction::forward, 8},
	{Direction::down, 7},	 {Direction::down, 6},	  {Direction::forward, 5}, {Direction::up, 6},		{Direction::forward, 9}, {Direction::down, 9},	  {Direction::up, 3},
	{Direction::down, 6},	 {Direction::down, 1},	  {Direction::forward, 6}, {Direction::up, 1},		{Direction::down, 1},	 {Direction::up, 3},	  {Direction::up, 7},
	{Direction::forward, 1}, {Direction::down, 5},	  {Direction::forward, 7}, {Direction::forward, 3}, {Direction::down, 9},	 {Direction::up, 8},	  {Direction::forward, 1},
	{Direction::down, 4},	 {Direction::up, 1},	  {Direction::forward, 9}, {Direction::forward, 7}, {Direction::down, 2},	 {Direction::forward, 8}, {Direction::down, 2},
	{Direction::down, 5},	 {Direction::down, 2},	  {Direction::up, 1},	   {Direction::down, 5},	{Direction::forward, 4}, {Direction::forward, 8}, {Direction::forward, 3},
	{Direction::forward, 3}, {Direction::forward, 1}, {Direction::down, 1},	   {Direction::forward, 1}, {Direction::down, 7},	 {Direction::up, 7},	  {Direction::down, 3},
	{Direction::down, 1},	 {Direction::down, 7},	  {Direction::down, 4},	   {Direction::forward, 7}, {Direction::forward, 5}, {Direction::down, 9},	  {Direction::down, 5},
	{Direction::forward, 3}, {Direction::up, 7},	  {Direction::down, 2},	   {Direction::up, 1},		{Direction::forward, 1}, {Direction::forward, 2}, {Direction::down, 7},
	{Direction::down, 3},	 {Direction::forward, 7}, {Direction::up, 4},	   {Direction::forward, 3}, {Direction::up, 8},		 {Direction::down, 9},	  {Direction::down, 4},
	{Direction::forward, 5}, {Direction::forward, 6}, {Direction::down, 3},	   {Direction::down, 5},	{Direction::down, 4},	 {Direction::down, 9},	  {Direction::down, 8},
	{Direction::forward, 6}, {Direction::down, 3},	  {Direction::down, 1},	   {Direction::down, 9},	{Direction::down, 6},	 {Direction::forward, 9}, {Direction::forward, 2},
	{Direction::up, 5},		 {Direction::forward, 5}, {Direction::forward, 4}, {Direction::down, 9},	{Direction::up, 7},		 {Direction::up, 2},	  {Direction::forward, 1},
	{Direction::forward, 8}, {Direction::forward, 6}, {Direction::up, 8},	   {Direction::down, 9},	{Direction::down, 2},	 {Direction::forward, 7}, {Direction::down, 6},
	{Direction::forward, 7}, {Direction::up, 9},	  {Direction::up, 7},	   {Direction::down, 8},	{Direction::up, 1},		 {Direction::forward, 2}, {Direction::forward, 9},
	{Direction::down, 9},	 {Direction::forward, 6}, {Direction::down, 2},	   {Direction::down, 1},	{Direction::up, 3},		 {Direction::forward, 4}, {Direction::down, 3},
	{Direction::down, 4},	 {Direction::down, 9},	  {Direction::up, 8},	   {Direction::up, 8},		{Direction::forward, 3}, {Direction::up, 7},	  {Direction::forward, 9},
	{Direction::forward, 7}, {Direction::up, 2},	  {Direction::up, 8},	   {Direction::forward, 2}, {Direction::down, 6},	 {Direction::forward, 3}, {Direction::forward, 1},
	{Direction::down, 7},	 {Direction::down, 2},	  {Direction::forward, 9}, {Direction::forward, 9}, {Direction::down, 3},	 {Direction::forward, 2}, {Direction::forward, 8},
	{Direction::down, 6},	 {Direction::forward, 6}, {Direction::forward, 5}, {Direction::forward, 1}, {Direction::forward, 6}, {Direction::down, 8},	  {Direction::down, 7},
	{Direction::up, 9},		 {Direction::down, 6},	  {Direction::up, 7},	   {Direction::down, 2},	{Direction::up, 8},		 {Direction::up, 8},	  {Direction::down, 3},
	{Direction::down, 7},	 {Direction::up, 2},	  {Direction::up, 2},	   {Direction::down, 6},	{Direction::down, 6},	 {Direction::forward, 2}, {Direction::down, 6},
	{Direction::forward, 8}, {Direction::forward, 9}, {Direction::down, 3},	   {Direction::forward, 6}, {Direction::down, 9},	 {Direction::forward, 1}, {Direction::up, 6},
	{Direction::down, 3},	 {Direction::up, 5},	  {Direction::forward, 9}, {Direction::forward, 7}, {Direction::forward, 9}, {Direction::forward, 5}, {Direction::up, 6},
	{Direction::down, 3},	 {Direction::down, 3},	  {Direction::down, 3},	   {Direction::forward, 1}, {Direction::up, 5},		 {Direction::forward, 3}, {Direction::forward, 2},
	{Direction::down, 1},	 {Direction::forward, 7}, {Direction::down, 1},	   {Direction::forward, 6}, {Direction::forward, 5}, {Direction::forward, 9}, {Direction::up, 6},
	{Direction::forward, 1}, {Direction::up, 8},	  {Direction::down, 7},	   {Direction::forward, 6}, {Direction::forward, 3}, {Direction::forward, 1}, {Direction::up, 6},
	{Direction::forward, 4}, {Direction::up, 6},	  {Direction::down, 7},	   {Direction::forward, 8}, {Direction::forward, 4}, {Direction::forward, 6}, {Direction::forward, 5},
	{Direction::up, 6},		 {Direction::down, 7},	  {Direction::up, 9},	   {Direction::down, 7},	{Direction::forward, 3}, {Direction::down, 7},	  {Direction::forward, 6},
	{Direction::down, 6},	 {Direction::down, 6},	  {Direction::forward, 8}, {Direction::up, 8},		{Direction::forward, 8}, {Direction::forward, 2}, {Direction::down, 8},
	{Direction::forward, 4}, {Direction::forward, 9}, {Direction::forward, 7}, {Direction::down, 4},	{Direction::down, 7},	 {Direction::forward, 4}, {Direction::forward, 3},
	{Direction::forward, 2}, {Direction::forward, 2}, {Direction::forward, 5}, {Direction::down, 6},	{Direction::forward, 1}, {Direction::forward, 6}, {Direction::up, 8},
	{Direction::up, 3},		 {Direction::up, 9},	  {Direction::forward, 3}, {Direction::up, 8},		{Direction::forward, 3}, {Direction::up, 8},	  {Direction::down, 9},
	{Direction::up, 7},		 {Direction::forward, 9}, {Direction::forward, 1}, {Direction::down, 7},	{Direction::forward, 9}, {Direction::down, 6},	  {Direction::forward, 4},
	{Direction::down, 3},	 {Direction::up, 9},	  {Direction::forward, 5}, {Direction::down, 4},	{Direction::up, 6},		 {Direction::down, 1},	  {Direction::up, 9},
	{Direction::forward, 2}, {Direction::up, 2},	  {Direction::down, 1},	   {Direction::forward, 7}, {Direction::down, 6},	 {Direction::down, 4},	  {Direction::down, 7},
	{Direction::down, 4},	 {Direction::down, 8},	  {Direction::up, 9},	   {Direction::down, 6},	{Direction::up, 3},		 {Direction::down, 7},	  {Direction::forward, 3},
	{Direction::forward, 1}, {Direction::down, 1},	  {Direction::forward, 2}, {Direction::forward, 6}, {Direction::down, 6},	 {Direction::forward, 5}, {Direction::down, 8},
	{Direction::down, 8},	 {Direction::down, 6},	  {Direction::down, 9},	   {Direction::forward, 6}, {Direction::forward, 7}, {Direction::up, 8},	  {Direction::forward, 5},
	{Direction::up, 8},		 {Direction::down, 6},	  {Direction::up, 3},	   {Direction::forward, 9}, {Direction::up, 9},		 {Direction::forward, 2}, {Direction::up, 6},
	{Direction::forward, 2}, {Direction::down, 8},	  {Direction::forward, 3}, {Direction::down, 5},	{Direction::down, 8},	 {Direction::up, 6},	  {Direction::down, 3},
	{Direction::down, 7},	 {Direction::down, 4},	  {Direction::forward, 5}, {Direction::forward, 8}, {Direction::down, 8},	 {Direction::forward, 6}, {Direction::down, 8},
	{Direction::up, 1},		 {Direction::forward, 5}, {Direction::down, 3},	   {Direction::down, 2},	{Direction::up, 1},		 {Direction::forward, 3}, {Direction::forward, 7},
	{Direction::forward, 6}, {Direction::forward, 9}, {Direction::up, 8},	   {Direction::down, 2},	{Direction::down, 1},	 {Direction::down, 7},	  {Direction::forward, 4},
	{Direction::forward, 2}, {Direction::down, 9},	  {Direction::down, 3},	   {Direction::down, 5},	{Direction::up, 6},		 {Direction::down, 2},	  {Direction::forward, 8},
	{Direction::up, 1},		 {Direction::up, 5},	  {Direction::down, 6},	   {Direction::down, 7},	{Direction::forward, 3}, {Direction::down, 4},	  {Direction::up, 6},
	{Direction::down, 9},	 {Direction::up, 6},	  {Direction::down, 2},	   {Direction::down, 2},	{Direction::down, 6},	 {Direction::down, 3},	  {Direction::forward, 9},
	{Direction::down, 6},	 {Direction::forward, 5}, {Direction::forward, 6}, {Direction::forward, 4}, {Direction::down, 6},	 {Direction::forward, 3}, {Direction::down, 9},
	{Direction::up, 8},		 {Direction::forward, 2}, {Direction::up, 3},	   {Direction::forward, 1}, {Direction::up, 8},		 {Direction::forward, 1}, {Direction::down, 6},
	{Direction::down, 3},	 {Direction::forward, 5}, {Direction::forward, 4}, {Direction::down, 9},	{Direction::up, 3},		 {Direction::down, 6},	  {Direction::forward, 4},
	{Direction::down, 8},	 {Direction::down, 3},	  {Direction::down, 7},	   {Direction::forward, 1}, {Direction::forward, 2}, {Direction::forward, 8}, {Direction::down, 2},
	{Direction::down, 6},	 {Direction::up, 9},	  {Direction::forward, 2}, {Direction::forward, 4}, {Direction::forward, 8}, {Direction::down, 3},	  {Direction::forward, 9},
	{Direction::down, 7},	 {Direction::up, 8},	  {Direction::forward, 1}, {Direction::down, 6},	{Direction::down, 3},	 {Direction::forward, 5}, {Direction::forward, 5},
	{Direction::forward, 2}, {Direction::down, 2},	  {Direction::down, 2},	   {Direction::down, 2},	{Direction::up, 4},		 {Direction::forward, 2}, {Direction::forward, 5},
	{Direction::forward, 1}, {Direction::forward, 5}, {Direction::down, 3},	   {Direction::forward, 8}, {Direction::up, 1},		 {Direction::forward, 9}, {Direction::up, 5},
	{Direction::forward, 2}, {Direction::down, 4},	  {Direction::forward, 8}, {Direction::forward, 9}, {Direction::up, 6},		 {Direction::up, 1},	  {Direction::down, 7},
	{Direction::down, 3},	 {Direction::forward, 9}, {Direction::down, 3},	   {Direction::down, 3},	{Direction::forward, 3}, {Direction::forward, 6}, {Direction::up, 4},
	{Direction::forward, 2}, {Direction::down, 9},	  {Direction::forward, 5}, {Direction::forward, 3}, {Direction::forward, 5}, {Direction::down, 6},	  {Direction::up, 6},
	{Direction::down, 7},	 {Direction::forward, 2}, {Direction::down, 4},	   {Direction::forward, 6}, {Direction::forward, 5}, {Direction::forward, 8}, {Direction::down, 4},
	{Direction::up, 3},		 {Direction::up, 4},	  {Direction::down, 9},	   {Direction::forward, 9}, {Direction::down, 7},	 {Direction::down, 1},	  {Direction::down, 9},
	{Direction::down, 6},	 {Direction::down, 8},	  {Direction::forward, 7}, {Direction::down, 3},	{Direction::up, 3},		 {Direction::up, 5},	  {Direction::forward, 5},
	{Direction::up, 6},		 {Direction::down, 6},	  {Direction::forward, 9}, {Direction::down, 7},	{Direction::forward, 6}, {Direction::up, 1},	  {Direction::forward, 7},
	{Direction::forward, 8}, {Direction::down, 9},	  {Direction::down, 1},	   {Direction::forward, 4}, {Direction::up, 2},		 {Direction::down, 3},	  {Direction::up, 3},
	{Direction::down, 6},	 {Direction::forward, 6}, {Direction::down, 7},	   {Direction::down, 2},	{Direction::forward, 8}, {Direction::forward, 2}, {Direction::forward, 3},
	{Direction::forward, 5}, {Direction::up, 8},	  {Direction::up, 6},	   {Direction::down, 1},	{Direction::up, 7},		 {Direction::down, 1},	  {Direction::down, 8},
	{Direction::forward, 5}, {Direction::up, 7},	  {Direction::down, 1},	   {Direction::forward, 8}, {Direction::down, 6},	 {Direction::down, 2},	  {Direction::up, 7},
	{Direction::down, 1},	 {Direction::forward, 1}, {Direction::up, 8},	   {Direction::forward, 5}, {Direction::down, 7},	 {Direction::down, 8},	  {Direction::forward, 4},
	{Direction::down, 6},	 {Direction::down, 2},	  {Direction::forward, 4}, {Direction::forward, 7}, {Direction::down, 5},	 {Direction::down, 1},	  {Direction::down, 8},
	{Direction::down, 3},	 {Direction::up, 8},	  {Direction::down, 6},	   {Direction::down, 1},	{Direction::down, 1},	 {Direction::forward, 4}, {Direction::down, 8},
	{Direction::up, 5},		 {Direction::forward, 3}, {Direction::forward, 3}, {Direction::forward, 5}, {Direction::forward, 8}, {Direction::up, 7},	  {Direction::forward, 5},
	{Direction::down, 8},	 {Direction::forward, 9}, {Direction::up, 9},	   {Direction::forward, 1}, {Direction::down, 2},	 {Direction::up, 9},	  {Direction::down, 7},
	{Direction::up, 1},		 {Direction::up, 3},	  {Direction::forward, 9}, {Direction::forward, 8}, {Direction::forward, 3}, {Direction::forward, 8}, {Direction::down, 8},
	{Direction::down, 5},	 {Direction::down, 7},	  {Direction::up, 7},	   {Direction::forward, 9}, {Direction::up, 8},		 {Direction::down, 9},	  {Direction::down, 9},
	{Direction::down, 1},	 {Direction::up, 4},	  {Direction::up, 4},	   {Direction::up, 3},		{Direction::forward, 3}, {Direction::down, 7},	  {Direction::down, 3},
	{Direction::forward, 5}, {Direction::up, 9},	  {Direction::down, 3},	   {Direction::up, 2},		{Direction::forward, 1}, {Direction::forward, 4}, {Direction::up, 9},
	{Direction::forward, 6}, {Direction::down, 6},	  {Direction::down, 6},	   {Direction::forward, 2}, {Direction::forward, 2}, {Direction::down, 4},	  {Direction::forward, 9},
	{Direction::up, 6},		 {Direction::down, 8},	  {Direction::down, 8},	   {Direction::down, 9},	{Direction::up, 4},		 {Direction::down, 9},	  {Direction::down, 3},
	{Direction::down, 7},	 {Direction::forward, 4}, {Direction::up, 4},	   {Direction::up, 5},		{Direction::down, 2},	 {Direction::up, 2},	  {Direction::forward, 1},
	{Direction::up, 8},		 {Direction::forward, 2}, {Direction::down, 6},	   {Direction::forward, 9}, {Direction::down, 9},	 {Direction::forward, 9}, {Direction::up, 8},
	{Direction::down, 5},	 {Direction::up, 3},	  {Direction::up, 9},	   {Direction::down, 8},	{Direction::forward, 6}, {Direction::forward, 2}, {Direction::forward, 7},
	{Direction::down, 9},	 {Direction::down, 8},	  {Direction::up, 9},	   {Direction::down, 5},	{Direction::up, 5},		 {Direction::down, 1},	  {Direction::forward, 3},
	{Direction::down, 2},	 {Direction::down, 5},	  {Direction::down, 4},	   {Direction::down, 1},	{Direction::down, 5},	 {Direction::down, 5},	  {Direction::down, 5},
	{Direction::forward, 8}, {Direction::down, 2},	  {Direction::down, 3},	   {Direction::down, 4},	{Direction::down, 2},	 {Direction::up, 8},	  {Direction::up, 1},
	{Direction::down, 5},	 {Direction::forward, 8}, {Direction::down, 6},	   {Direction::forward, 9}, {Direction::down, 6},	 {Direction::down, 6},	  {Direction::down, 5},
	{Direction::forward, 5}, {Direction::forward, 3}, {Direction::forward, 7}, {Direction::down, 6},	{Direction::forward, 4}, {Direction::down, 8},	  {Direction::up, 9},
	{Direction::up, 6},		 {Direction::forward, 5}, {Direction::down, 4},	   {Direction::forward, 8}, {Direction::forward, 1}, {Direction::forward, 8}, {Direction::up, 5},
	{Direction::up, 5},		 {Direction::forward, 6}, {Direction::down, 3},	   {Direction::down, 7},	{Direction::up, 7},		 {Direction::down, 5},	  {Direction::forward, 1},
	{Direction::forward, 3}, {Direction::up, 3},	  {Direction::down, 3},	   {Direction::down, 3},	{Direction::down, 5},	 {Direction::forward, 9}, {Direction::down, 2},
	{Direction::up, 5},		 {Direction::up, 2},	  {Direction::forward, 1}, {Direction::down, 1},	{Direction::forward, 5}, {Direction::down, 8},	  {Direction::forward, 8},
	{Direction::forward, 9}, {Direction::forward, 3}, {Direction::forward, 2}, {Direction::forward, 4}, {Direction::down, 5},	 {Direction::up, 1},	  {Direction::down, 5},
	{Direction::up, 1},		 {Direction::up, 4},	  {Direction::forward, 2}, {Direction::forward, 4}, {Direction::down, 6},	 {Direction::up, 2},	  {Direction::up, 4},
	{Direction::forward, 4}, {Direction::down, 7},	  {Direction::forward, 2}, {Direction::up, 1},		{Direction::forward, 4}, {Direction::up, 4},	  {Direction::forward, 9},
	{Direction::down, 1},	 {Direction::down, 4},	  {Direction::up, 1},	   {Direction::forward, 2}, {Direction::forward, 3}, {Direction::down, 6},	  {Direction::forward, 9},
	{Direction::forward, 3}, {Direction::down, 2},	  {Direction::forward, 9}, {Direction::up, 4},		{Direction::forward, 5}, {Direction::forward, 2}, {Direction::down, 2},
	{Direction::forward, 5}, {Direction::down, 5},	  {Direction::down, 3},	   {Direction::down, 7},	{Direction::down, 7},	 {Direction::up, 3},	  {Direction::down, 7},
	{Direction::forward, 9}, {Direction::forward, 7}, {Direction::up, 4},	   {Direction::forward, 7}, {Direction::up, 8},		 {Direction::down, 8},	  {Direction::forward, 5},
	{Direction::down, 2},	 {Direction::down, 9},	  {Direction::up, 8},	   {Direction::forward, 4}, {Direction::forward, 4}, {Direction::forward, 2}, {Direction::up, 4},
	{Direction::down, 5},	 {Direction::forward, 3}, {Direction::forward, 6}, {Direction::forward, 5}, {Direction::forward, 3}, {Direction::forward, 7}, {Direction::up, 9},
	{Direction::forward, 1}, {Direction::forward, 2}, {Direction::up, 7},	   {Direction::down, 4},	{Direction::forward, 8}, {Direction::down, 2},	  {Direction::forward, 1},
	{Direction::down, 1},	 {Direction::down, 9},	  {Direction::up, 2},	   {Direction::down, 2},	{Direction::forward, 8}, {Direction::forward, 5}, {Direction::up, 9},
	{Direction::forward, 5}, {Direction::down, 2},	  {Direction::forward, 2}, {Direction::down, 7},	{Direction::forward, 5}, {Direction::down, 1},	  {Direction::forward, 9},
	{Direction::forward, 8}, {Direction::forward, 8}, {Direction::forward, 9}, {Direction::forward, 8}, {Direction::down, 9},	 {Direction::forward, 8}, {Direction::down, 1},
	{Direction::down, 2},	 {Direction::down, 9},	  {Direction::up, 2},	   {Direction::forward, 8}, {Direction::forward, 8}, {Direction::down, 9},	  {Direction::forward, 8},
	{Direction::up, 8},		 {Direction::forward, 2}, {Direction::down, 5},	   {Direction::up, 3},		{Direction::forward, 2}, {Direction::up, 3},	  {Direction::down, 6},
	{Direction::forward, 5}, {Direction::up, 7},	  {Direction::forward, 2}, {Direction::forward, 7}, {Direction::forward, 7}, {Direction::down, 8},	  {Direction::forward, 3},
	{Direction::up, 5},		 {Direction::down, 8},	  {Direction::down, 3},	   {Direction::down, 8},	{Direction::up, 6},		 {Direction::down, 6},	  {Direction::up, 4},
	{Direction::forward, 7}, {Direction::up, 6},	  {Direction::up, 1},	   {Direction::down, 5},	{Direction::up, 8},		 {Direction::forward, 8}, {Direction::forward, 9},
	{Direction::down, 8},	 {Direction::forward, 6}, {Direction::down, 8},	   {Direction::down, 9},	{Direction::down, 8},	 {Direction::forward, 9}, {Direction::up, 1},
	{Direction::down, 1},	 {Direction::down, 8},	  {Direction::down, 5},	   {Direction::down, 2},	{Direction::up, 7},		 {Direction::forward, 4}, {Direction::down, 4},
	{Direction::forward, 6}, {Direction::down, 1},	  {Direction::forward, 5}, {Direction::forward, 3}, {Direction::forward, 9}, {Direction::up, 8},	  {Direction::down, 4},
	{Direction::down, 6},	 {Direction::down, 4},	  {Direction::down, 1},	   {Direction::up, 9},		{Direction::forward, 9}, {Direction::down, 9},	  {Direction::forward, 7},
	{Direction::down, 2},	 {Direction::down, 8},	  {Direction::forward, 2}, {Direction::forward, 5}, {Direction::down, 6},	 {Direction::down, 1},	  {Direction::down, 1},
	{Direction::up, 3},		 {Direction::forward, 9}, {Direction::up, 7},	   {Direction::down, 1},	{Direction::down, 6},	 {Direction::forward, 6}, {Direction::up, 2},
	{Direction::down, 4},	 {Direction::down, 7},	  {Direction::forward, 3}, {Direction::down, 9},	{Direction::down, 1},	 {Direction::forward, 7}, {Direction::forward, 2},
	{Direction::forward, 6}, {Direction::down, 4},	  {Direction::forward, 7}, {Direction::forward, 8}, {Direction::forward, 3}, {Direction::forward, 7}, {Direction::up, 8},
	{Direction::forward, 5}, {Direction::up, 8},	  {Direction::down, 8},	   {Direction::forward, 3}, {Direction::forward, 8}, {Direction::forward, 7}, {Direction::forward, 3},
	{Direction::down, 4},	 {Direction::forward, 9}, {Direction::forward, 4}, {Direction::up, 6},		{Direction::forward, 4}, {Direction::forward, 6}, {Direction::up, 4},
	{Direction::forward, 6}, {Direction::forward, 2}, {Direction::down, 3},	   {Direction::down, 3},	{Direction::down, 4},	 {Direction::down, 1},	  {Direction::down, 9},
	{Direction::up, 1},		 {Direction::up, 9},	  {Direction::down, 7},	   {Direction::up, 9},		{Direction::forward, 5}, {Direction::down, 2},	  {Direction::up, 7},
	{Direction::forward, 9}, {Direction::up, 1},	  {Direction::down, 5},	   {Direction::up, 8},		{Direction::forward, 9}, {Direction::down, 1},	  {Direction::up, 3},
	{Direction::forward, 3}, {Direction::forward, 9}, {Direction::up, 7},	   {Direction::forward, 3}, {Direction::down, 7},	 {Direction::forward, 3}, {Direction::forward, 5},
	{Direction::forward, 4}, {Direction::up, 3},	  {Direction::forward, 3}, {Direction::down, 8},	{Direction::forward, 7}, {Direction::up, 5},	  {Direction::forward, 9},
	{Direction::down, 6},	 {Direction::up, 6},	  {Direction::up, 1},	   {Direction::forward, 8}, {Direction::down, 9},	 {Direction::forward, 9}, {Direction::forward, 9},
	{Direction::down, 5},	 {Direction::down, 7},	  {Direction::forward, 7}, {Direction::down, 5},	{Direction::down, 3},	 {Direction::forward, 4}, {Direction::up, 6},
	{Direction::forward, 6}, {Direction::forward, 2}, {Direction::down, 8},	   {Direction::down, 6},	{Direction::forward, 1}, {Direction::forward, 1}, {Direction::down, 6},
	{Direction::forward, 1}, {Direction::down, 6},	  {Direction::down, 2},	   {Direction::forward, 1}, {Direction::forward, 6}, {Direction::up, 4},	  {Direction::up, 7},
	{Direction::up, 3},		 {Direction::down, 6},	  {Direction::forward, 1}, {Direction::forward, 9}, {Direction::forward, 4}, {Direction::down, 4},	  {Direction::forward, 3},
	{Direction::down, 8},	 {Direction::down, 6},	  {Direction::down, 6},	   {Direction::forward, 2}, {Direction::forward, 8}, {Direction::forward, 6}, {Direction::down, 4},
	{Direction::up, 2},		 {Direction::down, 1},	  {Direction::up, 4},	   {Direction::down, 8},	{Direction::forward, 9}, {Direction::down, 4},	  {Direction::down, 8},
	{Direction::up, 8},		 {Direction::forward, 2}, {Direction::up, 9},	   {Direction::down, 9},	{Direction::forward, 2}, {Direction::down, 8},	  {Direction::forward, 3},
	{Direction::down, 1},	 {Direction::up, 9},	  {Direction::forward, 6}, {Direction::down, 9},	{Direction::forward, 2}, {Direction::down, 2},	  {Direction::up, 5},
	{Direction::down, 4},	 {Direction::down, 5},	  {Direction::down, 7},	   {Direction::forward, 4}, {Direction::down, 4},	 {Direction::forward, 6}, {Direction::forward, 2},
	{Direction::down, 8},	 {Direction::up, 3},	  {Direction::up, 9},	   {Direction::forward, 3}, {Direction::forward, 6}, {Direction::down, 6},	  {Direction::down, 2},
	{Direction::down, 5},	 {Direction::down, 4},	  {Direction::forward, 1}, {Direction::up, 2},		{Direction::down, 3},	 {Direction::forward, 6}, {Direction::forward, 5},
	{Direction::down, 4},	 {Direction::down, 3},	  {Direction::forward, 2}, {Direction::forward, 4}, {Direction::down, 9},	 {Direction::down, 3},	  {Direction::down, 4},
	{Direction::up, 6},		 {Direction::forward, 8}, {Direction::up, 2},	   {Direction::up, 8},		{Direction::up, 4},		 {Direction::forward, 7}, {Direction::forward, 5},
	{Direction::forward, 9}, {Direction::down, 6},	  {Direction::forward, 7}, {Direction::forward, 9}, {Direction::up, 3},		 {Direction::forward, 6}
};

constexpr Move g_dataTest[] =
{
	{Direction::forward, 5},
	{Direction::down, 5},
	{Direction::forward, 8},
	{Direction::up, 3},
	{Direction::down, 8},
	{Direction::forward, 2},
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

void Day2()
{
	//std::cout << "After test1 combined position was " << Task1(g_dataTest, std::size(g_dataTest)) << "\n";

	std::cout << "After data1 combined position was " << Task1(g_data1, std::size(g_data1)) << "\n";

	//std::cout << "After test2 combined position was " << Task2(g_dataTest, std::size(g_dataTest)) << "\n";

	std::cout << "After data2 combined position was " << Task2(g_data1, std::size(g_data1)) << "\n";
}
