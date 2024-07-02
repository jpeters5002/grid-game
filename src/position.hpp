#ifndef POSITION_HPP
#define POSITION_HPP

enum class DrawPositionType {
    TopLeft,
    Center,
};

class DrawPosition {
public:
    DrawPosition() = delete;
    DrawPosition(int x, int y, DrawPositionType type = DrawPositionType::TopLeft) : x(x), y(y), type(type) {}
    int x;
    int y;
    DrawPositionType type;
};

class GridCellIndex {
public:
    GridCellIndex() = delete;
    GridCellIndex(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

class GridContinuousPosition {
public:
    GridContinuousPosition() = delete;
    GridContinuousPosition(double x, double y) : x(x), y(y) {}
    double x;
    double y;
};

#endif // POSITION_HPP

