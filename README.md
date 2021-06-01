MINIMAL REQUIREMENTS TO COMPILE THE YAFIX KERNEL

Intro

This document is designed to provide a list of the minimum levels of software necessary to compile the YAFIX kernel.

Current Minimal Requirements

Keep in mind that this list assumes you are already functionally running a Linux kernel, specifically Ubuntu 20.04 or later, in a virtual machine or on bare metal.  Also, not all tools are necessary on all systems; obviously, if you have a preferred IDE, then VS Code is not required. If you are using a different Linux distribution, you may need to modify the following commands accordingly.

Program 	Command to obtain software
GNU gcc     sudo apt-get intall build-essential
GNU make    sudo apt-get install mtools
nasm        sudo apt-get install nasm
git         sudo apt-get install git
qemu        sudo apt-get install qemu
aqemu       sudo apt-get install aqemu
VS Code     sudo snap install --classic code */Assumes SNAP store is installed/*

All required software can be obtained by entering the following commands into your Terminal emulator:

*/ sudo apt-get install build-essential mtools nasm git qemu aqemu /*
*/ sudo snap install --classic code /*

Downloading The Kernel Source

If you are viewing this README on Github, chances are you already know how to download the source code for the YAFIX kernel. However, common sense dictates that we provide directions for those that are unfamiliar with the process.

To download the kernel source, you need to open a new Terminal emulator and enter:

*/ cd Desktop /*
*/ git clone https://github.com/wmthornton/YAFIX-x64-Main.git /*
*/ cd YAFIX-x64-Main /*

Compiling the Bootloader

YAFIX is an EFI-based operating system. As such, we have designed an appropriate bootloader that tells the computer when and how to start the YAFIX kernel. Compling the bootloader is an integral part of the process and must be done before anything else can compiled and run.

To compile the bootloader, you need to enter the "gnu-efi" directory in your Terminal emulator. Assuming you followed the steps to download the kernel source, you are already where you need to be in order to enter the following command:

*/ cd gnu-efi /*

If you did this correctly, your terminal will look like this:

*/ wayne@MacBook:~/Desktop/YAFIX-x64-Main/gnu-efi$ /* 

Now you're in the correct directory to compile the bootloader. Type the following:

*/ make bootloader /*

You will receive a series of outputs in your Terminal and will be returned to the prompt. Read the output given. If no errors are indicated you have successfully compiled the YAFIX bootloader.

Compiling The Kernel

Now that we have compiled the bootloader, we must compile the kernel itself. This process is fairly straightforward and you should not have any issues as long as you have met the software requirements detailed earlier.

The first command you need to enter into your Terminal emulator are the commands that allows you to change directories to the kernel source tree. Enter the following commands at the prompt:

*/ cd ../ /*
*/ cd kernel /*

Your prompt should have to changed to now look like this:

*/ wayne@MacBook:~/Desktop/YAFIX-x64-Main/kernel$ /*

The Git repository contains old and outdated build files that must first be deleted prior to compiling the kernel. This is done to ensure that no conflicts exist and that the kernel is truly up-to-date. It is recommended that this command is done everytime you wish to compile the kernel from source. 

In order to delete the old and outdated build files, you must enter the following at the prompt:

*/ rm -r lib /*

This command deletes the "lib" folder and all of the outdated build files within. This will be very fast and you will not receive a warning or other indication of success.

We are now ready to compile the kernel from source! To compile the kernel, enter the following commands:

*/ make kernel /*

If this command completes successfully, you will receive a series of output but nothing that indicates an error or warning. These two problems will be indicated clearly by colored text.

Assuming you have no errors, the kernel has compiled and is now ready to be combined with the bootloader into a single, bootable image file. To accomplish this, enter the following at the prompt:

*/ make buildimg /*

You will receive the following output if everything completed successfully:

*/ dd if=/dev/zero of=bin/YAFIX.img bs=512 count=93750 /*
*/ 93750+0 records in /*
*/ 93750+0 records out /*
*/ 48000000 bytes (48 MB, 46 MiB) copied, 1.11708 s, 43.0 MB/s /*
*/ mformat -i bin/YAFIX.img -f 1440 :: /*
*/ mmd -i bin/YAFIX.img ::/EFI /*
*/ mmd -i bin/YAFIX.img ::/EFI/BOOT /*
*/ mcopy -i bin/YAFIX.img ../gnu-efi/x86_64/bootloader/main.efi ::/EFI/BOOT /*
*/ mcopy -i bin/YAFIX.img startup.nsh :: /*
*/ mcopy -i bin/YAFIX.img bin/kernel.elf :: /*
*/ mcopy -i bin/YAFIX.img bin/zap-light16.psf :: /*

Booting The Kernel For The First Time

Now that you have compiled the bootloader and kernel, and produced a bootable image file, you are ready to boot into a Qemu virtual machine running YAFIX.

This process is simple. Enter the following command at the prompt:

*/ make run /*

A Qemu virtual machine will start and the YAFIX kernel will be loaded. If you have issues with the machine not starting, exit Qemu and try the compilation process again. 




