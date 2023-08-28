#!/bin/zsh

DIRPATH="$(
    cd -- "$(dirname "$0")" >/dev/null 2>&1
    pwd -P
)"

echo "Attempting to launch QEMU..."

osascript - "$DIRPATH" <<EOF
  on run argv
    tell application "Terminal"
      do script ("cd " & quoted form of item 1 of argv) in window 1
      do script "
          qemu-system-x86_64 \
            -serial stdio \
            -bios bootloader/bios.bin \
            -drive file=fat:rw:hda-contents,format=raw,media=disk \
            -m 1024M \
            -s \
            -no-reboot -d int,cpu_reset
      " in window 1
    end tell
  end run
EOF