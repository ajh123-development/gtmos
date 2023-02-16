# GTMOS

A simple operating system made from C!

## Building

### Requirements
As of now they are the same as the [Meaty Skeleton](https://wiki.osdev.org/Meaty_Skeleton#Cross-Compiling_the_Operating_System).

You will need these dependencies in order to complete this build:

* i686-elf toolchain, as discussed above.
* GRUB, for the grub-mkrescue command, along with the appropriate runtime files.
* Xorriso, the .iso creation engine used by grub-mkrescue.
* GNU make 4.0 or later.
* Qemu, optionally for testing the operating system.
This build requires a GNU/Linux system, or a similar enough system. The BSD systems may almost work. OS X is not supported but can possibly be made to work with some changes. Windows is not supported, but Windows environments like Cygwin might work, also Windows Subsystem For Linux (WSL) will work.

#### Debian-ish (like Ubuntu) Users
Install the i686-elf toolchain as described [here](https://github.com/lordmilko/i686-elf-tools) or [here](https://wiki.osdev.org/Meaty_Skeleton#Building_a_Cross-Compiler) and then install the packages `xorriso` `grub-pc-bin`.

### The real build
To build the OS simply run the `iso` make target. This will compile / link and generate a bootable iso. If you don't need an iso use the `all` target.

Finally, the `qemu` target can be used to run QEMU. It will run the `iso` target it self if the iso hasn't been made yet.

# Resources used
* [The little book about OS development](http://littleosbook.github.io/)
* [OSDev.org](https://wiki.osdev.org/)