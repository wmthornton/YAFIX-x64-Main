#include "Kernel_Util.h"

// We use extern "C" to tell the file that it is being called from an external C program file
extern "C" void _start(BootInfo* bootInfo){

	KernelInfo kernelInfo = InitializeKernel(bootInfo);
	PageTableManager* pageTableManager = kernelInfo.pageTableManager;

	// We are using consoleOutput to distinguish text generated outside of kernel initialization
	// routines. Kernel initialization routines use kernelPrint.
	Basic_Renderer consoleOutput = Basic_Renderer(bootInfo->framebuffer, bootInfo->psf1_Font);

	// Console output must be directed to begin on the 15th line of the screen to make it
	// appear in-line with the kernel initialization output. Our character height is 16, thus
	// we use 16 * 14 to get a value of 224. All output should thus begin at position 224.
	consoleOutput.CursorPosition = {0, consoleOutput.CursorPosition.Y = 224};

	consoleOutput.Print("Kernel Initialized Successfully. Awaiting Instructions.");

	// We can't return from this function or kernel panic ensues.
    while(true);
}