run: os.bin
	qemu-system-elf32_x84_64 -fda image.bin

os.bin: bootloader/main.bin kernel/main.bin
	cat bootloader/main.bin kernel/main.bin > os.bin

bootloader/main.bin: bootloader/main.asm
	nasm bootloader/main.asm -f bin -o bootloader/main.bin

kernel/entry.o: kernel/entry.asm
	nasm kernel/entry.asm -f elf -o kernel/entry.o

kernel/main.o: kernel/main.c
	gcc -m32 -ffreestanding -c kernel/main.c -o kernel.main.o

kernel/main.bin: kernel/entry.o kernel/main.o
	ld -m elf32_x86_64 -o kernel/main.bin -Ttext 0x1000 kernel/entry.o --oformat binary
