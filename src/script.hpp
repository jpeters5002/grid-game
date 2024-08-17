#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include "spacial.hpp"
#include <variant>

struct VoidStruct {};

namespace script
{
enum class Command
{
    Nop,
    Move,
    COUNT,
};
constexpr const char *str_from_command(Command value)
{
    switch (value)
    {
        case Command::Nop:
            return "nop";
        case Command::Move:
            return "move";
        case Command::COUNT:
            break;
    }
    assert(!"unreachable");
    return "[INVALID ENUM VALUE]";
}

namespace commandinfos
{
class MoveInfo
{
public:
    MoveInfo() : movement(Movement(AngleType::Wind8, Wind8MovementInfo(Wind8::R, DrawnMovementStyle::SmoothDrawnSuddenLogic), 1.0)) {}
    Movement movement;
};

typedef std::variant<VoidStruct, commandinfos::MoveInfo> CommandInfoVariant;
class CommandInfo
{
public:
    CommandInfo() : civ(CommandInfoVariant()), cmd(script::Command::Nop) {}
    CommandInfo(const CommandInfoVariant &civ, script::Command cmd) : civ(civ), cmd(cmd) {}
    CommandInfoVariant civ;
    script::Command cmd;
};
} // namespace commandinfos
} // namespace script

#endif // SCRIPT_HPP

