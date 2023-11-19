#ifndef OPTIONS_H
#define OPTIONS_H
#include <vector>
#include <string>


using args_t = std::vector<std::string>;

const std::string FLAG_X = "x";
const std::string FLAG_Y = "y";
const std::string FLAG_GRAYSCALE = "grayscale";
const std::string FLAG_T = "t";
const std::string FLAG_TRANSPARENT = "transparent";
const std::string VALUE_R = "r";
const std::string VALUE_RED = "red";
const std::string VALUE_G = "g";
const std::string VALUE_GREEN = "green";
const std::string VALUE_B = "b";
const std::string VALUE_BLUE = "blue";
const std::string VALUE_A = "a";
const std::string VALUE_ALPHA = "alpha";

bool processOptions(const std::vector<std::string>& arguments);

#endif
