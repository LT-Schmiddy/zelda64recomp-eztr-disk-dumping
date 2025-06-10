#pragma once
#include <iostream>
#include <string>

#include <string.h>
#include <ctype.h>

bool is_printable_char(char c);
std::string process_char(char character, bool use_cc_macros, bool pipe_escaped_bytes) ;

