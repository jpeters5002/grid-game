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
    GridContinuousPosition(float x, float y) : x(x), y(y) {}
    float x;
    float y;
};

#endif // POSITION_HPP

