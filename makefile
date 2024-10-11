os.img: os.bin
	dd if=/dev/zero of=os.img count=2280
	dd if=os.bin of=os.img conv=notrunc

os.bin: bootloader.bin kernel.bin
	cat bootloader.bin kernel.bin > os.bin

bootloader.bin: bootloader/main.asm
	nasm bootloader/main.asm -f bin -o bootloader.bin

kernel.o: kernel/main.c
	gcc -m32 -ffreestanding -c kernel/main.c -o kernel.o -fno-PIC

kernel.elf: kernel.o
	ld -m elf_i386 kernel.o -o kernel.elf

kernel.bin: kernel.elf
	objcopy -O binary -j .text kernel.elf kernel.bin

.PHONY: clean
clean:
	rm bootloader.bin
	rm kernel.o
	rm kernel.elf
	rm kernel.bin
	rm os.bin
	rm os.img
