#pragma once
#include "Math.h"
#include "Frame_Buffer.h"
#include "Simple_Fonts.h"
#include "System_Memory.h"
#include <stdint.h>

// Standard line placement definitions. Decreases typing during coding ops.
#define CURSOR_SINGLE  GlobalRenderer->Next()
#define CURSOR_DOUBLE  GlobalRenderer->CursorPosition = {0, GlobalRenderer->CursorPosition.Y + 32}
#define CURSOR_TRIPLE  GlobalRenderer->CursorPosition = {0, GlobalRenderer->CursorPosition.Y + 48}
#define CURSOR_DEFAULT GlobalRenderer->CursorPosition = {0,0}

// Shortcut to clear screen output using memset() function.
#define CLEAR_SCREEN_MEMSET memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize)

// Standard screen state color definitions.
#define CLEAR_FAULT_COLOR GlobalRenderer->ClearColor = 0x00ff0000;
#define CLEAR_STD_COLOR   GlobalRenderer->ClearColor = 0x0000000;
#define CLEAR_SCREEN      GlobalRenderer->Clear();


class Basic_Renderer{
    public:
    Basic_Renderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
    Point CursorPosition;
    Framebuffer* TargetFramebuffer;
    PSF1_FONT* PSF1_Font;
    unsigned int Color;
    unsigned int ClearColor;
    void Print(const char* str);
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void PutChar(char chr);
    void ClearChar();
    void Clear();
    void Next();
};

extern Basic_Renderer* GlobalRenderer;