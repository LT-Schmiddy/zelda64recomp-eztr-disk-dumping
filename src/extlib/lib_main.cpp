#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <filesystem>
#include <string.h>
#include "lib_recomp.hpp"
#include "TextEntry.hpp"

namespace fs = std::filesystem;

extern "C" {
    DLLEXPORT uint32_t recomp_api_version = 1;
}

std::map<uint16_t, std::shared_ptr<TextEntry>> text_entries;

RECOMP_DLL_FUNC(EZTR_DumpToDiskNative_Init) {}

RECOMP_DLL_FUNC(EZTR_DumpToDiskNative_AddMessage) {
    uint16_t messageId = RECOMP_ARG(uint16_t, 0);

    if (text_entries.contains(messageId)) {
        printf("EZTR_DumpToDiskNative: Message ID %04X already copied.\n", messageId);
        return;
    }
    
    int len = RECOMP_ARG(int, 1);
    PTR(char) starting_address = RECOMP_ARG(PTR(char), 2);

    std::shared_ptr<TextEntry> entry = std::make_shared<TextEntry>(messageId, len, rdram, starting_address);

    text_entries.insert({messageId, entry});
    printf("EZTR_DumpToDiskNative: Message ID %04X copied to map.\n", messageId);
}

RECOMP_DLL_FUNC(EZTR_DumpToDiskNative_BuildOutputFile) {
    std::u8string outdir = RECOMP_ARG_U8STR(0);
    std::u8string outname = RECOMP_ARG_U8STR(1);
    int use_cc_macros = RECOMP_ARG(int, 2);
    int pipe_escaped_bytes = RECOMP_ARG(int, 3);

    fs::path outpath(outdir);
    outpath.append(outname);

    std::ofstream outfile(outpath);
    if (outfile.is_open()) {
        outfile << "#include \"modding.h\"\n";
        outfile << "#include \"global.h\"\n";
        outfile << "#include \"eztr_api.h\"\n\n";
        outfile << "EZTR_ON_INIT void init_text() {\n";

        for (auto iter : text_entries) {
            outfile << iter.second->constructApiCall(use_cc_macros, pipe_escaped_bytes) << "\n";
        }
        outfile << "}\n";
    }
    outfile.close();
    printf("EZTR_DumpToDiskNative: Saved output to %s\n", outpath.string().c_str());
}