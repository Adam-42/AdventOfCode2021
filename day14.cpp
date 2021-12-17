#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

constexpr const char *g_data1[] = {
	"VPPHOPVVSFSVFOCOSBKF",
	"",
	"CO -> B",
	"CV -> N",
	"HV -> H",
	"ON -> O",
	"FS -> F",
	"NS -> S",
	"VK -> C",
	"BV -> F",
	"SC -> N",
	"NV -> V",
	"NC -> F",
	"NH -> B",
	"BO -> K",
	"FC -> H",
	"NB -> H",
	"HO -> F",
	"SB -> N",
	"KP -> V",
	"OS -> C",
	"OB -> P",
	"SH -> N",
	"BC -> H",
	"CK -> H",
	"SO -> N",
	"SP -> P",
	"CF -> P",
	"KV -> F",
	"CS -> V",
	"FF -> P",
	"VS -> V",
	"CP -> S",
	"PH -> V",
	"OP -> K",
	"KH -> B",
	"FB -> S",
	"CN -> H",
	"KS -> P",
	"FN -> O",
	"PV -> O",
	"VC -> S",
	"HF -> N",
	"OC -> O",
	"PK -> V",
	"KC -> C",
	"HK -> C",
	"PO -> N",
	"OO -> S",
	"VH -> N",
	"CC -> K",
	"BP -> K",
	"HC -> K",
	"FV -> K",
	"KF -> V",
	"VF -> C",
	"HN -> S",
	"VP -> B",
	"HH -> O",
	"FO -> O",
	"PC -> N",
	"KK -> C",
	"PN -> P",
	"NN -> C",
	"FH -> N",
	"VV -> O",
	"OK -> V",
	"CB -> N",
	"SN -> H",
	"VO -> H",
	"BB -> C",
	"PB -> F",
	"NF -> P",
	"KO -> S",
	"PP -> K",
	"NO -> O",
	"SF -> N",
	"KN -> S",
	"PS -> O",
	"VN -> V",
	"SS -> N",
	"BF -> O",
	"HP -> H",
	"HS -> N",
	"BS -> S",
	"VB -> F",
	"PF -> K",
	"SV -> V",
	"BH -> P",
	"FP -> O",
	"CH -> P",
	"OH -> K",
	"OF -> F",
	"HB -> V",
	"FK -> V",
	"BN -> V",
	"SK -> F",
	"OV -> C",
	"NP -> S",
	"NK -> S",
	"BK -> C",
	"KB -> F",
};

constexpr const char *g_dataTest[] = {
	"NNCB", "", "CH -> B", "HH -> N", "CB -> H", "NH -> C", "HB -> C", "HC -> B", "HN -> C", "NN -> C", "BH -> H", "NC -> B", "NB -> B", "BN -> B", "BB -> N", "BC -> B", "CC -> N", "CN -> C",
};

struct Rule
{
	char match[2];
	char insert;
};

static int64_t Task1(const char *const data[], size_t length, int steps)
{
	std::string polymer = data[0];

	std::vector<Rule> input;

	for (size_t i = 2; i < length; i++)
	{
		// Parse line
		Rule r;
		r.match[0] = data[i][0];
		r.match[1] = data[i][1];
		r.insert   = data[i][6];
		input.push_back(r);
	}

	for (int step = 0; step < steps; step++)
	{
		std::string oldPolymer = polymer;
		polymer.clear();
		for (int x = 0; x < oldPolymer.length() - 1; x++)
		{
			char thingToInsert = 0;
			for (const Rule &r : input)
			{
				if (oldPolymer[x] == r.match[0] && oldPolymer[x + 1] == r.match[1])
				{
					thingToInsert = r.insert;
					break;
				}
			}
			polymer.push_back(oldPolymer[x]);
			if (thingToInsert)
			{
				polymer.push_back(thingToInsert);
			}
		}
		polymer.push_back(oldPolymer[oldPolymer.length() - 1]);

		//std::cout << polymer << '\n';
	}

	int64_t frequency[128] = {};
	for (char c : polymer)
	{
		frequency[c]++;
	}

	int64_t maxFrequency = 0;
	int64_t minFrequency = std::numeric_limits<int64_t>::max();
	for (int64_t x : frequency)
	{
		if (x != 0)
		{
			maxFrequency = std::max(maxFrequency, x);
			minFrequency = std::min(minFrequency, x);
		}
	}

	return maxFrequency - minFrequency;
}

static int64_t Task2(const char *const data[], size_t length, int steps)
{
	std::string polymer = data[0];

	for (char &c : polymer)
	{
		c -= 'A';
	}

	std::vector<Rule> input;

	for (size_t i = 2; i < length; i++)
	{
		// Parse line
		Rule r;
		r.match[0] = data[i][0] - 'A';
		r.match[1] = data[i][1] - 'A';
		r.insert   = data[i][6] - 'A';
		input.push_back(r);
	}

	// We could reduce the storage requrement and performance cost if we assumed that not every letter could be in the polymer
	// We could also make this more generic with a bigger array, and not subtracting 'A' above
	std::array<int64_t, 26 * 26> letterPairFrequency = {};

	// Look at each pair of letters in the original string and count the pairs
	for (int x = 0; x < polymer.length() - 1; x++)
	{
		uint16_t pair = polymer[x] + (polymer[x + 1] * 26);
		letterPairFrequency[pair]++;
	}

	for (int step = 0; step < steps; step++)
	{
		std::array<int64_t, 26 * 26> newFrequency = {};

		for (int x = 0; x < 26 * 26; x++)
		{
			uint64_t pair = letterPairFrequency[x];
			if (pair > 0)
			{
				char c1 = x % 26;
				char c2 = x / 26;

				// Assume for now that no rules will match
				newFrequency[x] += letterPairFrequency[x];
				for (const Rule &r : input)
				{
					if (c1 == r.match[0] && c2 == r.match[1])
					{
						// A rule has matched!
						uint16_t pair1 = c1 + (r.insert * 26);
						uint16_t pair2 = r.insert + (c2 * 26);
						// Increment the frequencies of the letter pairs that we generate by modifying the matching pair
						newFrequency[pair1] += letterPairFrequency[x];
						newFrequency[pair2] += letterPairFrequency[x];
						// Revert the change from the incorrect assumption above
						newFrequency[x] -= letterPairFrequency[x];
						break;
					}
				}
			}
		}

		letterPairFrequency = newFrequency;
	}

	std::array<int64_t, 26> letterFrequency = {};
	for (int x = 0; x < 26 * 26; x++)
	{
		char c1 = x % 26;
		char c2 = x / 26;

		letterFrequency[c1] += letterPairFrequency[x];
		letterFrequency[c2] += letterPairFrequency[x];
	}

	// The first and last letters don't get counted twice like every other letter does, because they are each only in one pair
	letterFrequency[polymer[0]]++;
	letterFrequency[polymer[polymer.size() - 1]]++;

	int64_t maxFrequency = 0;
	int64_t minFrequency = std::numeric_limits<int64_t>::max();
	for (int64_t x : letterFrequency)
	{
		if (x != 0)
		{
			maxFrequency = std::max(maxFrequency, x);
			minFrequency = std::min(minFrequency, x);
		}
	}

	// We need to divide by two because each letter is counted in two letter pairs
	// (except the first and last letter in the string, which we handled earlier)
	return (maxFrequency - minFrequency) / 2;
}

void Day14()
{
	constexpr const char *resultName = " frequency delta is ";

	//std::cout << "From test1, " << resultName << Task1(g_dataTest, std::size(g_dataTest), 10) << "\n";

	std::cout << "From task1, " << resultName << Task1(g_data1, std::size(g_data1), 10) << "\n";

	//std::cout << "From test2, " << resultName << Task2(g_dataTest, std::size(g_dataTest), 40) << '\n';

	std::cout << "From task2, " << resultName << Task2(g_data1, std::size(g_data1), 40) << '\n';
}
