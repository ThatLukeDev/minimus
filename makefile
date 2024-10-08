os.bin: bootloader/main.bin kernel/main.bin
	cat bootloader/main.bin kernel/main.bin > os.bin

bootloader/main.bin: bootloader/main.asm
	nasm bootloader/main.asm -f bin -o bootloader/main.bin

kernel/entry.o: kernel/entry.asm
	nasm kernel/entry.asm -f elf -o kernel/entry.o

kernel/main.o: kernel/main.c
	gcc -m32 -ffreestanding -fno-PIC -c kernel/main.c -o kernel/main.o

kernel/main.bin: kernel/entry.o kernel/main.o
	ld -m elf_i386 -o kernel/main.bin -no-pie -Ttext 0x1000 kernel/entry.o kernel/main.o --oformat binary
