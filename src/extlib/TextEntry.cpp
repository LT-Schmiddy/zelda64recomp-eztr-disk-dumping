#include <format>
#include <sstream>
#include <string.h>

#include "TextEntry.hpp"
#include "lib_recomp.hpp"
#include "name_lookup.hpp"
#include "util.hpp"

// Copied from eztr_api.h
#define EZTR_MSG_HEADER_SIZE 11
#define EZTR_MSG_BUFFER_SIZE 1280

TextEntry::TextEntry(uint16_t p_message_id, int p_len, uint8_t* rdram, int32_t starting_address) {
    message_id = p_message_id;
    len = p_len;

    // Copying buffer:
    message_buffer = new char[p_len];
    for (int32_t i = 0; i < len; i++) {
        message_buffer[i] = MEM_B(starting_address, i);
    }
}

TextEntry::~TextEntry() {
    if (message_buffer != NULL) {
        delete message_buffer;
    }
}

uint8_t TextEntry::getTextBoxType(){
    // Copying to avoid any bizzare typecasting issues.
    uint8_t retVal;
    memcpy(&retVal, &message_buffer[0], sizeof(uint8_t));
    return retVal;
}

uint8_t TextEntry::getTextBoxYPos(){
    uint8_t retVal;
    memcpy(&retVal, &message_buffer[1], sizeof(uint8_t));
    return retVal;
}

uint8_t TextEntry::getDisplayIcon(){
    uint8_t retVal;
    memcpy(&retVal, &message_buffer[2], sizeof(uint8_t));
    return retVal;
}

uint16_t TextEntry::getNextMessageId(){
    uint16_t retVal;
    memcpy(&retVal, &message_buffer[3], sizeof(uint16_t));
    return retVal;
}

uint16_t TextEntry::getFirstItemRupees(){
    uint16_t retVal;
    memcpy(&retVal, &message_buffer[5], sizeof(uint16_t));
    return retVal;
}

uint16_t TextEntry::getSecondItemRupees(){
    uint16_t retVal;
    memcpy(&retVal, &message_buffer[7], sizeof(uint16_t));
    return retVal;
}

// String versions
std::string TextEntry::getMessageIdString() {
    char retVal[10];
    snprintf(retVal, 10, "0x%04X", message_id);
    return std::string(retVal);
}

std::string TextEntry::getTextBoxTypeString() {
    return std::string(eztr_textbox_names[getTextBoxType()]);
}

std::string TextEntry::getTextBoxYPosString() {
    char retVal[10];
    snprintf(retVal, 10, "%i", getTextBoxYPos());
    return std::string(retVal);
}

std::string TextEntry::getDisplayIconString() {
    return std::string(eztr_icon_names[getDisplayIcon()]);
}

std::string TextEntry::getNextMessageIdString() {
    uint16_t val = getNextMessageId();

    if (val == 0xFFFF) {
        return std::string(eztr_no_value_string);
    } else {
        char retVal[10];
        snprintf(retVal, 10, "0x%04X", getTextBoxYPos());
        return std::string(retVal);
    }
}

std::string TextEntry::getFirstItemRupeesString() {
    uint16_t val = getFirstItemRupees();

    if (val == 0xFFFF) {
        return std::string(eztr_no_value_string);
    } else {
        char retVal[10];
        snprintf(retVal, 10, "0x%04X", getTextBoxYPos());
        return std::string(retVal);
    }
}

std::string TextEntry::getSecondItemRupeesString() {
    uint16_t val = getSecondItemRupees();

    if (val == 0xFFFF) {
        return std::string(eztr_no_value_string);
    } else {
        char retVal[10];
        snprintf(retVal, 10, "0x%04X", getTextBoxYPos());
        return std::string(retVal);
    }
}

std::string TextEntry::getContentString(bool use_cc_macros, bool pipe_escaped_bytes) {
    std::ostringstream ss;
    ss.put('\"');
    for (int i = EZTR_MSG_HEADER_SIZE; i < len; i++) {
        process_char_append(&ss, message_buffer[i], use_cc_macros, pipe_escaped_bytes);
        if (message_buffer[i] == '\xBF') {
            break;
        }
    }
    ss.put('\"');
    return ss.str();
}

std::string TextEntry::constructApiCall(bool use_cc_macros, bool pipe_escaped_bytes, int indent_level, std::string indent_string) {
    std::ostringstream indent_prefix_s;

    for (int i = 0; i < indent_level; i++) {
        indent_prefix_s.write(indent_string.c_str(), indent_string.size());
    }

    std::string indent_prefix = indent_prefix_s.str();

    // I should really come up with a more efficient version of this... later.
    return 
        std::format("{}EZTR_Basic_ReplaceText(\n", indent_prefix)
        + std::format("{}{}{},\n", indent_prefix, indent_string, getMessageIdString())
        + std::format("{}{}{},\n", indent_prefix, indent_string, getTextBoxTypeString())
        + std::format("{}{}{},\n", indent_prefix, indent_string, getTextBoxYPosString())
        + std::format("{}{}{},\n", indent_prefix, indent_string, getDisplayIconString())
        + std::format("{}{}{},\n", indent_prefix, indent_string, getNextMessageIdString())
        + std::format("{}{}{},\n", indent_prefix, indent_string, getFirstItemRupeesString())
        + std::format("{}{}{},\n", indent_prefix, indent_string, getSecondItemRupeesString())
        + std::format("{}{}{},\n", indent_prefix, indent_string, pipe_escaped_bytes)
        + std::format("{}{}{},\n", indent_prefix, indent_string, getContentString(use_cc_macros, pipe_escaped_bytes))
        + std::format("{}{}NULL\n", indent_prefix, indent_string)
        + std::format("{});\n", indent_prefix)
    ;
}