#include <iostream>
#include <unordered_map>
#include <memory>
#include <string.h>
#include "lib_recomp.hpp"
#include "TextEntry.hpp"

extern "C" {
    DLLEXPORT uint32_t recomp_api_version = 1;
}

std::unordered_map<uint16_t, std::shared_ptr<TextEntry>> text_entries;

RECOMP_DLL_FUNC(EZTR_DumpToDiskNative_Init) {

}

RECOMP_DLL_FUNC(EZTR_DumpToDiskNative_AddMessage) {
    uint16_t messageId = RECOMP_ARG(uint16_t, 0);
    printf("Trying to copy Message ID %04X\n", messageId);

    if (text_entries.contains(messageId)) {
        printf("Message ID %04X already captured.\n", messageId);
        RECOMP_RETURN(int, 0);
    }
    
    int len = RECOMP_ARG(int, 1);
    PTR(char) starting_address = RECOMP_ARG(PTR(char), 2);

    std::shared_ptr<TextEntry> entry = std::make_shared<TextEntry>(messageId, len, rdram, starting_address);

    text_entries.insert({messageId, entry});
    printf("Message ID %04X copied to map.\n", messageId);
}