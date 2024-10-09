# . /Users/user/Documents/audk/BootloaderPkg/setup.sh

# echo "Compiling OVMF.fd and Bootloader..."
# PYTHON_COMMAND=/usr/bin/python3 . $PARPATH/BootloaderPkg/setup.sh

# Replace ZIG_PATH with the appropriate path
# to the Zig compiler here.
# ZIG_PATH=$HOME/Downloads/zig-macos-aarch64-0.13.0-dev.211+6a65561e3/zig
ZIG_PATH=zig

rm -rf kernel.o 2>/dev/null
rm -rf hda-contents/kernel.bin* 2>/dev/null

# Compile
$ZIG_PATH cc \
    --sysroot=x86_64-w64-mingw32-gcc \
    --target=x86_64-uefi-msvc \
    -Wl,-e,KernMain \
    -Wl,--subsystem,efi_application \
    -fuse-ld=lld-link \
    -ffreestanding \
    -nostdlib \
    -fmacro-prefix-map=src/Kernel/= \
    -fmacro-prefix-map=src/Kernel/Drivers/= \
    -fmacro-prefix-map=src/Kernel/Drivers/IO/= \
    -fmacro-prefix-map=src/Kernel/Drivers/USB/= \
    -fmacro-prefix-map=src/Kernel/Graphics/= \
    -fmacro-prefix-map=src/Kernel/Memory/= \
    -fmacro-prefix-map=src/Kernel/Util/= \
    -fmacro-prefix-map=src/Kernel/Math/= \
    -fmacro-prefix-map=src/Kernel/Syscall/= \
    -fmacro-prefix-map=src/Kernel/Syscall/CPUID/= \
    -fmacro-prefix-map=src/Kernel/Interrupts/= \
    \
    -o kernel.o \
    src/Kernel/Kernel.c \
    src/Kernel/Acpi/MADTParser.c \
    src/Kernel/Memory/KernMem.c \
    src/Kernel/Memory/KernMemoryManager.c \
    src/Kernel/Graphics/KernGraphics.c \
    src/Kernel/Graphics/KernFontParser.c \
    src/Kernel/Graphics/KernText.c \
    src/Kernel/Drivers/IO/io.c \
    src/Kernel/Drivers/IO/serial.c \
    src/Kernel/Util/KernString.c \
    src/Kernel/Util/KernRuntimeValues.c \
    src/Kernel/Syscall/CPUID/CPUID.c \
    src/Kernel/Interrupts/ApicHandler.c \
    src/Kernel/Interrupts/GDT.c \
    src/Kernel/Interrupts/Interrupts.c \
    src/Kernel/Interrupts/MSRegister.c \
    Exception.obj \
    FlushGDT.obj \
    INterrupts.obj \
    \
    -Wextra -pedantic \
    -I/Users/kernel/Documents/audk/MdePkg/Include/ \
    -I/Users/kernel/Documents/audk/MdePkg/Include/X64 \
    -I/Users/kernel/Documents/audk/KernelOSPkg/src/Common \
    -L/Users/kernel/Documents/audk/MdePkg/Library/ \
    \
    -fshort-wchar ||
    exit 1 # Exit if something goes wrong

cp kernel.o hda-contents/kernel.bin 2>/dev/null

# Run the OVMF.fd inside of QEMU
qemu-system-x86_64 \
    -serial stdio \
    -bios bootloader/bios.bin \
    -drive file=fat:rw:hda-contents,format=raw,media=disk \
    -m 1024M \
    -s
