#ifndef INC_6TH_HW_EXCEPTION_H
#define INC_6TH_HW_EXCEPTION_H

#include <string>
#include <stack>

class Exception {
private:
    std::string message;

public:
    inline Exception(const std::string &message);

    inline Exception(std::string &&message);

    inline const std::string &what() const;

};

class EvaluationException : public Exception {
public:
    using Exception::Exception;
};

class ParsingException : public Exception {
public:
    using Exception::Exception;
};

class MemoryException : public Exception {
public:
    using Exception::Exception;
};

inline Exception::Exception(const std::string &message) : message(message) {}

inline Exception::Exception(std::string &&message) : message(std::move(message)) {}

inline const std::string &Exception::what() const {
    return message;
}



#endif //INC_6TH_HW_EXCEPTION_H
