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

#include "Interrupts.h"
#include "../Panic.h"
#include "../IO.h"
#include "../userinput/Keyboard.h"
#include "../userinput/Mouse.h"
#include "../scheduling/PIT.h"

__attribute__((interrupt)) void PageFault_Handler(interrupt_frame* frame){
    Panic("Page Fault Detected");
    while(true);
}

__attribute__((interrupt)) void DoubleFault_Handler(interrupt_frame* frame){
    Panic("Double Fault Detected");
    while(true);
}

__attribute__((interrupt)) void GPFault_Handler(interrupt_frame* frame){
    Panic("General Protection Fault Detected");
    while(true);
}

__attribute__((interrupt)) void KeyboardInt_Handler(interrupt_frame* frame){
    uint8_t scancode = inb(0x60);
    HandleKeyboard(scancode);
    PIC_EndMaster();
}

__attribute__((interrupt)) void MouseInt_Handler(interrupt_frame* frame){

    uint8_t mouseData = inb(0x60);

    HandlePS2Mouse(mouseData);

    PIC_EndSlave();
}

__attribute__((interrupt)) void PITInt_Handler(interrupt_frame* frame){

    PIT::Tick();
    PIC_EndMaster();
}

// End the interrupts for PIC chip
void PIC_EndMaster(){
    outb(PIC1_COMMAND, PIC_EOI);
}

void PIC_EndSlave(){
    outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}

void RemapPIC(){
    uint8_t a1, a2; 

    // Save current bitmasks
    a1 = inb(PIC1_DATA);
    io_wait();
    a2 = inb(PIC2_DATA);
    io_wait();

    // Initialize Master PIC
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    // Initialize Slave PIC
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    // Master PIC offset
    outb(PIC1_DATA, 0x20);
    io_wait();
    // Slave PIC offset
    outb(PIC2_DATA, 0x28);
    io_wait();

    // Tell PICs how they correspond/know of existence
    outb(PIC1_DATA, 4);
    io_wait();
    outb(PIC2_DATA, 2);
    io_wait();

    // Tell PICs to operate in 8086 mode
    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    // Restore bitmasks
    outb(PIC1_DATA, a1);
    io_wait();
    outb(PIC2_DATA, a2);

}