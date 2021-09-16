#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Bootloader will store a value within its' code that is used to determine if the bootloader is valid for the operating system. A similar
// function should be implemented in the bootloader code and removed from this file. Best to store it in an EFI header file under obfuscation.
int _BOOTLOADER() {
    int _BOOTLOADER_RETURN_VALUE;

    _BOOTLOADER_RETURN_VALUE = 0xB9BAD4;

    return _BOOTLOADER_RETURN_VALUE;
}

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
            printf("Failed to locate Magic Value in memory\n");
            return 0;
        } else {
            if (_DSYFX_CHALLENGE_INPUT_VALUE == NULL) {
                printf("Failed to locate Challenge Value in memory\n");
                return 0;
            } else {
                if (_DSYFX_BOOTLOADER_VALUE == _DSYFX_CHALLENGE_INPUT_VALUE) {
                    _DSYFX_VALID_BOOTLOADER = true;
                    printf("DSYFX Has Arrived\n");
                    return _DSYFX_VALID_BOOTLOADER;
            } else {
                _DSYFX_VALID_BOOTLOADER = false;
                printf("DSYFX Has Failed\n");
                printf("Invalid Magic Value in memory!\n");
                printf("Expected: %d\n", _DSYFX_BOOTLOADER_VALUE); // Debug only. Remove in final implementation.
                printf("Received: %d\n", _DSYFX_CHALLENGE_INPUT_VALUE);
                return _DSYFX_VALID_BOOTLOADER;
            }
        }
    }
}

}

int main() {

    int (VERIFIER)(_BOOTLOADER());
    //int VERIFIER = 0xB9BAD5;

    _DSYFX(VERIFIER);

    return 0;

}
