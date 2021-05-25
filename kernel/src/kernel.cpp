#include "Kernel_Util.h"

// We use extern "C" to tell the file that it is being called from an external C program file
extern "C" void _start(BootInfo* bootInfo){

	KernelInfo kernelInfo = InitializeKernel(bootInfo);
	PageTableManager* pageTableManager = kernelInfo.pageTableManager;

	Basic_Renderer newRenderer = Basic_Renderer(bootInfo->framebuffer, bootInfo->psf1_Font);

	// Display kernel logo information after kernel has initialized and virtual memory
	// has been setup.
	newRenderer.Print("YAFIX Kernel Release 0.0.1a Version Generic_05182021-01_i386_amd64");
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Copyright 2020 - 2021 Dexter's Laboratory. All rights reserved.");
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Developed by Wayne Michael Thornton (WMT).");
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Use is subject to license terms.");
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 32};

	// Display system memory information. Very DOS-like but I think it looks cool. Does not
	// include virtual memory.
	newRenderer.Print("Free Physical RAM: ");
	newRenderer.Print(to_string(GlobalAllocator.GetFreeRAM() / 1024));
	newRenderer.Print(" KB");

	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Used Physical RAM: ");
	newRenderer.Print(to_string(GlobalAllocator.GetUsedRAM() / 1024));
	newRenderer.Print(" KB");

	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Reserved Physical RAM: ");
	newRenderer.Print(to_string(GlobalAllocator.GetReservedRAM() / 1024));
	newRenderer.Print(" KB");
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 32};

	// System status messages... no real use but looks cool. Probably a memory drain.
	newRenderer.Print("MEMSET Function Passed");
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Memory Sized");
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("PTM Variable Set");
	newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
	newRenderer.Print("Virtual Memory Initialized");

	// We can't return from this function or kernel panic ensues.
    while(true);
}