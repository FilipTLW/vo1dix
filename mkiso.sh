#!/usr/bin/env sh
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/vo1dix.kernel isodir/boot/vo1dix.kernel
cp grub/grub.cfg isodir/boot/grub/grub.cfg

mkdir -p out
grub-mkrescue -o out/vo1dix.iso isodir