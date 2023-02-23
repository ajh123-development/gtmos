mkfile_path:=$(abspath $(lastword $(MAKEFILE_LIST)))
current_dir:=$(patsubst %/,%,$(dir $(mkfile_path)))

ROOT_DIR:=${current_dir}
PWD=$(shell pwd)

DEFAULT_HOST=i686-elf
HOST=${DEFAULT_HOST}
HOSTARCH=i386

CFLAGS?=-O2 -g -fPIC
CPPFLAGS?=
LDFLAGS?=

# Configure the cross-compiler to use the desired system root.
SYSROOT=${ROOT_DIR}/sysroot

DESTDIR=${SYSROOT}
PREFIX=/usr
EXEC_PREFIX=${PREFIX}
BOOTDIR=${ROOT_DIR}/bootroot
LIBDIR=${EXEC_PREFIX}/lib
INCLUDEDIR=${PREFIX}/include

AR=${HOST}-ar
AS=${HOST}-as
CC=${HOST}-gcc
CXX=${HOST}-g++
ASM=nasm -f elf

CC:=${CC} --sysroot=${SYSROOT}
CXX:=${CXX} --sysroot=${SYSROOT} -fno-rtti -fno-exceptions
# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
ifneq (,$(findstring -elf,$(HOST)))
    CC:=${CC} -isystem=${INCLUDEDIR}
    CXX:=${CXX} -isystem=${INCLUDEDIR}
endif