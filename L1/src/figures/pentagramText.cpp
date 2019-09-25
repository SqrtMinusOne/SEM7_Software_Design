#include "pentagramText.h"

#include <utility>

namespace pavel {
    void PentagramText::print(std::ostream &o) const {
        o << "PentagramText {center: " << Pentagram::center << "; size: " << size << "; string: " << getString() << "}";
    }

    std::pair<Point, Point> PentagramText::getBorders() {
        return Pentagram::getBorders();
    }

    std::vector<Point> PentagramText::getPath() {
        auto pentagramPath = Pentagram::getPath();
        auto textPath = Text::getPath();
        pentagramPath.insert(pentagramPath.end(), textPath.begin(), textPath.end());
        return pentagramPath;
    }

    void PentagramText::move(Point delta) {
        Text::move(delta);
    }

    PentagramText::PentagramText(std::string string, Point center, double size)
    : Pentagram(center, size), Text(std::move(string), center + (size / 2), center - (size / 2))
    {}
}
