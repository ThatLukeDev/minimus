# Minimus
A kernel? An OS? Something?

## Run
To run in a VM (faster), the command for qemu is `qemu-system-x86_64 -hda bin/os.img`.

To emulate, the command for bochs is `bochs -q` followed by a `c` in the bochs terminal (for continue).
Simply run `./run` in a bash shell with dependencies installed to run.

## Build
To build, install all dependencies and run `make`.

## Make Dependencies
|  Name      |  PKG                  |
|------------|-----------------------|
|  GNUMake   |  `make`               |
|  GCC       |  `gcc`                |
|  NASM      |  `nasm`               |
|  qemu      |  `qemu-system-x86_64` |
|  bochs     |  `bochs`              |

# Decompilation
To decompile, run `objdump -b binary --adjust-vma=0x7c00 -mi386 -D bin/os.bin | less`
