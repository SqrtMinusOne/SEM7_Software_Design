#include "shape.h"
#include "hashMap.h"
#include "pentagram.h"
#include "atanSegment.h"
#include "text.h"
#include "pentagramText.h"
#include "point.h"
#include "colors.h"
#include "myCli.h"
#include "exception.h"

#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
    box("          Korytov Pavel, 6304. LR 1, Part 3           ", std::cout, RED);
    std::cout.precision(3);
    auto map = pavel::HashMap<int, std::shared_ptr<pavel::Shape>>();
    std::cout << GREEN << "Создание элементов" << RESET << std::endl;
    map.create(1, std::make_shared<pavel::Pentagram>(pavel::Pentagram()));
    map.create(2, std::make_shared<pavel::Text>(pavel::Text("Hello", pavel::Point {0, 0}, pavel::Point{10, 10})));
    map.create(3, std::make_shared<pavel::PentagramText>(pavel::PentagramText("Goodbye")));

    std::cout << GREEN << "Получение элементов" << RESET << std::endl;
    for (auto it = map.begin(); !it.end(); ++it) {
        std::cout << it.key() << ": " << *it.value() << std::endl;
    }

    std::cout << GREEN << "Обновление элементов" << RESET << std::endl;
    map.update(3, std::make_shared<pavel::AtanSegment>(pavel::AtanSegment(pavel::Point{1, 1}, pavel::Point{10, 10}, 5)));
    for (auto it = map.begin(); !it.end(); ++it) {
        std::cout << it.key() << ": " << *it.value() << std::endl;
    }

    std::cout << GREEN << "Удаление элементов" << RESET << std::endl;
    map.remove(2);

    for (auto it = map.begin(); !it.end(); ++it) {
        std::cout << it.key() << ": " << *it.value() << std::endl;
    }

    std::cout << GREEN << "Исключения" << RESET << std::endl;
    try{
        map.remove(2);
    } catch (pavel::Exception& ex) {
        std::cout << "Поймано исключение: " << ex << std::endl;
    }
    try{
        auto a = map.at(2);
    } catch (pavel::Exception& ex) {
        std::cout << "Поймано исключение: " << ex << std::endl;
    }
    try{
        map.create(3, std::make_shared<pavel::Pentagram>(pavel::Pentagram()));
    } catch (pavel::Exception& ex) {
        std::cout << "Поймано исключение: " << ex << std::endl;
    }

}