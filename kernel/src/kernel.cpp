
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

// We use extern "C" to tell the file that it is being called from an external C program file
extern "C" void _start(BootInfo* bootInfo){

	Basic_Renderer newRenderer = Basic_Renderer(bootInfo->framebuffer, bootInfo->psf1_Font);
	
	// Determine memory map information
	uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

	GlobalAllocator = PageFrameAllocator();
	GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);
	
	// Determine kernel memory size and lock away to prevent conflict
	uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
	uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

	GlobalAllocator.LockPages(&_KernelStart, kernelPages);

	// Display kernel logo information
	newRenderer.Print("YAFIX Kernel Release 0.0.1a Version Generic_05182021-01_i386_amd64");
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Copyright 2020 - 2021 Dexter's Laboratory. All rights reserved.");
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Developed by Wayne Michael Thornton (WMT).");
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Use is subject to license terms.");
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 32};

	// Display system memory information. Very DOS-like but I think it looks cool
	newRenderer.Print("Total System RAM: ");
	newRenderer.Print(to_string(GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize)));
	newRenderer.Print(" KB");
	
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Free RAM: ");
	newRenderer.Print(to_string(GlobalAllocator.GetFreeRAM() / 1024));
	newRenderer.Print(" KB");

	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Used RAM: ");
	newRenderer.Print(to_string(GlobalAllocator.GetUsedRAM() / 1024));
	newRenderer.Print(" KB");

	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Reserved RAM: ");
	newRenderer.Print(to_string(GlobalAllocator.GetReservedRAM() / 1024));
	newRenderer.Print(" KB");

	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Kernel Pages Reserved: ");
	newRenderer.Print(to_string(kernelPages));
	newRenderer.Print(" KB of ");
	newRenderer.Print(to_string(GlobalAllocator.GetReservedRAM() / 1024));
	newRenderer.Print(" KB");
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 32};

	// Enabling virtual memory paging
	PageTable* PML4 = (PageTable*)GlobalAllocator.RequestPage();
	memset(PML4, 0, 0x1000);

	newRenderer.Print("MEMSET Function Passed");
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};

	PageTableManager pageTableManager = PageTableManager(PML4);

	newRenderer.Print("PTM Variable Set");

	for (uint64_t t = 0; t < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize); t+= 0x1000){

		pageTableManager.MapMemory((void*)t, (void*)t);
		
	}

	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Memory Sized");

	uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
	uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;
	GlobalAllocator.LockPages((void*)fbBase, fbSize / 0x1000 + 1);

	for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096){
		pageTableManager.MapMemory((void*)t, (void*)t);
	}

	asm ("mov %0, %%cr3" : : "r" (PML4));

	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Virtual Memory Initialized");

    return;
}