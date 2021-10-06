#pragma once

#include "../Basic_Renderer.h"
#include "../../../gnu-efi/bootloader/bootloader.h"

// This function will be used to set a challenge value in memory for comparison against the value stored in the bootloader. Can be used
// throughout the operating system whenver a challenge is required.
int _DSYFX_CHALLENGE_BOOTLOADER(int _BOOTLOADER_CHALLENGE_VALUE) {

    int *_DSYFX_CHALLENGE_BOOTLOADER;
    int _DSYFX_CHALLENGE_BOOTLOADER_VAL = _BOOTLOADER_CHALLENGE_VALUE;
    int _DSYFX_CHALLENGE_RETURN = 0;

    // Assign value of _DSYFX_CHALLENGE_BOOTLOADER_VAL to pointer _DSYFX_CHALENGE_BOOTLOADER
    _DSYFX_CHALLENGE_BOOTLOADER = &_DSYFX_CHALLENGE_BOOTLOADER_VAL;

    _DSYFX_CHALLENGE_RETURN = *_DSYFX_CHALLENGE_BOOTLOADER;

    return _DSYFX_CHALLENGE_RETURN;

}

int _DSYFX(int _DSYFX_CHALLENGE_INPUT) {

    int (BOOTLOADER)(_BOOTLOADER());
    int (*CHALLENGE)(int);

    int _DSYFX_BOOTLOADER_VALUE = BOOTLOADER;
    int _DSYFX_CHALLENGE_INPUT_VALUE = _DSYFX_CHALLENGE_INPUT;

    bool _DSYFX_VALID_BOOTLOADER = false;

    CHALLENGE = _DSYFX_CHALLENGE_BOOTLOADER;

    if (&_DSYFX_CHALLENGE_INPUT_VALUE != &_DSYFX_BOOTLOADER_VALUE) {

        if (_DSYFX_BOOTLOADER_VALUE == NULL) {
            _DSYFX_VALID_BOOTLOADER = false;
            GlobalRenderer->Print("Failed To Locate Magic Value In Memory");
            return _DSYFX_VALID_BOOTLOADER;
        } else {
            if (_DSYFX_CHALLENGE_INPUT_VALUE == NULL) {
                _DSYFX_VALID_BOOTLOADER = false;
                GlobalRenderer->Print("Failed To Locate Challenge Value In Memory");
                return _DSYFX_VALID_BOOTLOADER;
            } else {
                if (_DSYFX_BOOTLOADER_VALUE == _DSYFX_CHALLENGE_INPUT_VALUE) {
                    _DSYFX_VALID_BOOTLOADER = true;
                    GlobalRenderer->Print("DSYFX Has Arrived");
                    return _DSYFX_VALID_BOOTLOADER;
            } else {
                _DSYFX_VALID_BOOTLOADER = false;
                GlobalRenderer->Print("DSYFX Has Not Arrived");
                return _DSYFX_VALID_BOOTLOADER;
            }
        }
    }
}
}








