#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>

#include "myCli.h"
#include "colors.h"

using std::cout, std::endl;

int main(int argc, char *argv[])
{
    box("          Korytov Pavel, 6304. LR 1, Part 2           ", std::cout, RED);
    std::initializer_list<std::string> strings = {
            "Du", "kan", "om",  "du", "vil",
            "Ingen", "kan", "ta", "ditt", "valg",
            "Bare", "plante", "tvi",
            "Det", "er", "så", "mange", "veier", "å", "gå",
            "Mange", "mål", "som", "kan", "nåes", "om", "du", "våger",
            "Å", "tro", "på", "at", "du", "har", "det", "som", "skal", "til"
    };
    box("vector, list, deque", std::cout, YELLOW);
    auto vector = std::vector<std::string>(strings);
    auto list = std::list<std::string>(strings);
    auto deque = std::deque<std::string>(strings);

    cout << GREEN << "Vector и deque поддерживают random access, list - нет:" << RESET << endl;
    cout << "vector[15] = " << vector[15] << endl;
    cout << "deque[15] = " << deque[15] << endl;

    cout << GREEN << "Все три контейнера позволяют эффективно получить доступ к первому или последнему элементу:" << RESET << endl;
    cout << "vector.front(): " << vector.front() << "; vector.back(): " << vector.back() << endl;
    cout << "list.front(): " << list.front() << "; list.back(): " << list.back() << endl;
    cout << "deque.front(): " << deque.front() << "; deque.back(): " << deque.back() << endl;

}
