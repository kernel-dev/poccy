# Poccy

Poccy, whilst still a WIP, is a toy OS I've built in my spare time for a school project. More precisely, I am doing my senior's paper/thesis on operating systems and kernels, and am providing this one as an example to detail how one may go about kernel/OS development.

## Goals

- [x] Custom bootloader to obtain basic information necessary, load the kernel image and call it with passed down arguments.
- [x] Graphics methods for handling plotting pixels to the screen
- [x] Handling drawing glyphs on the screen from a font file
- [ ] Filesystem handler
- [ ] Memory management (pagers, vmem functions, etc.)
- [ ] Mutex locks for threads
- [ ] Basic Bash & C support
- [ ] PS/2 Keyboard support
- [ ] ACPICA implementation
- [ ] DSDT parser to expose the table in plaintext
- [ ] Basic math library (logarithms, pow(), etc.)

## Building the project

First of all, you must create 2 directories: `hda-contents` and `bootloader`, as QEMU will read `hda-contents` as a virtual disk, and the `OvmfPkg` image will be placed in `bootloader`. 
In the `hda-contents` directory, add a new directory: `EFI/BOOT`.

Next, check out [the bootloader project](https://github.com/kernel-dev/kernelOSBootloader) for more information on how to use the EDK2 build system and on how to compile the bootloader itself.

You're going to need [Zig](https://github.com/ziglang/zig). This project uses Zig's drop-in replacement for GCC/Clang to cross-compile for PE+ images. I had difficulties invoking `zig cc` directly in CMake, as such, I simply made a bash script to circumvent this issue (although you could just prepend `CC="zig cc $@"` before invoking cmake), and compiled it as a binary called `zigcc`.

The required version of Zig (at time of writing this: August 28th, 2023) is `0.11-dev`.

The rest of the dependencies are as follows:

- `mingw`
- `LLVM`
- `qemu`

Once you've properly set up dependencies and compiled the bootloader, execute the following commands:

```bash
cmake -S . -B <build_directory>

cd <build_directory>

cmake --build .
```

After that, you can just execute qemu:

```bash
qemu-system-x86_64 \
            -serial stdio \
            -bios bootloader/bios.bin \
            -drive file=fat:rw:hda-contents,format=raw,media=disk \
            -m 1024M \
            -s \
            -no-reboot -d int,cpu_reset
```

Additionally, if you need to use a debugger, you will need to append the `-S` flag when executing qemu. As per the nature of GDB, it doesn't support Microsoft's Program Database (PDB) file format, and you can only use LLDB for real-time debugging.

## Credits / Resources

- [UEFI.org](https://uefi.org/specsandtesttools) - for providing exhaustive and detailed specifications of both UEFI and ACPI.
- [OSDev Wiki](https://wiki.osdev.org/Expanded_Main_Page) - for providing me, and a plentiful of other users, with the common knowledge as an introduction for OS development.
- [Tianocore](https://github.com/tianocore/edk2) - for providing UEFI utilities and abstractions.
- [Mhaeuser](https://github.com/mhaeuser) — for providing this project with an amazing library for PE/COFF images (PeCoffLib2), which was used in the bootloader.
