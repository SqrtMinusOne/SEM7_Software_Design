#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <map>

#include "myCli.h"
#include "colors.h"

using std::cout, std::endl;

int main(int argc, char *argv[])
{
    box("          Korytov Pavel, 6304. LR 1, Part 2           ", std::cout, RED);
    std::initializer_list<int> init = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };
    box("vector, list, deque", std::cout, YELLOW);
    auto vector = std::vector<int>(init);
    auto list = std::list<int>(init);
    auto deque = std::deque<int>(init);

    cout << GREEN << "Vector и deque поддерживают random access, list - нет:" << RESET << endl;
    cout << "vector[15] = " << vector[4] << endl;
    cout << "deque[15] = " << deque[4] << endl;

    cout << GREEN << "Все три контейнера позволяют эффективно получить доступ к первому или последнему элементу:" << RESET << endl;
    cout << "vector.front(): " << vector.front() << "; vector.back(): " << vector.back() << endl;
    cout << "list.front(): " << list.front() << "; list.back(): " << list.back() << endl;
    cout << "deque.front(): " << deque.front() << "; deque.back(): " << deque.back() << endl;

    cout << GREEN << "Модификация содержимого. Все три контейнера обладают идентичными операциями..." << RESET << endl;
    deque.push_back(15);
    deque.push_front(25);
    list.push_back(15);
    list.push_front(25);
    cout << GREEN << "Но vector не позволяет добавлять элементы в начало" << RESET << endl;
    vector.push_back(15);

    cout << GREEN << "Итерация" << RESET << endl;
    for (auto & it : deque) {
        cout << it << " ";
    }
    cout << endl;

    for (auto & it : list) {
        cout << it << " ";
    }
    cout << endl;

    for (auto & it : vector) {
        cout << it << " ";
    }
    cout << endl;

    box("map", std::cout, YELLOW);
    cout << GREEN << "Создание map" << RESET << endl;
    auto map = std::map<int, int> {{1, 2}, {3, 4}, {5, 6}};
    for (auto & it : map) {
        std::cout << it.first << " " << it.second << std::endl;
    }

    cout << GREEN << "Изменение map" << RESET << endl;
    map[1] = 20;
    map[0] = 25;

    for (auto & it : map) {
        std::cout << it.first << " " << it.second << std::endl;
    }
}
