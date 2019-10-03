#include "shape.h"
#include "hashMap.h"
#include "pentagram.h"

#include <iostream>

int main(int argc, char *argv[]) {
    std::cout.precision(3);
    auto p = pavel::Pentagram();
    auto map = pavel::HashMap<int, pavel::Shape&>();
    map.create(1, p);
}