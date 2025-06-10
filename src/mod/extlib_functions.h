#include "modding.h"
#include "global.h"

RECOMP_IMPORT(".", void EZTR_DumpToDiskNative_Init());
RECOMP_IMPORT(".", int EZTR_DumpToDiskNative_AddMessage(u16 messageId, int length, char* buf));