#include <iostream>

extern void Day1();
extern void Day2();
extern void Day3();
extern void Day4();
extern void Day5();
extern void Day6();
extern void Day7();
extern void Day8();
extern void Day9();
extern void Day10();
extern void Day11();
extern void Day12();
extern void Day13();
extern void Day14();
extern void Day15();
extern void Day16();
extern void Day17();
extern void Day18();
extern void Day19();
extern void Day20();
extern void Day21();
extern void Day22();
extern void Day23();
extern void Day24();
extern void Day25();

#define DAY(x) std::cout << "Day" #x "\n----\n"; Day##x();

int main(int argc, char** argv)
{
	DAY(1);
	DAY(2);
	DAY(3);
	DAY(4);
	DAY(5);
	DAY(6);
}
