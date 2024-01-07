
#ifndef INC_11_12TH_HW_EXCEPTION_H
#define INC_11_12TH_HW_EXCEPTION_H

#include <string>

class Exception {
public:
    virtual const char *message() const = 0;

};

// ------------------ MemoryException ------------------

class MemoryException : public Exception {
private:
    const char *message_;
public:
    MemoryException(const char *message);

    const char *message() const override;
};

inline MemoryException::MemoryException(const char *message) : message_(message) {}

inline const char *MemoryException::message() const {
    return message_;
}

class DynamicallyConstructedMessages : public Exception {
private:
    std::string message_;
public:
    DynamicallyConstructedMessages(const std::string &message);

    const char *message() const override;
};

// ------------------ DynamicallyConstructedMessages ------------------

inline DynamicallyConstructedMessages::DynamicallyConstructedMessages(const std::string &message) : message_(message) {}

inline const char *DynamicallyConstructedMessages::message() const {
    return message_.c_str();
}

class IdentifierException : public DynamicallyConstructedMessages {
public:
    using DynamicallyConstructedMessages::DynamicallyConstructedMessages;
};

class ElementException : public DynamicallyConstructedMessages {
public:
    using DynamicallyConstructedMessages::DynamicallyConstructedMessages;
};

class ConflictException : public DynamicallyConstructedMessages {
public:
    using DynamicallyConstructedMessages::DynamicallyConstructedMessages;
};

class FileException : public DynamicallyConstructedMessages {
public:
    using DynamicallyConstructedMessages::DynamicallyConstructedMessages;
};

#endif //INC_11_12TH_HW_EXCEPTION_H
