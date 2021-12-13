#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

constexpr const char *g_data1[] = {
	"QR-da", "QR-end", "QR-al",	 "start-op", "zh-iw", "zh-start", "da-PF", "op-bj", "iw-QR",	"end-HR", "bj-PF", "da-LY",
	"op-PF", "bj-iw",  "end-da", "bj-zh",	 "HR-iw", "zh-op",	  "zh-PF", "HR-bj", "start-PF", "HR-da",  "QR-bj",
};

constexpr const char *g_dataTest[] = {
	"start-A", "start-b", "A-c", "A-b", "b-d", "A-end", "b-end",
};

struct Node
{
	std::string			name;
	std::vector<Node *> children;
	uint8_t				visited = 0;
};

struct Map
{
	std::map<std::string, Node *> nodes;
};

//#define DEBUG_OUTPUT

static Map ParseInput(const char *const data[], size_t length)
{
	Map map;

	for (size_t i = 0; i < length; i++)
	{
		// Parse line
		const char *pos = strchr(data[i], '-');
		std::string from(data[i], pos);
		std::string to(pos + 1);

		// Add nodes if they are missing
		Node *fromNode = map.nodes[from];
		Node *toNode   = map.nodes[to];
		if (!fromNode)
		{
			fromNode		= new Node();
			fromNode->name	= from;
			map.nodes[from] = fromNode;
		}
		if (!toNode)
		{
			toNode		  = new Node();
			toNode->name  = to;
			map.nodes[to] = toNode;
		}

		// Link nodes. Assuming no duplicate links
		fromNode->children.push_back(toNode);
		toNode->children.push_back(fromNode);
	}

	return map;
}

// Do a depth first search to find all of the paths, and count them.
// The 'joker' is the option to revisit a single lower case node once in the path.
// Note that this can overflow the stack if the input is invalid (e.g. two large caves are directly connected)
static int64_t DFS(Map &map, Node *start, Node *end, bool usedJoker)
{
	int64_t pathCount = 0;

#ifdef DEBUG_OUTPUT
	std::cout << start->name << ' ';
#endif

	if (islower(start->name[0]))
	{
		// We could get away with a bool for Task1, but we need a counter to handle the joker
		start->visited++;
	}

	for (Node *node : start->children)
	{
		if (node == end)
		{
			// Path found
#ifdef DEBUG_OUTPUT
			std::cout << "end\n";
#endif
			pathCount++;
		}
		else if (!node->visited)
		{
			pathCount += DFS(map, node, end, usedJoker);
		}
		else if (node->visited && !usedJoker && node->name != "start")
		{
			// Use joker
#ifdef DEBUG_OUTPUT
			std::cout << '*';
#endif
			pathCount += DFS(map, node, end, true);
		}
	}

	if (islower(start->name[0]))
	{
		start->visited--;
	}

#ifdef DEBUG_OUTPUT
	std::cout << '-' << start->name << ' ';
#endif

	return pathCount;
};

static int64_t Task1(const char *const data[], size_t length)
{
	Map map = ParseInput(data, length);

	return DFS(map, map.nodes["start"], map.nodes["end"], true);

	// Free up the nodes
	for (auto &pair : map.nodes)
	{
		delete pair.second;
	}
}

static size_t Task2(const char *const data[], size_t length)
{
	Map map = ParseInput(data, length);

	return DFS(map, map.nodes["start"], map.nodes["end"], false);

	// Free up the nodes
	for (auto &pair : map.nodes)
	{
		delete pair.second;
	}
}

void Day12()
{
	constexpr const char *resultName = " path count is ";

	//std::cout << "From test1, " << resultName << Task1(g_dataTest, std::size(g_dataTest)) << "\n";

	std::cout << "From task1, " << resultName << Task1(g_data1, std::size(g_data1)) << "\n";

	//std::cout << "From test2, " << resultName << Task2(g_dataTest, std::size(g_dataTest)) << "\n";

	std::cout << "From task2, " << resultName << Task2(g_data1, std::size(g_data1)) << "\n";
}
