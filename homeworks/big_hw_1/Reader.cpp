#include <iostream>
#include <vector>
#include <fstream>
#include "Reader.h"
#include "Exception.h"

using namespace std;

void Reader::process_file_args(const std::string& argument, std::vector<std::string>& expressions){
    ifstream fileName;
    string line;

    fileName.open(argument);

    if (fileName.good()) {
        while (getline(fileName, line)) {
            if (line.empty()) {
                continue;
            }
            expressions.push_back(line);
        }
    } else {
        throw FileException("Unable to open input file");
    }

    fileName.close();
}

void Reader::process_arguments(const std::vector<std::string>& arguments, std::vector<std::string>& expressions) {
    bool isfile = false;
    for (const string& argument : arguments) {
        if (argument[0] == '-') {
            if (argument == "-a") {
                isfile = false;
            } else if (argument == "-f") {
                isfile = true;
            } else {
                throw ArgumentException("Invalid option");
            }
        } else if (isfile) {
            process_file_args(argument, expressions);
        } else {
            expressions.push_back(argument);
        }
    }
}
