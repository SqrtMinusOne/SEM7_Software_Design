#pragma once

#include "shape.hpp"

namespace pavel {
    class Text : public Shape {
    public:
        explicit Text(std::string string, Point topRight, Point bottomLeft);

        std::pair<Point, Point> getBorders() override;

        std::vector<Point> getPath() override;

        [[nodiscard]] const std::string &getString() const;
        void setString(const std::string &newString);

        void move(Point delta) override;

    protected:
        void print(std::ostream &o) const override;

    private:
        std::string string;
        std::pair<Point, Point> borders;
    };
}
