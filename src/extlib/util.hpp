#pragma once
#include <iostream>
#include <string>
#include <sstream>

#include <string.h>
#include <ctype.h>

bool is_printable_char(char c);
std::string process_char(char character, bool use_cc_macros, bool pipe_escaped_bytes);
void process_char_append(std::ostringstream* stream, char character, bool use_cc_macros, bool pipe_escaped_bytes);

