bin/os.img: bin bin/os.bin
	dd if=/dev/zero of=bin/os.img count=2280
	dd if=bin/os.bin of=bin/os.img conv=notrunc

bin/os.bin: bin/bootloader.bin bin/kernel.bin
	cat bin/bootloader.bin bin/kernel.bin > bin/os.bin

bin/bootloader.bin: bootloader/main.asm
	nasm bootloader/main.asm -f bin -o bin/bootloader.bin

bin/kernel.o: kernel/main.c
	gcc -m32 -ffreestanding -c kernel/main.c -o bin/kernel.o -fno-PIC

bin/kernel.elf: bin/kernel.o
	ld -m elf_i386 bin/kernel.o -o bin/kernel.elf

bin/kernel.bin: bin/kernel.elf
	objcopy -O binary -j .text bin/kernel.elf bin/kernel.bin

bin:
	mkdir bin

.PHONY: clean
clean:
	rm bin/*
