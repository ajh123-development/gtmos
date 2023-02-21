# GTMOS

A simple operating system made from C!

## Building

### Requirements
A similar process is used in the [Meaty Skeleton](https://wiki.osdev.org/Meaty_Skeleton).

You will need these dependencies in order to complete this build:

* x86_64-elf toolchain, as discussed [here](https://wiki.osdev.org/Meaty_Skeleton#Cross-Compiling_the_Operating_System) (explicity called `x86_65-elf-...`).
* Git.
* Xorriso, the .iso creation engine used by grub-mkrescue.
* GNU make 4.0 or later.
* NASM (The Netwide assembler) for build the assembly object files.
* Qemu, optionally for testing the operating system.
This build requires a GNU/Linux system, or a similar enough system. The BSD systems may almost work. OS X is not supported but can possibly be made to work with some changes. Windows is not supported, but Windows environments like Cygwin might work, also Windows Subsystem For Linux (WSL) will work.

#### Debian-ish (like Ubuntu) Users
Use the i686-elf toolchain from [here](https://github.com/lordmilko/i686-elf-tools) or [here](https://wiki.osdev.org/Meaty_Skeleton#Building_a_Cross-Compiler) and use the `-64` option and then install the packages `xorriso` `nasm`, and probably a few more ...

### The real build
To build the OS simply run the `iso` make target. This will compile / link and generate a bootable iso. If you don't need an iso use the `build` target.

Finally, the `run` target can be used to run QEMU, or the `run-uefi` to run QEMU with UEFI support. It will run the `iso` target it self if the iso hasn't been made yet.

# Resources used
* [The little book about OS development](http://littleosbook.github.io/)
* [OSDev.org](https://wiki.osdev.org/)
* [Nanobyte OS](https://github.com/nanobyte-dev/nanobyte_os)