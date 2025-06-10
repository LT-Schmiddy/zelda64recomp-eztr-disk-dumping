#include <format>
#include <string.h>

#include "TextEntry.hpp"
#include "lib_recomp.hpp"
#include "name_lookup.hpp"

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