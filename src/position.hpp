#ifndef POSITION_HPP
#define POSITION_HPP

enum class DrawPositionType {
    TopLeft,
    Center,
};

class DrawPosition {
public:
    Position() = delete;
    Position(int x, int y, DrawPositionType type = DrawPositionType::TopLeft) : x(x), y(y), type(type) {}
    int x;
    int y;
    DrawPositionType type;
};

class GridPosition {
public:
    GridPosition() = delete;
    GridPosition(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

#endif // POSITION_HPP

