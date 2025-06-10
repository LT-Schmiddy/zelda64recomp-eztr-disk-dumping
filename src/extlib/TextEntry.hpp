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

    std::string getTextBoxTypeString();
    std::string getTextBoxYPosString();
    std::string getDisplayIconString();
    std::string getNextMessageIdString();
    std::string getFirstItemRupeesString();
    std::string getSecondItemRupeesString();
    std::string getContentString();
};