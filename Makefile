OBJS = out/boot.o out/kernel.o
CFLAGS = -T linker/linker.ld -o out/vo1dix.bin -ffreestanding -O2 -nostdlib -lgcc
CRTI_OBJ = out/crti.o
CRTBEGIN_OBJ := $(shell i686-elf-gcc $(CFLAGS) $(OBJS) --print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell i686-elf-gcc $(CFLAGS) $(OBJS) --print-file-name=crtend.o)
CRTN_OBJ = out/crtn.o

OBJ_LINK_LIST := $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)

qemu_iso: $(OBJ_LINK_LIST) out/iso/boot/grub/grub.cfg
	i686-elf-gcc $(CFLAGS) $(OBJ_LINK_LIST)
	cp out/vo1dix.bin out/iso/boot/vo1dix.bin
	grub-mkrescue -o out/vo1dix.iso out/iso

out/crti.o: boot/crti.asm
	nasm -felf32 boot/crti.asm -o $(CRTI_OBJ)

out/crtn.o: boot/crtn.asm
	nasm -felf32 boot/crtn.asm -o $(CRTN_OBJ)

out/kernel.o: kernel/kernel.c
	i686-elf-gcc -c kernel/kernel.c -o out/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

out/boot.o: boot/boot.asm
	nasm -felf32 boot/boot.asm -o out/boot.o

out/iso/boot/grub/grub.cfg: boot/grub.cfg
	mkdir -p out/iso/boot/grub
	cp boot/grub.cfg out/iso/boot/grub/grub.cfg
