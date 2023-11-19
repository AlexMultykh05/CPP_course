#include <fstream>
#include <string>
#include "Counter.h"

using namespace std;

bool Counter::isWord(const string &word) {
    if (word.empty())
        return false;

    for (char i: word) {
        if (!isalpha(i))
            return false;
    }

    return true;
}

bool Counter::isInteger(const string &word) {
    if (word.empty())
        return false;

    for (char i: word) {
        if (!isdigit(i))
            return false;
    }

    return true;
}

bool Counter::isFloatNumber(const string &word) {
    if (word.empty())
        return false;

    bool dot = false;
    for (char i: word) {
        if (!isdigit(i) && i != '.')
            return false;
        if (i == '.') {
            if (dot)
                return false;
            dot = true;
        }
    }

    return dot;
}


void Counter::convertToInteger(const string &word, Statistics *statistics) {
    statistics -> integers += stoi(word);
}

void Counter::convertToFloatNumber(const string &word, Statistics *statistics) {
    statistics -> symbols++;
    statistics -> floats += stof(word);
}

void Counter::checkAndProcess(string &word, Statistics *statistics) {
    if (isWord(word)) {
        statistics -> words++;
    } else if (isInteger(word)) {
        convertToInteger(word, statistics);
        statistics -> numbers++;
    } else if (isFloatNumber(word)) {
        convertToFloatNumber(word, statistics);
        statistics -> numbers++;
    }
}

void Counter::updateStatistics(Statistics *statistics, const string &line, string &word) {
    for (auto it = line.begin(); it != line.end(); it++) {
        if (isalpha(*it)) {
            statistics -> letters++;
        } else if (isdigit(*it)) {
            statistics -> digits++;
        }
        if (*it == ' ') {
            statistics->spaces++;
            checkAndProcess(word, statistics);
            word = "";
        } else if (*it == '!' || *it == '?') {
            statistics -> symbols++;
            checkAndProcess(word, statistics);
            statistics -> sentences++;
            word = "";
        } else if (*it == '.' && ((next(it)) == line.end() || *next(it) == ' ')) {
            statistics->symbols++;
            checkAndProcess(word, statistics);
            statistics -> sentences++;
            word = "";
        } else {
            word += *it;
        }
    }
    checkAndProcess(word, statistics);
}

void Counter::process(const string &fileName, Statistics *statistics) {
    ifstream fileIn;

    fileIn.open(fileName);
    if (!fileIn.good()) {
        throw "Unable to open input file";
    }
    process(fileIn, statistics);

    fileIn.close();
}

void Counter::process(istream &is, Statistics *statistics) {
    string line;
    while (getline(is, line)) {
        string word;
        statistics -> lines++;
        updateStatistics(statistics, line, word);
    }
}

void Counter::print(const string &fileName, const Statistics *statistics) {
    ofstream fileOut = ofstream(fileName);

    if (!fileOut.good()) {
        throw "Unable to open output file";
    }
    print(fileOut, statistics);

    fileOut.close();
}

void Counter::print(ostream &os, const Statistics *statistics) {
    os << "Lines: " << statistics -> lines << endl;
    os << "Sentences: " << statistics -> sentences << endl;
    os << "Words: " << statistics -> words << endl;
    os << "Numbers: " << statistics -> numbers << endl;
    os << "Letters: " << statistics -> letters << endl;
    os << "Digits: " << statistics -> digits << endl;
    os << "Spaces: " << statistics -> spaces << endl;
    os << "Symbols: " << statistics -> symbols << endl;
    os << "Integers: " << statistics -> integers << endl;
    os << "Floats: " << statistics -> floats << endl;
}