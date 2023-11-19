#ifndef UNTITLED_COUNTER_H
#define UNTITLED_COUNTER_H

#include <iostream>

class Statistics{
public:
    size_t lines = 0;
    size_t sentences = 0;
    size_t words = 0;
    size_t numbers = 0;
    size_t letters = 0;
    size_t digits = 0;
    size_t spaces = 0;
    size_t symbols = 0;
    long integers = 0;
    double floats = 0;
};

class Counter{
public:

    static void process(const std::string& fileName, Statistics* statistics);

    static void process(std::istream& is, Statistics* statistics);

    static void print(const std::string& fileName, const Statistics* statistics);

    static void print(std::ostream& os, const Statistics* statistics);

private:

    static bool isWord(const std::string& word);

    static bool isInteger(const std::string& word);

    static bool isFloatNumber(const std::string& word);

    static void convertToInteger(const std::string& word, Statistics* statistics);

    static void convertToFloatNumber(const std::string& word, Statistics* statistics);

    static void checkAndProcess(std::string& word, Statistics* statistics);

    static void updateStatistics(Statistics* statistics, const std::string& line, std::string& word);
};


#endif //UNTITLED_COUNTER_H