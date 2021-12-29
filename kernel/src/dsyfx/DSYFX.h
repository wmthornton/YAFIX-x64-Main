#pragma once

#include "../Basic_Renderer.h"
#include "../../../gnu-efi/bootloader/bootloader.h"
#include "../Panic.h"

bool _DSYFX_VALID_BOOTLOADER = false; // This is set to true when the bootloader is valid, meaning the kernel can be booted.

bool _DSYFX_MISSING_MV_BOOTLOADER = false; // This is set to true if the Magic Value is missing from memory. If this occurs, something is very wrong.
bool _DSYFX_MISSING_CI_VALUE = false; // This is set to true if the Challenge Value is missing from memory. If this occurs, something is very wrong.

int _DSYFX(int _DSYFX_CHALLENGE_INPUT) {

    int (BOOTLOADER)(_BOOTLOADER());

    int _DSYFX_BOOTLOADER_VALUE = BOOTLOADER;
    int _DSYFX_CHALLENGE_INPUT_VALUE = _DSYFX_CHALLENGE_INPUT;

    if (&_DSYFX_CHALLENGE_INPUT_VALUE != &_DSYFX_BOOTLOADER_VALUE) {

        if (_DSYFX_BOOTLOADER_VALUE == NULL) {
            _DSYFX_MISSING_MV_BOOTLOADER = true;
            return _DSYFX_MISSING_MV_BOOTLOADER;
        } else {
            if (_DSYFX_CHALLENGE_INPUT_VALUE == NULL) {
                _DSYFX_MISSING_CI_VALUE = true;
                return _DSYFX_MISSING_CI_VALUE;
            } else {
                if (_DSYFX_BOOTLOADER_VALUE == _DSYFX_CHALLENGE_INPUT_VALUE) {
                    _DSYFX_VALID_BOOTLOADER = true;
                    GlobalRenderer->Print("DSYFX Has Arrived");
                    return _DSYFX_VALID_BOOTLOADER;
            } else {
                _DSYFX_VALID_BOOTLOADER = false;
                return _DSYFX_VALID_BOOTLOADER;
            }
        }
    }
}
}

void _DSYFX_Fault_Detected() {
    if (_DSYFX_VALID_BOOTLOADER == false) {
        DSYFX_Fault("DSYFX Verification Failed. Bootloader Is Not Valid.");
        while(true);
    } else if (_DSYFX_MISSING_MV_BOOTLOADER == true) {
        DSYFX_Fault("Magic Value Not Found In Memory. This is a fatal error and a memory diagnostic is recommended.");
        while(true);
    } else if (_DSYFX_MISSING_CI_VALUE == true) {
        DSYFX_Fault("Challenge Value Not Found In Memory. This is a fatal error and a memory diagnostic is recommended.");
        while(true);
    }
}








