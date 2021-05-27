#pragma once

#include <stdint.h>
#include "Basic_Renderer.h"
#include "C_String.h"
#include "EFI_Memory.h"
#include "System_Memory.h"
#include "Memory_Bitmap.h"
#include "paging/PageFrameAllocator.h"
#include "paging/PageMapIndexer.h"
#include "paging/Paging.h"
#include "paging/PageTableManager.h"
#include "userinput/Mouse.h"

// Kernel information strings. Change as necessary for your system.
#define VERSION "YAFIX Kernel Release 0.0.1a Version Generic_05182021-01_i386_amd64 (64-bit)"
#define COPYRIGHT_STRING "Copyright 2020 - 2021 *NIX Foundation, Inc. All rights reserved."
#define DEVELOPER_INFO "Developed by Wayne Michael Thornton (WMT)."
#define LICENSE_INFO "Use is subject to Unlicense terms."

// Memory management typedef
struct BootInfo {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
};

// Variables used to determine start and end of kernel memory space
extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

struct KernelInfo {
    PageTableManager* pageTableManager;
};

KernelInfo InitializeKernel(BootInfo* BootInfo);