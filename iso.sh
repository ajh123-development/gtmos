#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/gtmos.kernel isodir/boot/gtmos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "gtmos" {
	multiboot /boot/gtmos.kernel
}
EOF
grub-mkrescue -o gtmos.iso isodir
