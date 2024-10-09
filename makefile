os.bin: bootloader/main.elf kernel/main.elf
	ld -m elf_i386 -o os.bin -no-pie -Ttext 0x7c00 bootloader/main.elf kernel/main.elf --oformat binary -T kernel/entry.ld

bootloader/main.elf: bootloader/main.asm
	nasm bootloader/main.asm -f elf -o bootloader/main.elf

kernel/entry.o: kernel/entry.asm
	nasm kernel/entry.asm -f elf -o kernel/entry.o

kernel/main.o: kernel/main.c
	gcc -m32 -ffreestanding -fno-PIC -c kernel/main.c -o kernel/main.o

kernel/main.elf: kernel/entry.o kernel/main.o
	ld -m elf_i386 -o kernel/main.elf -no-pie -Ttext 0x1000 kernel/entry.o kernel/main.o -T kernel/entry.ld

.PHONY: clean
clean:
	rm bootloader/*.elf
	rm kernel/*.o
	rm kernel/*.elf
	rm *.bin
