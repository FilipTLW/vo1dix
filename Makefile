qemu_iso: out/kernel.o out/boot.o out/iso/boot/grub/grub.cfg
	i686-elf-gcc -T linker/linker.ld -o out/vo1dix.bin -ffreestanding -O2 -nostdlib out/boot.o out/kernel.o -lgcc
	cp out/vo1dix.bin out/iso/boot/vo1dix.bin
	grub-mkrescue -o out/vo1dix.iso out/iso

out/kernel.o: kernel/kernel.c
	i686-elf-gcc -c kernel/kernel.c -o out/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

out/boot.o: boot/boot.asm
	nasm -felf32 boot/boot.asm -o out/boot.o

out/iso/boot/grub/grub.cfg: boot/grub.cfg
	mkdir -p out/iso/boot/grub
	cp boot/grub.cfg out/iso/boot/grub/grub.cfg
