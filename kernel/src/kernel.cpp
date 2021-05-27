#include "Kernel_Util.h"

// We use extern "C" to tell the file that it is being called from an external C program file
extern "C" void _start(BootInfo* bootInfo){

	KernelInfo kernelInfo = InitializeKernel(bootInfo);
	PageTableManager* pageTableManager = kernelInfo.pageTableManager;

	// We are using GlobalRenderer to output all text from the kernel.

	// Console output must be directed to begin after the kernelLogo function output.
	// We use GlobalRenderer->CursorPosition.Y + 32 to provide a space between the
	// previous output and new output.
	CURSOR_DOUBLE;

	GlobalRenderer->Print("Kernel Initialized Successfully. Awaiting Instructions.");
	CURSOR_DOUBLE;
	GlobalRenderer->Print("YAFIX #: ");


	

	// We can't return from this function or kernel panic ensues.
    while(true);
}