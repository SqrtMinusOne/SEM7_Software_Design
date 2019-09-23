#include <tuple>
#include <utility>
#include "text.h"

namespace pavel {

    const std::string &Text::getString() const {
        return string;
    }

    void Text::setString(const std::string &newString) {
        string = newString;
    }

    std::pair<Point, Point> Text::getBorders() {
        auto [p1, p2] = borders;
        return alignRect(getScaled(p1), getScaled(p2));
    }

    std::vector<Point> Text::getPath() {
        auto [p1, p2] = getBorders();
        return std::vector<Point> {
            Point {p1.getX(), p1.getY()},
            Point {p1.getX(), p2.getY()},
            Point {p2.getX(), p2.getY()},
            Point {p2.getX(), p1.getY()}
        };
    }

    void Text::move(Point delta) {
        Shape::move(delta);
        borders.first += delta;
        borders.second += delta;
    }

    void Text::print(std::ostream &o) const {
       o << " Text: {string: " << string <<  "; center: " << getCenter() << "}";
    }

    Text::Text(std::string string, Point topRight, Point bottomLeft)
        :string(std::move(string)), borders(std::make_pair(topRight, bottomLeft)) {
        center = (topRight + bottomLeft) / 2;
    }
}