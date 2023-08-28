cmake_minimum_required(VERSION 3.22)

set(CMAKE_OSX_ARCHITECTURES "x86_64")

project(KernelOSPkg VERSION 0.1.0 LANGUAGES C ASM)

enable_language(C ASM ASM_NASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER zigcc)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DPRINT_TABS -DDEBUG_CPU -DDEBUG_INTERRUPTS")

set(CMAKE_ASM_COMPILER /usr/local/bin/nasm)
set(CMAKE_NASM_SOURCE_FILE_EXTENSIONS "s;S")

set(ASM_SOURCES
        ${CMAKE_SOURCE_DIR}/src/Assembly/FlushGDT.s
        ${CMAKE_SOURCE_DIR}/src/Assembly/Interrupts.s)

foreach (ASM_SOURCE ${ASM_SOURCES})
    get_filename_component(ASM_FILENAME ${ASM_SOURCE} NAME_WE)
    set(ASM_OBJECT "${CMAKE_CURRENT_BINARY_DIR}/${ASM_FILENAME}.obj")
    add_custom_command(
            OUTPUT ${ASM_OBJECT}
            COMMAND nasm -f win64 ${ASM_SOURCE} -o ${ASM_OBJECT}
            DEPENDS ${ASM_SOURCE}
    )
    list(APPEND ASM_OBJECTS ${ASM_OBJECT})
endforeach ()

add_executable(KernelOSPkg
        ${CMAKE_SOURCE_DIR}/src/Kernel/Kernel.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Drivers/IO/io.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Drivers/IO/serial.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Drivers/USB/KernKeyboard.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Drivers/PS2/PS2KeyboardDriver.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Interrupts/ApicHandler.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Interrupts/MSRegister.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Interrupts/GDT.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Syscall/CPUID/CPUID.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Graphics/KernFontParser.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Graphics/KernGraphics.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Graphics/KernText.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Memory/KernMemoryManager.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Memory/KernMem.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Util/KernRuntimeValues.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Util/KernString.c
        ${CMAKE_SOURCE_DIR}/src/Kernel/Util/KernUtil.c
        ${CMAKE_SOURCE_DIR}/src/Math/Pow.c
        ${CMAKE_SOURCE_DIR}/src/Math/Logarithm.c
        ${CMAKE_SOURCE_DIR}/src/Common/Drivers/IO/io.h
        ${CMAKE_SOURCE_DIR}/src/Common/Drivers/IO/serial.h
        ${CMAKE_SOURCE_DIR}/src/Common/Drivers/USB/KernKeyboard.h
        ${CMAKE_SOURCE_DIR}/src/Common/Drivers/PS2/PS2KeyboardDriver.h
        ${CMAKE_SOURCE_DIR}/src/Common/Interrupts/ApicHandler.h
        ${CMAKE_SOURCE_DIR}/src/Common/Interrupts/MSRegister.h
        ${CMAKE_SOURCE_DIR}/src/Common/Interrupts/GDT.h
        ${CMAKE_SOURCE_DIR}/src/Common/Interrupts/IDTRTable.h
        ${CMAKE_SOURCE_DIR}/src/Common/Interrupts/TrapExceptions.h
        ${CMAKE_SOURCE_DIR}/src/Common/Syscall/CPUID/CPUID.h
        ${CMAKE_SOURCE_DIR}/src/Common/Graphics/KernFontParser.h
        ${CMAKE_SOURCE_DIR}/src/Common/Graphics/KernGraphics.h
        ${CMAKE_SOURCE_DIR}/src/Common/Graphics/KernText.h
        ${CMAKE_SOURCE_DIR}/src/Common/Graphics/KernGop.h
        ${CMAKE_SOURCE_DIR}/src/Common/Memory/KernMemoryManager.h
        ${CMAKE_SOURCE_DIR}/src/Common/Memory/KernMem.h
        ${CMAKE_SOURCE_DIR}/src/Common/Memory/KernEfiMem.h
        ${CMAKE_SOURCE_DIR}/src/Common/Util/KernRuntimeValues.h
        ${CMAKE_SOURCE_DIR}/src/Common/Util/KernString.h
        ${CMAKE_SOURCE_DIR}/src/Common/Util/KernUtil.h
        ${CMAKE_SOURCE_DIR}/src/Common/Math/Pow.h
        ${CMAKE_SOURCE_DIR}/src/Common/Math/Logarithm.h
        ${ASM_OBJECTS})

set_target_properties(KernelOSPkg PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/hda-contents")
set_target_properties(KernelOSPkg PROPERTIES OUTPUT_NAME "kernel.bin")

target_compile_options(KernelOSPkg PRIVATE
        -g
        --target=x86_64-uefi-msvc
        --sysroot=x86_64-w64-mingw32-gcc
        -ffreestanding
        -nostdlib
        -fmacro-prefix-map=${CMAKE_SOURCE_DIR}/src/Kernel/=
        -fmacro-prefix-map=${CMAKE_SOURCE_DIR}/src/Kernel/Drivers/IO/=
        -fmacro-prefix-map=${CMAKE_SOURCE_DIR}/src/Kernel/Drivers/USB/=
        -fmacro-prefix-map=${CMAKE_SOURCE_DIR}/src/Kernel/Graphics/=
        -fmacro-prefix-map=${CMAKE_SOURCE_DIR}/src/Kernel/Memory/=
        -fmacro-prefix-map=${CMAKE_SOURCE_DIR}/src/Kernel/Util/=
        -fmacro-prefix-map=${CMAKE_SOURCE_DIR}/src/Kernel/Math/=
        -Wextra -pedantic
        )

target_link_options(KernelOSPkg PRIVATE
        --target=x86_64-uefi-msvc
        --sysroot=x86_64-w64-mingw32-gcc
        -fuse-ld=lld-link
        -Wl,--entry,EfiMain
        -Wl,--subsystem,efi_application
        -fshort-wchar
        )

target_include_directories(KernelOSPkg PRIVATE ${CMAKE_SOURCE_DIR}/src/Common/)
target_include_directories(KernelOSPkg PRIVATE ${CMAKE_SOURCE_DIR}/../MdePkg/Include/)
target_include_directories(KernelOSPkg PRIVATE ${CMAKE_SOURCE_DIR}/../MdePkg/Include/X64/)

link_libraries(/Users/kernel/Documents/AUDK/MdePkg/Library/)
target_link_libraries(KernelOSPkg PRIVATE ${ASM_OBJECTS})