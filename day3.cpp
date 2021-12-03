#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

constexpr uint16_t g_data1[] = {
	0b010001110001, 0b110100000001, 0b111001001011, 0b111100001000, 0b000111101001, 0b101111001001, 0b111111000110, 0b000101110010, 0b001101001010, 0b000110001101, 0b011111111110, 0b101100010001,
	0b110101100001, 0b000000000110, 0b010011000011, 0b010101110010, 0b011001001001, 0b010011010111, 0b001101010110, 0b100000101000, 0b011100110010, 0b001011110001, 0b101110110011, 0b100011011101,
	0b000101111011, 0b000010011000, 0b110101101111, 0b011010101100, 0b111001011010, 0b011100110011, 0b000101000111, 0b111000110101, 0b110111010000, 0b111110010001, 0b010100100110, 0b010001011010,
	0b101100100001, 0b001000101010, 0b011111010010, 0b101011100110, 0b100111010110, 0b101000110100, 0b011010110001, 0b000010001000, 0b100001110111, 0b101001011100, 0b100100001011, 0b111010101110,
	0b001101101001, 0b000111111100, 0b011011111000, 0b111111111011, 0b101100011010, 0b011101001001, 0b111001001000, 0b010101010001, 0b100000011011, 0b100110100011, 0b010101110111, 0b111110110000,
	0b000001011111, 0b111110100111, 0b000100101000, 0b000100100011, 0b000011110001, 0b000001101101, 0b011000001000, 0b110111011010, 0b010000011010, 0b110101111011, 0b110110000001, 0b111101000100,
	0b101010100111, 0b101110110001, 0b000111110101, 0b001010000100, 0b010100000101, 0b111110000010, 0b110011001011, 0b010011000101, 0b010001101110, 0b010001101000, 0b110111000100, 0b111000010010,
	0b010000000101, 0b111110001100, 0b100110000110, 0b100100000011, 0b011101101011, 0b011001100010, 0b110011111011, 0b011001111000, 0b110001001110, 0b011111001000, 0b100010001011, 0b111001001101,
	0b100000110000, 0b100000001000, 0b011001011010, 0b111110100011, 0b100111000100, 0b011000111010, 0b011101001100, 0b000110011001, 0b101101111011, 0b001101001011, 0b100101111100, 0b111001001110,
	0b010100011110, 0b100101011010, 0b110101110000, 0b111101110110, 0b001010101100, 0b011010000011, 0b110001010011, 0b101000100011, 0b110010111110, 0b100000010100, 0b101011100000, 0b111110111000,
	0b000000100011, 0b100010000100, 0b011111001100, 0b010100111011, 0b101110001100, 0b101101111100, 0b011000101110, 0b001010010010, 0b011001011000, 0b010011100001, 0b011111111101, 0b000001111011,
	0b011010110100, 0b011001100000, 0b111101000110, 0b010110101001, 0b011100001111, 0b000000001110, 0b110010110111, 0b100110011101, 0b101010000000, 0b010100011111, 0b110111001110, 0b101100011000,
	0b101101101111, 0b110110111001, 0b101111111010, 0b000011010101, 0b000000001000, 0b100011000110, 0b000000110110, 0b100011000001, 0b110011111110, 0b110001000101, 0b110110100100, 0b010001101010,
	0b110100000011, 0b110100001010, 0b000010110111, 0b100011001010, 0b001111111011, 0b000110111010, 0b011110001100, 0b011110110000, 0b100100110000, 0b100011111110, 0b100000000011, 0b100101110010,
	0b101010110110, 0b110000011001, 0b101110111101, 0b000110001000, 0b001110111111, 0b110000010001, 0b100101111111, 0b000001001001, 0b111100101011, 0b111110101110, 0b000110000111, 0b000000000001,
	0b110100101111, 0b011010100110, 0b000010110001, 0b011000100111, 0b110011010011, 0b001101101010, 0b000011111001, 0b010110001111, 0b110000011000, 0b111010100000, 0b011101110111, 0b010001111001,
	0b100000111111, 0b101110100111, 0b000110001011, 0b011110001110, 0b100000000000, 0b011010100000, 0b100111100100, 0b010011000001, 0b100100011100, 0b010010101100, 0b100010101001, 0b000101001110,
	0b001101011010, 0b011100100111, 0b001010100100, 0b110010100000, 0b100111110001, 0b001111001000, 0b111000101011, 0b011011101001, 0b110001011001, 0b111011110111, 0b110010000001, 0b001011010010,
	0b001011011100, 0b101000110001, 0b011000010010, 0b111011000110, 0b001011110101, 0b000111001001, 0b110110100110, 0b011101111111, 0b111001101101, 0b000100011110, 0b100011101010, 0b011111111011,
	0b011110110001, 0b001010111111, 0b100101001011, 0b001101110110, 0b100100000001, 0b111000111001, 0b000101100100, 0b110011011000, 0b101010011011, 0b101100110111, 0b111011011100, 0b000011111110,
	0b101001101010, 0b011000111100, 0b001101010000, 0b110000000011, 0b100110011000, 0b001000011100, 0b010110100101, 0b000111101100, 0b110010111101, 0b010010101010, 0b001001001011, 0b001010011011,
	0b111010101011, 0b111111001110, 0b011011110001, 0b011101010101, 0b011111110010, 0b000111111110, 0b000110110011, 0b111100001101, 0b000000100101, 0b000010111111, 0b111010100101, 0b100101111000,
	0b000100101100, 0b000111100010, 0b001010010000, 0b100100010001, 0b100011000101, 0b001000001010, 0b001000000011, 0b011100011010, 0b101110011111, 0b000011101101, 0b111011010110, 0b110100111011,
	0b101110110110, 0b011110001011, 0b111101001111, 0b011100101110, 0b101110101000, 0b000101000001, 0b100010110110, 0b101101001101, 0b110000001010, 0b000111001111, 0b000000010001, 0b001110100101,
	0b100100001001, 0b100011111000, 0b110011000101, 0b110111111000, 0b101100101111, 0b000000110100, 0b101111111011, 0b111001010101, 0b110110010111, 0b011100011001, 0b111100110010, 0b011011101000,
	0b110110010010, 0b011000001010, 0b110101000110, 0b100000100101, 0b010010101101, 0b110100001011, 0b110000010011, 0b100011001101, 0b001100011000, 0b100010110111, 0b110100110000, 0b011011001000,
	0b110110100000, 0b010000101001, 0b111100011010, 0b000000010100, 0b010110000000, 0b110010000100, 0b100001010110, 0b000010100110, 0b110011110000, 0b000000111101, 0b010011010101, 0b111101100011,
	0b001001101010, 0b111110010110, 0b101100001010, 0b000001000110, 0b110111001000, 0b000100111000, 0b001110111000, 0b010010110101, 0b010001001100, 0b100101100001, 0b111010101010, 0b111101000000,
	0b101010101100, 0b001000001100, 0b110001001010, 0b101100111100, 0b110110100001, 0b011110000001, 0b001011011000, 0b101101101100, 0b100110000101, 0b010101110000, 0b110101001110, 0b100011011001,
	0b011100001000, 0b000110111001, 0b010101111101, 0b101101100010, 0b011101101100, 0b001011110111, 0b101001001100, 0b101001110100, 0b000010011011, 0b110001101111, 0b110110001010, 0b100101101010,
	0b110110011001, 0b001011110000, 0b000111100111, 0b110111100001, 0b110010100100, 0b110010001001, 0b011010001110, 0b010100110101, 0b011011111001, 0b111111101101, 0b111111001000, 0b110001000100,
	0b001101010100, 0b010010001111, 0b000000001111, 0b111000101010, 0b101101101010, 0b011010010100, 0b011011100100, 0b111001110101, 0b101000011101, 0b111100001100, 0b011001010011, 0b111001100111,
	0b000100000100, 0b100011000111, 0b010100001111, 0b110010111100, 0b100100001111, 0b110101110110, 0b100111010101, 0b001100110111, 0b111010110001, 0b011000011100, 0b101100100100, 0b011100010111,
	0b000001101110, 0b011101000111, 0b011100101011, 0b001111011010, 0b101100100011, 0b001000101110, 0b001100011011, 0b010010011111, 0b111100101001, 0b110111111001, 0b110111010110, 0b111000110010,
	0b000010101100, 0b010101101101, 0b100110111110, 0b010110011001, 0b001100010111, 0b010101111001, 0b011011001100, 0b111100110000, 0b011110000011, 0b101010111110, 0b011000100010, 0b000001110100,
	0b011111100010, 0b111011110011, 0b011110101000, 0b000110011010, 0b111001101010, 0b011000101000, 0b110000100000, 0b100101111001, 0b100001101100, 0b101100100111, 0b100010000001, 0b010100010001,
	0b001101011001, 0b110101101000, 0b101110001011, 0b101101000000, 0b010000100110, 0b001101000010, 0b100011001001, 0b000010100001, 0b101000011111, 0b110000101001, 0b110101000111, 0b101101000011,
	0b111111110100, 0b111000100010, 0b100000111011, 0b000100010010, 0b100010100110, 0b100110110110, 0b011101011011, 0b101101000010, 0b000100111110, 0b111101111110, 0b000100001011, 0b011100101001,
	0b101010100001, 0b110110001011, 0b000001010001, 0b001000100110, 0b101100000111, 0b100010111111, 0b100000010101, 0b111100010100, 0b010001100010, 0b110001001001, 0b000100011111, 0b010110111101,
	0b111111110111, 0b100011011110, 0b001011011110, 0b010110001011, 0b010100001010, 0b001101101011, 0b110110111110, 0b110101010010, 0b111010011001, 0b000001000010, 0b100100110110, 0b100110100010,
	0b001101110111, 0b001110101010, 0b001110101011, 0b011101100010, 0b101101001010, 0b110100011101, 0b110010101100, 0b010010011101, 0b000101011111, 0b010111100011, 0b001111101011, 0b100000110001,
	0b110101011110, 0b000000010111, 0b000010101101, 0b000111010100, 0b001100000001, 0b111011011101, 0b110001110110, 0b111010101111, 0b101101011100, 0b010000101010, 0b011111000010, 0b000100100110,
	0b100011011100, 0b010110011101, 0b011001001011, 0b001001010111, 0b101100101011, 0b101000110111, 0b010000011111, 0b101011111100, 0b100100100001, 0b111011110000, 0b001100110011, 0b110011100000,
	0b111101100101, 0b011100010010, 0b010001100001, 0b110001100011, 0b000000001100, 0b010101110100, 0b110011010001, 0b000110001100, 0b101101000110, 0b000010010000, 0b000010100111, 0b001111111100,
	0b010110010000, 0b000110000000, 0b011011110101, 0b000101000110, 0b001101011000, 0b100011100010, 0b101100010000, 0b001011001100, 0b001110010110, 0b000100000110, 0b100110111000, 0b110101110001,
	0b101000001000, 0b100101000011, 0b101010101010, 0b101111001101, 0b110001100110, 0b011110101110, 0b110011100100, 0b011101101001, 0b010001111101, 0b110101000101, 0b111100001010, 0b101001001011,
	0b101011101111, 0b110011101110, 0b101010011010, 0b001010011101, 0b111111111001, 0b011000010011, 0b111010001101, 0b001010110101, 0b011001000000, 0b010010110010, 0b100111001001, 0b010010000111,
	0b100100110001, 0b000110010111, 0b111000000001, 0b100111111111, 0b100100011111, 0b011011101011, 0b111100010011, 0b001010010101, 0b100001110110, 0b000101010011, 0b110110011110, 0b110010110000,
	0b110101001001, 0b110111101001, 0b110001101011, 0b101110111011, 0b101100010011, 0b111000101101, 0b100101101100, 0b111000101000, 0b101011011110, 0b011000100000, 0b111011001100, 0b010110110111,
	0b001101001000, 0b011011000110, 0b100100101100, 0b011011101111, 0b100000010000, 0b110110101100, 0b111101101101, 0b101111011000, 0b100110011010, 0b110101010110, 0b110110010110, 0b000101000010,
	0b010100100000, 0b100110011111, 0b100011100000, 0b111000000011, 0b011111010001, 0b111011110101, 0b110100001101, 0b000001001101, 0b010111010100, 0b110110011000, 0b111101101011, 0b101011110010,
	0b111010001000, 0b001111110111, 0b110101000001, 0b101101101001, 0b110100001001, 0b110100111111, 0b111011000001, 0b001000110000, 0b111001100110, 0b000100111100, 0b010101010000, 0b000000000100,
	0b001111110010, 0b011010001010, 0b000111011100, 0b001000000111, 0b110101010100, 0b010110010111, 0b100101110011, 0b000101000100, 0b100101011101, 0b010100100001, 0b011001100111, 0b010101001111,
	0b110011100010, 0b010100001110, 0b000010101000, 0b001011101000, 0b001000011010, 0b001100101011, 0b011110111000, 0b110100000100, 0b101011001010, 0b111011010101, 0b010011101011, 0b001111111001,
	0b000101010111, 0b011100100010, 0b111101011101, 0b011010111001, 0b101110101110, 0b101011111111, 0b011100011101, 0b011001011110, 0b000100011010, 0b010100101110, 0b010000001011, 0b100001011110,
	0b000011101010, 0b010101100000, 0b001000010010, 0b001100011111, 0b100111110101, 0b011101100100, 0b101101110001, 0b000110010001, 0b001110000000, 0b000000011010, 0b101101010100, 0b111101110011,
	0b010011001000, 0b000011000001, 0b110110000110, 0b011011101100, 0b010011111011, 0b001101010011, 0b111000001100, 0b111100010111, 0b111000100100, 0b000011111100, 0b000011111000, 0b000000101110,
	0b001001000010, 0b101011011000, 0b010110111111, 0b100001000010, 0b111001010010, 0b010110000110, 0b010001111111, 0b110101001111, 0b100001100100, 0b100100011011, 0b100100100010, 0b110110001101,
	0b101001011000, 0b101100100101, 0b111001000001, 0b100100000000, 0b101001011110, 0b100110111010, 0b111101011010, 0b010110011111, 0b000001010111, 0b101000011010, 0b000111011011, 0b101000001001,
	0b010010000010, 0b111110100100, 0b000100110001, 0b001101111011, 0b000110110001, 0b101111111100, 0b111110110101, 0b000010011101, 0b100001100110, 0b001011000110, 0b111100000001, 0b100111101000,
	0b001001101011, 0b011100111111, 0b110001010100, 0b110000011110, 0b100101111101, 0b101000111000, 0b010110001010, 0b000100100101, 0b001011011101, 0b100110100100, 0b000011011110, 0b011101111000,
	0b001110101000, 0b011010101001, 0b010000100100, 0b010000100101, 0b111110011100, 0b110010000110, 0b000100111101, 0b100011101100, 0b111101111010, 0b110111111101, 0b010100000011, 0b111110010000,
	0b101001011101, 0b000000000010, 0b100100001010, 0b010100011101, 0b011111110001, 0b110110101011, 0b001100101100, 0b101101101000, 0b100001000000, 0b011100010011, 0b001011111111, 0b010001110101,
	0b000100000101, 0b000111010010, 0b000011101111, 0b010001100101, 0b000110010100, 0b011100100001, 0b111110110100, 0b011100010100, 0b011111100100, 0b010001001110, 0b011000011001, 0b010101100010,
	0b100110000100, 0b011111001101, 0b001101001111, 0b100111000000, 0b001011110010, 0b110000101011, 0b010001100110, 0b111000011101, 0b100010110010, 0b010110010110, 0b000010110110, 0b100100101001,
	0b011010010110, 0b111010101100, 0b111001110011, 0b010010000110, 0b010111111000, 0b111001010011, 0b001100100011, 0b111100111010, 0b111011111110, 0b000101110001, 0b000101111010, 0b101111100101,
	0b000100001010, 0b011111010101, 0b100100011110, 0b011010010010, 0b101111100111, 0b110100100110, 0b001001010100, 0b111100000010, 0b000010011100, 0b010111011100, 0b111101001001, 0b111111110110,
	0b000010111001, 0b110011111111, 0b001000101100, 0b111111010011, 0b101010110010, 0b110111000000, 0b011010100100, 0b100111010001, 0b100100110011, 0b001011111001, 0b111100100011, 0b111011011111,
	0b110000000110, 0b100101011111, 0b100001011111, 0b010001100111, 0b000001110010, 0b001001110010, 0b010000110111, 0b110010011011, 0b101110111111, 0b100011110110, 0b100110010110, 0b001110101111,
	0b111110010011, 0b111000011100, 0b101101011001, 0b100000101111, 0b011001000001, 0b110001000110, 0b101011101101, 0b011000110110, 0b001110001110, 0b001001111101, 0b111111111111, 0b101011101100,
	0b000001011101, 0b111000010000, 0b001110010011, 0b101101000111, 0b001101011101, 0b001010110011, 0b011101110011, 0b001010101000, 0b000100001101, 0b010110000011, 0b000001010101, 0b101011110001,
	0b111010010101, 0b001110100000, 0b000011100001, 0b110001110111, 0b011011110111, 0b110100101011, 0b110111011110, 0b001111011001, 0b001111000111, 0b111100010101, 0b110000011010, 0b111000101111,
	0b011100001100, 0b101000000001, 0b000100110011, 0b101001111101, 0b100010101110, 0b010001010100, 0b110111100010, 0b001100100100, 0b010000011100, 0b111010111111, 0b101111101101, 0b101010011000,
	0b001001011001, 0b100100001110, 0b100000110110, 0b100110001010, 0b010010011001, 0b010101101011, 0b010000001111, 0b101111101111, 0b101000111011, 0b111100111111, 0b101110001001, 0b001011000011,
	0b110000100101, 0b011100100110, 0b000010100101, 0b011001110110, 0b111101000010, 0b010011111110, 0b011100111100, 0b101111000001, 0b010110111011, 0b011010110010, 0b001001100110, 0b011101100110,
	0b001110000110, 0b111011111111, 0b000011010011, 0b000110001110, 0b101001001000, 0b110111010001, 0b000111111000, 0b111111101011, 0b000001110110, 0b101011010100, 0b001010110100, 0b011000101011,
	0b001111010001, 0b110011010100, 0b100101111011, 0b100110010100, 0b000110000011, 0b111111000000, 0b001111100000, 0b000101101010, 0b101000011110, 0b011101010100, 0b101001011010, 0b101010100000,
	0b111011111101, 0b100101001000, 0b010100111110, 0b110100010101, 0b000001011011, 0b110101000010, 0b101100000011, 0b100101000100, 0b011011101010, 0b111110010100, 0b000100101111, 0b011111101010,
	0b011011000111, 0b011001100100, 0b101110111000, 0b111100001111, 0b000111110010, 0b000010010111, 0b001010001010, 0b010010001101, 0b110011101000, 0b000110111100, 0b110101101001, 0b101000000100,
	0b110000001101, 0b100100111000, 0b101100000101, 0b110011001111, 0b010011001101, 0b100111000110, 0b001111111010, 0b000000000101, 0b000011000000, 0b111011101110, 0b111110101001, 0b110000101010,
	0b110111101101, 0b010111110011, 0b000101110111, 0b010111010111, 0b011011111110, 0b101101000001, 0b101000101101, 0b101100100000, 0b100100000100, 0b001000010101, 0b110000001001, 0b010111111101,
	0b100001101011, 0b110011110110, 0b100110101011, 0b011001111010, 0b101000001011, 0b011001101111, 0b101011100111, 0b001011010000, 0b111100111000, 0b111001001001, 0b010001011000, 0b101010110101,
	0b001111001101, 0b000000111000, 0b010111001110, 0b110100010000, 0b111101111100, 0b000000001101, 0b110010001011, 0b110000111100, 0b101010000110, 0b101011011111, 0b101000011011, 0b001001110011,
	0b001011111100, 0b100110001001, 0b101000011000, 0b011100110101,
};

constexpr uint16_t g_dataTest[] = {
	0b00100, 0b11110, 0b10110, 0b10111, 0b10101, 0b01111, 0b00111, 0b11100, 0b10000, 0b11001, 0b00010, 0b01010,
};

static int64_t Task1(const uint16_t data[], size_t length, int bitCount)
{
	assert(bitCount <= 16);

	uint64_t gamma	 = 0;
	uint64_t epsilon = 0;

	const uint16_t topBit  = 1 << (bitCount - 1);
	const uint16_t bitMask = (1 << bitCount) - 1;

	uint32_t bitcount[16] = {};
	for (size_t i = 0; i < length; i++)
	{
		for (int bit = 0; bit < bitCount; bit++)
		{
			bitcount[bit] += (data[i] & (topBit >> bit)) != 0;
		}
	}

	for (int bit = 0; bit < bitCount; bit++)
	{
		gamma |= (bitcount[bit] > (length / 2)) ? (topBit >> bit) : 0;
	}

	epsilon = gamma ^ bitMask;

	return gamma * epsilon;
}

static int64_t Task2(const uint16_t data[], size_t length, int bitCount)
{
	assert(bitCount <= 16);

	const uint16_t topBit  = 1 << (bitCount - 1);
	const uint16_t bitMask = (1 << bitCount) - 1;

	std::vector<bool> valuesToDiscardO2;
	std::vector<bool> valuesToDiscardCO2;
	valuesToDiscardO2.resize(length);
	valuesToDiscardCO2.resize(length);

	size_t numDiscardedO2  = 0;
	size_t numDiscardedCO2 = 0;

	uint64_t oxygenGeneratorRating = 0;
	uint64_t CO2ScrubberRating	   = 0;

	for (int bit = 0; bit < bitCount; bit++)
	{
		// Count total bits, of the ones that we haven't discarded already.
		// Note that we count 1s for Oxygen, and Zeros for CO2, which means the rest of the code can treat them identically.
		int bitCountO2	= 0;
		int bitCountCO2 = 0;
		for (size_t i = 0; i < length; i++)
		{
			if (!valuesToDiscardO2[i])
			{
				bitCountO2 += (data[i] & (topBit >> bit)) != 0;
			}
			if (!valuesToDiscardCO2[i])
			{
				bitCountCO2 += (data[i] & (topBit >> bit)) == 0;
			}
		}

		// Note that we double the left side instead of halving the right side in order to handle odd numbers correctly
		int bitToKeepOG	 = (bitCountO2 * 2 >= (length - numDiscardedO2)) ? 1 : 0;
		int bitToKeepCO2 = (bitCountCO2 * 2 > (length - numDiscardedCO2)) ? 1 : 0;

		// Discard all of the values which don't match the ones we want to keep
		for (size_t i = 0; i < length; i++)
		{
			int bitSet = (data[i] & (topBit >> bit)) != 0;
			if (bitSet != bitToKeepOG)
			{
				if (!valuesToDiscardO2[i])
				{
					valuesToDiscardO2[i] = true;
					numDiscardedO2++;
				}
			}
			if (bitSet != bitToKeepCO2)
			{
				if (!valuesToDiscardCO2[i])
				{
					valuesToDiscardCO2[i] = true;
					numDiscardedCO2++;
				}
			}
		}

		// Check to see if we have one entry left. If so, find it.
		if (numDiscardedO2 == length - 1)
		{
			for (int j = 0; j < length; j++)
			{
				if (!valuesToDiscardO2[j])
				{
					oxygenGeneratorRating = data[j];
					break;
				}
			}
		}

		// Check to see if we have one entry left. If so, find it.
		if (numDiscardedCO2 == length - 1)
		{
			for (int j = 0; j < length; j++)
			{
				if (!valuesToDiscardCO2[j])
				{
					CO2ScrubberRating = data[j];
					break;
				}
			}
		}

		// Small optimization - stop once we have both values.
		// Note that it's safe to repeat the algorithm as it won't discard any values when there's only one left.
		if (numDiscardedO2 == length - 1 && numDiscardedCO2 == length - 1)
		{
			break;
		}
	}

	return oxygenGeneratorRating * CO2ScrubberRating;
}

void Day3()
{
	//std::cout << "From test1, power consumption was " << Task1(g_dataTest, std::size(g_dataTest), 5) << "\n";

	std::cout << "From task1, power consumption is " << Task1(g_data1, std::size(g_data1), 12) << "\n";

	//std::cout << "From test2, life support rating was " << Task2(g_dataTest, std::size(g_dataTest), 5) << "\n";

	std::cout << "From task2 life support rating was " << Task2(g_data1, std::size(g_data1), 12) << "\n";
}
