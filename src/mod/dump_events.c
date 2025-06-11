#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "eztr_api.h"

#include "extlib_functions.h"

// Patches a function in the base game that's used to check if the player should quickspin.
RECOMP_CALLBACK("*", recomp_on_init) void init_dump_file() {
    EZTR_DumpToDiskNative_Init();
}

EZTR_ON_DUMP_BUFFER(sendBufferToNative) {
    EZTR_DumpToDiskNative_AddMessage(textId, len, buf->raw.schar);

    unsigned char* outdir = recomp_get_mod_folder_path();
    char* outname = recomp_get_config_string("output_file_name");
    EZTR_DumpToDiskNative_BuildOutputFile((const char*)outdir, (const char*)outname, recomp_get_config_u32("text_dumping_cc_macros"), recomp_get_config_u32("text_dumping_byte_format"));
    recomp_free(outdir);
    recomp_free(outname);
}