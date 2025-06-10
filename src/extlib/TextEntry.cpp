#include "TextEntry.hpp"
#include "lib_recomp.hpp"

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