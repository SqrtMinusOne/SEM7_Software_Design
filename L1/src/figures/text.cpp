#include <tuple>
#include <utility>
#include <algorithm>
#include "text.h"

const std::string &Text::getString() const {
    return string;
}

void Text::setString(const std::string &newString) {
    string = newString;
}

std::vector<Point> Text::getRect() {
    auto [p1, p3] = borders;
    auto points = std::vector(
            {getScaled(p1),
             (getScaled(Point{p1.getX(), p3.getY()})),
             getScaled(p3),
             getScaled(Point{p1.getX(), p3.getY()})
            });
    return points;
}

std::pair<Point, Point> Text::getBorders() {
    auto points = getRect();
    auto xS = std::vector<double>();
    auto yS = std::vector<double>();
    for (auto & point: points) {
        xS.push_back(point.getX());
        yS.push_back(point.getY());
    }
    const auto [minX, maxX] = std::minmax_element(xS.begin(), xS.end());
    const auto [minY, maxY] = std::minmax_element(yS.begin(), yS.end());
    return std::make_pair(
            Point {*minX, *minY},
            Point {*maxX, *maxY}
    );
}

std::vector<Point> Text::getPath() {
    return getRect();
}

void Text::move(Point delta) {
    Shape::move(delta);
    borders.first += delta;
    borders.second += delta;
}

void Text::print(std::ostream &o) const {

    o << " Text: {string: " << string<< "; box:"
      << borders.second << " " << borders.first << "}";
}

Text::Text(std::string string, Point bottomLeft, Point topRight)
        :string(std::move(string)), borders(std::make_pair(topRight, bottomLeft)) {
    center = (topRight + bottomLeft) / 2;
}
