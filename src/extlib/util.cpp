#include "util.hpp"
#include "name_lookup.hpp"
static char const _hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

bool is_printable_char(char c) {
    return ((uint8_t)c) > 31 && ((uint8_t)c) < 127;
}


std::string process_char(char character, bool use_cc_macros, bool pipe_escaped_bytes) {
    char buf[20];
    if (is_printable_char(character)) {
        snprintf(buf, 20, "%c", character);
    } else {
        char buf[20];
        if (use_cc_macros && msg_control_code_names[(uint8_t)character] != NULL) {
            snprintf(buf, 20, "\" %s \"", msg_control_code_names[(uint8_t)character]);
        } else if (pipe_escaped_bytes) {
            snprintf(buf, 20, "|%02X", character);
        } else {
            snprintf(buf, 20, "\" \"\\x%02X\" \"", character);
        }
    }
    return std::string(buf);
}