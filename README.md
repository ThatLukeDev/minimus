# Minimus
I'm not quite sure what this is yet.

## Run
To run in a VM, the command for bochs is `bochs -q` followed by a `c` in the bochs terminal (for continue).
Simply run `./run` in a bash shell with dependencies installed to run.

## Build
To build, install all dependencies and run `make`.

## Dependencies
|  Name      |  PKG                |
|------------|---------------------|
|  GNUMake   |  `make`             |
|  GCC       |  `gcc`              |
|  NASM      |  `nasm`             |
|  bochs     |  `bochs`            |

# Decompilation
To decompile, run `objdump -b binary --adjust-vma=0x7c00 -mi386 -D bin/os.bin | less`
