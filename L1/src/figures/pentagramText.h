#include "text.h"
#include "pentagram.h"

class PentagramText : virtual public Text, virtual public Pentagram {
public:
    explicit PentagramText(std::string string, Point center = Point {0, 0}, double size = 1);

    std::pair<Point, Point> getBorders() override;

    std::vector<Point> getPath() override;

    void move(Point delta) override;

protected:
    void print(std::ostream &o) const override;
};
