# EZTR Dump To Disk Extention

This is an extention for [EZTR](https://thunderstore.io/c/zelda-64-recompiled/p/LT_Schmiddy/EZ_Text_Replacer_API/) that dumps messages to a ready-to-compile C file, rather than simply to console.

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

## Writing mods

See [this document](https://hackmd.io/fMDiGEJ9TBSjomuZZOgzNg) for an explanation of the modding framework, including how to write function patches and perform interop between different mods.

## Tools

This template has somewhat different requirements from the default mod template. In order to run it, you'll need the following:

* `make`
* `cmake`
* `ninja`
* `python` (or `python3` on POSIX systems).
* `zig`

On Linux and MacOS, you'll need to also ensure that you have the `zip` utility installed.

All of these can (and should) be installed via using [chocolatey](https://chocolatey.org/) on Windows, Homebrew on MacOS, or your distro's package manager on Linux.

**You do NOT need the `RecompModTool` tool, as the build script will compile all of the N64Recomp tools for you.**

You'll also need a `gcc` compatible compiler and linker with MIPS support. `clang` and `ld.lld` (part of the llvm toolset) are recommended.

* On Windows, using [chocolatey](https://chocolatey.org/) to install both is recommended. The packages are `llvm` and `make` respectively.
  * The LLVM 19.1.0 [llvm-project](https://github.com/llvm/llvm-project) release binary, which is also what chocolatey provides, does not support MIPS correctly. The solution is to install 18.1.8 instead, which can be done in chocolatey by specifying `--version 18.1.8` or by downloading the 18.1.8 release directly.
* On Linux, these can both be installed using your distro's package manager.
* On MacOS, these can both be installed using Homebrew. Apple clang won't work, as you need a mips target for building the mod code.

Alternatively, if you don't want to downgrade your clang version (or want a later version than what's provided for your system), I maintain [MIPS-only builds of the latest llvm utilities](https://github.com/LT-Schmiddy/n64recomp-clang/releases/latest). They're what I use. I recommend the `N64RecompEssentials` packages, as they only have the tools that are useful for working with recomp mods.

## Building

Run `git submodule update --init --recursive` to make sure you've clones all submodules. Then, run `make` (with an optional job count) to build everything.

Alternatively, you can also use special target invokations to only build specific things, such as the mod `.nrm` file or the extlib for a specific platform.
See the Makefile for all valid targets.

This repo is set up for building an extlib by default. If your mod isn't meant to have an extlib, simply remove the `extlib_compilation` section from your
`mod.toml`, and the build scripts will disable all extlib handling when building the `all` target.

On your first run, a file called `user_build_config.json` will be created at the root of the repo. Here you can set the command/path for the compiler and linker
you want to use for your mod code. If you want to use my MIPS-only clang builds (or any compiler not on the system path), this is an easy way to set them up.
You can also set which CMake presets you want to use for building your external library.

## Extlib Compilation, Cross-Compilation, and CMake Presets

This template is set up to automatically build and cross-compile your extlib code (via CMake and Zig) alongside your mod code when you invoke `make`.
CMake presets are used to handle any configuration differences between target platforms ([More info about CMake presets can be found
here](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html)). The default presets to use for each can be set in the `extlib_compiling`
section of your `mod.toml`. These are copied into `user_build_config.json` when the file is created. If you want to use a different preset for
a platform when compiling on your local system, without changing the default, you can change the preset in `user_build_config.json`.

More information about extlib compiling can be found in the `mod.toml` file.

## Testing

This template includes handling of a dedicated testing environment for you mod in the form of the `./runtime` folder. First, create `./runtime` in your
mod's root directory and copy in recomp's `assets` directory into it (You can also copy anyu config files, saves, and other mods you want to test against). After a build, your mod's `.nrm` file (and extlib file, if one is being built) will be copied to a folder called `./runtime/mods`, and a file called `./runtime/portable.txt` will be created. Then, if you use `runtime` and as your CWD, everything's ready to go for immediate testing as soon as your build finishes.

## Updating the Majora's Mask Decompilation Submodule

Mods can also be made with newer versions of the Majora's Mask decompilation instead of the commit targeted by this repo's submodule.
To update the commit of the decompilation that you're targeting, follow these steps:

* Build the [N64Recomp](https://github.com/N64Recomp/N64Recomp) repo and copy the N64Recomp executable to the root of this repository.
* Build the version of the Majora's Mask decompilation that you want to update to and copy the resulting .elf file to the root of this repository.
* Update the `mm-decomp` submodule in your clone of this repo to point to the commit you built in the previous step.
* Run `N64Recomp generate_symbols.toml --dump-context`
* Rename `dump.toml` and `data_dump.toml` to `mm.us.rev1.syms.toml` and `mm.us.rev1.datasyms.toml` respectively.
  * Place both files in the `Zelda64RecompSyms` folder.
* Try building.
  * If it succeeds, you're done.
  * If it fails due to a missing header, create an empty header file in the `include/dummy_headers` folder, with the same path.
    * For example, if it complains that `assets/objects/object_cow/object_cow.h` is missing, create an empty `include/dummy_headers/objects/object_cow.h` file.
  * If RecompModTool fails due to a function "being marked as a patch but not existing in the original ROM", it's likely that function you're patching was renamed in the Majora's Mask decompilation.
    * Find the relevant function in the map file for the old decomp commit, then go to that address in the new map file, and update the reference to this function in your code with the new name.
