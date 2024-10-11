os.img: os.bin
	dd if=/dev/zero of=os.img count=2280
	dd if=os.bin of=os.img conv=notrunc

os.bin: bootloader/main.bin kernel/main.bin
	cat bootloader/main.bin kernel/main.bin > os.bin

bootloader/main.bin: bootloader/main.asm
	nasm bootloader/main.asm -f bin -o bootloader/main.bin

kernel/main.o: kernel/main.c
	gcc -m32 -ffreestanding -c kernel/main.c -o kernel/main.o -fno-PIC

kernel/main.elf: kernel/main.o
	ld -m elf_i386 kernel/main.o -o kernel/main.elf

kernel/main.bin: kernel/main.elf
	objcopy -O binary -j .text kernel/main.elf kernel/main.bin

.PHONY: clean
clean:
	rm bootloader/*.bin
	rm kernel/*.o
	rm kernel/*.elf
	rm kernel/*.bin
	rm *.bin
	rm *.img
