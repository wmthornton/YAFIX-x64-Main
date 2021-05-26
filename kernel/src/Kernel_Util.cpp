#include "Kernel_Util.h"

KernelInfo kernelInfo;
PageTableManager pageTableManager = NULL; 
void PrepareMemory(BootInfo* bootInfo)
{
	// Determine memory map information
	uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

	GlobalAllocator = PageFrameAllocator();
	GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);
	
	// Determine kernel memory size and lock away to prevent conflict
	uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
	uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

	GlobalAllocator.LockPages(&_KernelStart, kernelPages);

	// Enabling virtual memory paging
	PageTable* PML4 = (PageTable*)GlobalAllocator.RequestPage();
	memset(PML4, 0, 0x1000);

	pageTableManager = PageTableManager(PML4);

	for (uint64_t t = 0; t < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize); t+= 0x1000){

		pageTableManager.MapMemory((void*)t, (void*)t);
		
	}

	uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
	uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;
	GlobalAllocator.LockPages((void*)fbBase, fbSize / 0x1000 + 1);

	for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096){
		pageTableManager.MapMemory((void*)t, (void*)t);
	}

	asm ("mov %0, %%cr3" : : "r" (PML4));

    kernelInfo.pageTableManager = &pageTableManager;
}

void KernelLogo(BootInfo* bootInfo)
{

	// We are using kernelOutput to distinguish text generated inside of kernel initialization
	// routines. Non-kernel initialization routines use consolePrint.
    Basic_Renderer kernelPrint = Basic_Renderer(bootInfo->framebuffer, bootInfo->psf1_Font);

	// Kernel logo information can be changed to reflect updated version information.
	// In future, these should be stored as variables passed to the compiler and auto-populated
	// but for now, this works.
	kernelPrint.Print("YAFIX Kernel Release 0.0.1a Version Generic_05182021-01_i386_amd64");
	kernelPrint.CursorPosition = {0, kernelPrint.CursorPosition.Y + 16};
	kernelPrint.Print("Copyright 2020 - 2021 Dexter's Laboratory. All rights reserved.");
	kernelPrint.CursorPosition = {0, kernelPrint.CursorPosition.Y + 16};
	kernelPrint.Print("Developed by Wayne Michael Thornton (WMT).");
	kernelPrint.CursorPosition = {0, kernelPrint.CursorPosition.Y + 16};
	kernelPrint.Print("Use is subject to Unlicense terms.");
	kernelPrint.CursorPosition = {0, kernelPrint.CursorPosition.Y + 32};

	// Display system memory information. Very DOS-like but I think it looks cool. Does not
	// include virtual memory information.
	kernelPrint.Print("Free Physical RAM: ");
	kernelPrint.Print(to_string(GlobalAllocator.GetFreeRAM() / 1024));
	kernelPrint.Print(" KB");

	kernelPrint.CursorPosition = {0, kernelPrint.CursorPosition.Y + 16};
	kernelPrint.Print("Used Physical RAM: ");
	kernelPrint.Print(to_string(GlobalAllocator.GetUsedRAM() / 1024));
	kernelPrint.Print(" KB");

	kernelPrint.CursorPosition = {0, kernelPrint.CursorPosition.Y + 16};
	kernelPrint.Print("Reserved Physical RAM: ");
	kernelPrint.Print(to_string(GlobalAllocator.GetReservedRAM() / 1024));
	kernelPrint.Print(" KB");
	kernelPrint.CursorPosition = {0, kernelPrint.CursorPosition.Y + 32};

	// System status messages... no real use but looks cool. Probably a memory drain.
	kernelPrint.Print("MEMSET Function Passed");
	kernelPrint.CursorPosition = {0, kernelPrint.CursorPosition.Y + 16};
	kernelPrint.Print("Memory Sized");
	kernelPrint.CursorPosition = {0, kernelPrint.CursorPosition.Y + 16};
	kernelPrint.Print("PTM Variable Set");
	kernelPrint.CursorPosition = {0, kernelPrint.CursorPosition.Y + 16};
	kernelPrint.Print("Virtual Memory Initialized");

    return;
}

KernelInfo InitializeKernel(BootInfo* bootInfo)
{
    PrepareMemory(bootInfo);

    // Set all pixels to black as soon as kernel has initialized. Removes UEFI messages.
    // Has added effect of removing odd color bars within some VMs during boot.
	memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);

	// Display kernel logo information after kernel has initialized and virtual memory
	// has been setup.
	KernelLogo(bootInfo);

    return kernelInfo;
}
