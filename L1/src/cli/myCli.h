#pragma once
#include <string>

void box(const std::string& string, std::ostream& os,
         const std::string& boxColor = "\033[0m",
         const std::string& textColor = "\033[0m");

std::string offset(int offset);