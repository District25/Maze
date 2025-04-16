#ifndef COORD_H
#define COORD_H

#include <tuple>  // Pour std::tie


struct Coord {
    int x;
    int y;

    // Constructeur pratique
    Coord(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
    bool operator==(const Coord& other) const {
        return x == other.x && y == other.y;
    }
    bool operator<(const Coord& other) const {
        return std::tie(y, x) < std::tie(other.y, other.x);
    }
};

#endif // COORD_H
