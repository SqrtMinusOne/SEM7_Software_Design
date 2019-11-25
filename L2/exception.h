# pragma once

#include <QTextStream>

class Exception {
public:
    friend std::ostream &operator<<(std::ostream &os, const Exception &ex);
    virtual ~Exception() = default;
    virtual QString toString() const = 0;
};

inline std::ostream &operator<<(std::ostream &os, const Exception &ex) {
    os << ex.toString().toStdString();
    return os;
}

template <typename Key>
class ElementNotFoundException: public Exception {
public:
    explicit ElementNotFoundException(Key key) : key(key) {}

protected:
    QString toString() const override {
        QString string;
        QTextStream outStream(&string);
        outStream << "ElementNotFoundException {Key: " << key << "}";
        return string;
    }

private:
    Key key;
};

template <typename Key, typename Value>
class ElementAlreadyExistsException: public Exception {
public:
    ElementAlreadyExistsException(Key key, const Value &element) : key(key), value(element) {}

protected:
    QString toString() const override {
        QString string;
        QTextStream outStream(&string);
        outStream << "ElementAlreadyExistsException {Key: " << key << ", Value:" << value << "}";
        return string;
    }

private:
    Key key;
    Value value;
};
