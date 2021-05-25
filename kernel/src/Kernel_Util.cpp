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

KernelInfo InitializeKernel(BootInfo* bootInfo)
{
    PrepareMemory(bootInfo);

    // Set all pixels to black as soon as kernel has initialized. Removes UEFI messages.
    // Has added effect of removing odd color bars within some VMs during boot.
	memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);

    return kernelInfo;
}