#include "script_handler.hpp"

#include "loop_limit.hpp"

#include <iostream>

#define SIZEOF_LUT(lut) (sizeof(lut) / sizeof(lut[0]))
static const char SPECIAL_CHARS[] = {
    '(',
    ')',
};
constexpr bool is_special(char c) {
    for (size_t i = 0; i < SIZEOF_LUT(SPECIAL_CHARS); i++)
        if (c == SPECIAL_CHARS[i])
            return true;
    return false;
}
static const char TOKEN_DELIMITER_CHARS[] = {
    ' ',
    '\n',
    '\t',
};
constexpr bool is_token_delimiter(char c) {
    for (size_t i = 0; i < SIZEOF_LUT(TOKEN_DELIMITER_CHARS); i++)
        if (c == TOKEN_DELIMITER_CHARS[i])
            return true;
    return false;
}
constexpr bool is_alpha(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}
constexpr bool is_numeric(char c) {
    return '0' <= c && c <= '9';
}
constexpr bool is_alphanumeric(char c) {
    return is_alpha(c) || is_numeric(c);
}

using namespace script;

ScriptHandler::ScriptHandler(const std::string &buffer) : buffer(buffer), index(0) {
    for (size_t i = 0; i < (size_t) script::Command::COUNT; i++)
        command_map.insert(std::make_pair(str_from_command((script::Command) i), (script::Command) i));
}

commandinfos::CommandInfo ScriptHandler::ParseNextCommand() {
    using namespace commandinfos;
    std::string token = NextToken();
    if (token.empty())
        return CommandInfo();
    auto cmdspec = command_map.find(token);
    if (cmdspec == command_map.end()) {
        std::cerr << "unknown command: \"" << token << "\"" << std::endl;
        return CommandInfo();
    }
    script::Command cmd = cmdspec->second;
    return ParseCommandArgs(cmd);
}

std::string ScriptHandler::NextToken() {
    std::string token {};
    char c = '\0';
    // bypass any token delimiters
    for (size_t limit = 0; limit < HARD_LOOP_LIMIT; limit++) {
        if (index >= buffer.size())
            break;
        c = buffer[index++];
        if (!is_token_delimiter(c))
            break;
    }
    if (c == '\0')
        return token; // should be empty in this case (we started at the end of the buffer)
    // create token starting with c
    token.push_back(c);
    if (is_special(c))
        return token;
    for (size_t limit = 0; limit < HARD_LOOP_LIMIT; limit++) {
        if (index >= buffer.size())
            return token;
        c = buffer[index];
        if (is_token_delimiter(c) || is_special(c))
            return token;
        token.push_back(c);
        index++;
    }
    assert(!"unreachable (infinite loop!?)");
    return token;
}

commandinfos::CommandInfo ScriptHandler::ParseCommandArgs(script::Command cmd) {
    using namespace commandinfos;
    std::string token = NextToken();
    if (token != "(") {
        std::cerr << "no '(' character after valid command: " << str_from_command(cmd) << std::endl;
        return CommandInfo();
    }
    switch (cmd)
    {
        case Command::Nop:
            return CommandInfo();
        case Command::Move: {
            MoveInfo mi {};
            token = NextToken();
            for (size_t i = 0; i < 8; i++) {
                if (token == str_from_wind8((Wind8) i)) {
                    std::get<0>(mi.movement.angle).wind8 = (Wind8) i;
                    break;
                }
            }
            token = NextToken();
            if (token != ")") {
                std::cerr << "no ')' to end move command" << std::endl;
                return CommandInfo();
            }
            return CommandInfo(mi, cmd);
        }
        case Command::COUNT:
            assert(!"unreachable");
            break;
    }
    assert(!"unreachable");
    return CommandInfo();
}
