# pragma once

#include <QTextStream>

class Exception {
public:
    friend std::ostream &operator<<(std::ostream &os, const Exception &ex);
    virtual ~Exception() = default;

protected:
    virtual void print(std::ostream &o) const = 0;
};

inline std::ostream &operator<<(std::ostream &os, const Exception &ex) {
    ex.print(os);
    return os;
}

template <typename Key>
class ElementNotFoundException: public Exception {
public:
    explicit ElementNotFoundException(Key key) : key(key) {}

protected:
    void print(std::ostream &o) const override {
        o << "ElementNotFoundException {Key: " << key << "}";
    }

private:
    Key key;
};

template <typename Key, typename Value>
class ElementAlreadyExistsException: public Exception {
public:
    ElementAlreadyExistsException(Key key, const Value &element) : key(key), value(element) {}

protected:
    void print(std::ostream &o) const override {
        QByteArray outBytes;
        QTextStream outStream(&outBytes);
        outStream << "ElementAlreadyExistsException {Key: " << key << ", Value:" << value << "}";
        o << QString(outBytes).toStdString();
    }

private:
    Key key;
    Value value;
};
