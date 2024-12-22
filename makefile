bin/os.img: bin bin/os.bin file/bin/blob
	dd if=/dev/zero of=$@ bs=512 count=32768
	dd if=file/bin/blob of=$@ bs=512 seek=40
	dd if=bin/os.bin of=$@ conv=notrunc

bin/os.bin: bin/bootloader.bin bin/kernel.bin
	cat $^ > $@

bin/bootloader.bin: bootloader/main.asm
	nasm $^ -f bin -o $@

kernel/libs/lib.o: kernel/libs/*.h kernel/libs/*.c kernel/libs/*.asm
	cd kernel/libs && make

bin/kernel.o: kernel/main.c kernel/libs/lib.o
	gcc -Ikernel/libs -m32 -ffreestanding -c $< -o $@ -fno-PIC -mno-sse

bin/kernel.elf: bin/kernel.o kernel/libs/lib.o
	ld -m elf_i386 $^ -o $@ -T kernel/link.ld

bin/kernel.bin: bin/kernel.elf
	objcopy -O binary $^ $@

file/bin/blob: file/files/* os/*.c
	cd os && make
	cd file && make

bin:
	mkdir $@

.PHONY: clean
clean:
	cd kernel/libs && make clean
	cd file && make clean
	rm bin/*
