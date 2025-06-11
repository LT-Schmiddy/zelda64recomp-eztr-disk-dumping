#include "modding.h"
#include "global.h"

RECOMP_IMPORT(".", void EZTR_DumpToDiskNative_Init());
RECOMP_IMPORT(".", void EZTR_DumpToDiskNative_AddMessage(u16 messageId, int length, char* buf));
RECOMP_IMPORT(".", void EZTR_DumpToDiskNative_BuildOutputFile(const char* outdir, const char* outname, int use_cc_macros, int pipe_escaped_bytes));