#pragma once
#include "Math.h"
#include "Frame_Buffer.h"
#include "Simple_Fonts.h"

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