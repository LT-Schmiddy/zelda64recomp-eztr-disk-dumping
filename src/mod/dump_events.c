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
    recomp_printf("Buffer Handled\n");
}