/**
 * Copyright (c) 2021 Wayne Michael Thornton <wmthornton>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
#include "ACPI.h"
#include "PCI.h"

// Kernel information strings. Change as necessary for your system.
#define VERSION "YAFIX Kernel Release 0.0.3a Version Generic_12292021-01_i386_amd64 (64-bit)"
#define COPYRIGHT_STRING "Copyright 2020 - 2021 Wayne Michael Thornton. All rights reserved."
#define DEVELOPER_INFO "Developed by Wayne Michael Thornton (wmthornton)."
#define LICENSE_INFO "Use is subject to license terms."

// Used by DSYFX
#define RANDOM_KEY int rand(void)

// Memory management typedef
struct BootInfo {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
	ACPI::RSDP2* rsdp;
};

// Variables used to determine start and end of kernel memory space
extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

struct KernelInfo {
    PageTableManager* pageTableManager;
};


KernelInfo InitializeKernel(BootInfo* BootInfo);