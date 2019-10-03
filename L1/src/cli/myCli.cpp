#include "myCli.h"
#include "colors.h"
#include <iostream>
#include <sstream>

#define OFFSET "    "

void box(const std::string& string, std::ostream& os,
         const std::string& boxColor,
         const std::string& textColor) {
    os << boxColor << "┌";
    for (int i = 0; i < string.length(); i++) {
        os << "─";
    }
    os << "┐" << std::endl;
    os << "│" << textColor << string << boxColor << "│" << std::endl;
    os << "└";
    for (int i = 0; i < string.length(); i++) {
        os << "─";
    }
    os << "┘" << std::endl << RESET;
}

std::string offset(int offset) {
    std::string str;
    for (int i = 0; i < offset; i ++) {
        str += OFFSET;
    }
    return str;
}
