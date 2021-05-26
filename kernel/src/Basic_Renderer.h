#pragma once
#include "Math.h"
#include "Frame_Buffer.h"
#include "Simple_Fonts.h"
#include "System_Memory.h"

// Standard line placement definitions. Decreases typing during coding ops.
#define CURSOR_SINGLE  GlobalRenderer->CursorPosition = {0, GlobalRenderer->CursorPosition.Y + 16}
#define CURSOR_DOUBLE  GlobalRenderer->CursorPosition = {0, GlobalRenderer->CursorPosition.Y + 32}
#define CURSOR_TRIPLE  GlobalRenderer->CursorPosition = {0, GlobalRenderer->CursorPosition.Y + 48}
#define CURSOR_DEFAULT GlobalRenderer->CursorPosition.Y = 0

// Shortcut to clear screen output using memset() function.
#define CLEAR_SCREEN memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize)

class Basic_Renderer{
    public:
    Basic_Renderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
    Point CursorPosition;
    Framebuffer* TargetFramebuffer;
    PSF1_FONT* PSF1_Font;
    unsigned int Colour;
    void Print(const char* str);
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
};

extern Basic_Renderer* GlobalRenderer;