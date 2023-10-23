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
const std::string VALUE_OUTPUT = "output";
const std::string VALUE_O = "o";

struct Options {
    int r = 0;
    int g = 0;
    int b = 0;
    float a = 0.0f;
    bool grayscale = false;
    bool transparent = false;
    bool xFlag = false;
    bool yFlag = false;
    bool outputFlag = false;
    bool redFlag = false;
    bool greenFlag = false;
    bool blueFlag = false;
    bool alphaFlag = false;
    std::string value_output;
    std::vector<std::string> standalone_values;

};


bool processOptions(const std::vector<std::string> &arguments, Options &options);
void printStatus(Options &options);

#endif
