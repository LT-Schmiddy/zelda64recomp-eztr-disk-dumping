#pragma once
#include <iostream>

class TextEntry {
public:
    TextEntry(uint16_t p_message_id, int p_len, uint8_t* rdram, int32_t starting_address);
    ~TextEntry();

    uint16_t message_id = 0;
    uint32_t len = 0;
    char* message_buffer = NULL;

    uint8_t getTextBoxType();
    uint8_t getTextBoxYPos();
    uint8_t getDisplayIcon();
    uint16_t getNextMessageId();
    uint16_t getFirstItemRupees();
    uint16_t getSecondItemRupees();

    std::string getMessageIdString();
    std::string getTextBoxTypeString();
    std::string getTextBoxYPosString();
    std::string getDisplayIconString();
    std::string getNextMessageIdString();
    std::string getFirstItemRupeesString();
    std::string getSecondItemRupeesString();
    std::string getContentString(bool use_cc_macros, bool pipe_escaped_bytes);
    std::string constructApiCall(bool use_cc_macros, bool pipe_escaped_bytes, int indent_level = 1, std::string indent_string = "    ");
};