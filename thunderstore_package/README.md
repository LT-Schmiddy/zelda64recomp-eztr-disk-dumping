# EZTR Dump To Disk Extention

This is an extention for EZTR that dumps messages to a C file, rather than simply to console.

The output is saved to your mods folder. Use the config menu to set the file name and formatting options.
Note that this extension DOES NOT match EZTR's formatting configuration. Use the ones in this mod instead.

The following is a sample output file from this extension:

```C
#include "modding.h"
#include "global.h"
#include "eztr_api.h"

EZTR_ON_INIT void init_text() {
    EZTR_Basic_ReplaceText(
        0x0104,
        EZTR_INVISIBLE_TEXT_BOX_V,
        0,
        EZTR_ICON_NO_ICON,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        false,
        "South Clock Town" EZTR_CC_END "",
        NULL
    );

    EZTR_Basic_ReplaceText(
        0x061A,
        EZTR_STANDARD_TEXT_BOX_I,
        0,
        EZTR_ICON_NO_ICON,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        false,
        "" EZTR_CC_SFX "iiThis poster's an eyesore! What a" EZTR_CC_NEWLINE "sorry collection of cowards!!" EZTR_CC_NEWLINE "Bluh-yek! Foo!" EZTR_CC_EVENT2 "" EZTR_CC_END "",
        NULL
    );

    EZTR_Basic_ReplaceText(
        0x061B,
        EZTR_STANDARD_TEXT_BOX_I,
        0,
        EZTR_ICON_NO_ICON,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        false,
        "Hey, apprentice! Don't just stand" EZTR_CC_NEWLINE "around lookin' at the sky all" EZTR_CC_NEWLINE "day!" EZTR_CC_EVENT2 "" EZTR_CC_END "",
        NULL
    );

    EZTR_Basic_ReplaceText(
        0x1C18,
        EZTR_STANDARD_TEXT_BOX_II,
        0,
        EZTR_ICON_NO_ICON,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        false,
        "Absolutely Guaranteed!" EZTR_CC_NEWLINE "We shall guard your assets!" EZTR_CC_NEWLINE "        Clock Town Bank" EZTR_CC_END "",
        NULL
    );
}
```
