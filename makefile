os.bin: bootloader/main.bin kernel/main.bin
	cat bootloader/main.bin kernel/main.bin > os.bin

bootloader/main.bin: bootloader/main.asm
	nasm bootloader/main.asm -f bin -o bootloader/main.bin

kernel/main.o: kernel/main.c
	gcc -m32 -ffreestanding -c kernel/main.c -o kernel/main.o -fno-pic

kernel/main.bin: kernel/main.o
	objcopy -O binary -j .text kernel/main.o kernel/main.bin

.PHONY: clean
clean:
	rm bootloader/*.bin
	rm kernel/*.o
	rm kernel/*.bin
	rm *.bin
