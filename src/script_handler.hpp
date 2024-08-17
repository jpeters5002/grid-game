#ifndef SCRIPT_HANDLER_HPP
#define SCRIPT_HANDLER_HPP

#include "script.hpp"
#include <string>
#include <unordered_map>

namespace script
{
class ScriptHandler
{
public:
    ScriptHandler() = delete;
    ScriptHandler(const std::string &buffer);
    commandinfos::CommandInfo ParseNextCommand();
private:
    const std::string &buffer;
    size_t index;

    std::unordered_map<std::string, Command> command_map;

    std::string NextToken();
    commandinfos::CommandInfo ParseCommandArgs(script::Command cmd);
};
} // namespace script

#endif // SCRIPT_HANDLER_HPP

