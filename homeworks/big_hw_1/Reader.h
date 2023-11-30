#ifndef INC_6TH_HW_READER_H
#define INC_6TH_HW_READER_H

#include <iostream>
#include <string>
#include <vector>

class Reader {
public:
    static void process_arguments(const std::vector<std::string>& arguments, std::vector <std::string>& expressions);

private:
    static void process_file_args(const std::string& argument, std::vector <std::string>& expressions);
};

#endif //INC_6TH_HW_READER_H
