#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Bootloader will store a value within its' code that is used to determine if the bootloader is valid for the operating system. A similar
// function should be implemented in the bootloader code and removed from this file. Best to store it in an EFI header file under obfuscation.
int _BOOTLOADER() {
    int _BOOTLOADER_RETURN_VALUE;

    _BOOTLOADER_RETURN_VALUE = 20;

    return _BOOTLOADER_RETURN_VALUE;
}

// This function is used to read the value stored in the bootloader as a pointer in memory and return it for use.
int _DSYFX_READ_BOOTLOADER(int _BOOTLOADER_RETURN_VALUE) {

    // Reference _BOOTLOADER function at runtime
    int (_DSYFX_READ_VALUE)(_BOOTLOADER_RETURN_VALUE);

    _DSYFX_READ_VALUE = _BOOTLOADER_RETURN_VALUE;

    // Declare variables and pointers
    int *_DSYFX;
    int _DSYFX_VAL = _DSYFX_READ_VALUE;
    int _DSYFX_READ_RETURN = 0;

    // Assign value of _DSYFX_VAL to pointer _DSYFX
    _DSYFX = &_DSYFX_VAL;

    // Set value of _DSYFX_ADDR to address of _DSYFX
    _DSYFX_READ_RETURN = *_DSYFX;

    // Return value of _DSYFX_ADDR
    return _DSYFX_READ_RETURN;

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

void _DSYFX(int _DSYFX_CHALLENGE_INPUT) {

    int (BOOTLOADER)(_BOOTLOADER());
    int (*CHALLENGE)(int);

    int _DSYFX_BOOTLOADER_VALUE = BOOTLOADER;
    int _DSYFX_CHALLENGE_INPUT_VALUE = _DSYFX_CHALLENGE_INPUT;
    bool _DSYFX_VALID_BOOTLOADER = false;

    CHALLENGE = _DSYFX_CHALLENGE_BOOTLOADER;
    printf("%d\n", CHALLENGE(_DSYFX_CHALLENGE_INPUT_VALUE));
    printf("%p\n", &_DSYFX_BOOTLOADER_VALUE); // Print memory address of _DSYFX_BOOTLOADER_VALUE

    if (_DSYFX_BOOTLOADER_VALUE == _DSYFX_CHALLENGE_INPUT_VALUE) {
        _DSYFX_VALID_BOOTLOADER = true;
        printf("DSYFX Has Arrived!\n");
    }   else {
        _DSYFX_VALID_BOOTLOADER = false;
        printf("DSYFX Failure!\n");
    }

}

int main() {

    _DSYFX(20);

    return 0;

}
