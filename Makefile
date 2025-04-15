all: headers iso

run: all qemu

headers:
	. ./headers.sh

iso:
	. ./mkiso.sh

qemu:
	qemu-system-i386 out/vo1dix.iso

clean:
	. ./clean.sh