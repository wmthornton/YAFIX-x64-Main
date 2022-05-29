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

#include "Kernel_Util.h"
#include "memory/Heap.h"


// We use extern "C" to tell the file that it is being called from an external C program file. _start is used as the entry point for the program and defined in kernel.ld
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
	
	// We can't return from this function or kernel panic ensues. Should be obvious, but
	// given the different levels of developer skillsets, we include the comment for clarity.
    while(true){
		// Send a CPU instruction to halt the processor when the kernel is not actively
		// working. Increases power efficiency of the processor.
		asm ("hlt");
	}
}