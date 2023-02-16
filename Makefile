include ./variables.mk

SYSTEM_HEADER_PROJECTS=libc kernel
PROJECTS=libc kernel

config_test:
	@echo DEFAULT_HOST = ${DEFAULT_HOST}
	@echo SYSTEM_HEADER_PROJECTS = ${SYSTEM_HEADER_PROJECTS}
	@echo PROJECTS = ${PROJECTS}
	@echo HOSTARCH = ${HOSTARCH}
	@echo HOST = ${HOST}
	@echo AR = ${AR}
	@echo AS = ${AS}
	@echo CC = ${CC}
	@echo PREFIX = ${PREFIX}
	@echo EXEC_PREFIX = ${EXEC_PREFIX}
	@echo BOOTDIR = ${BOOTDIR}
	@echo LIBDIR = ${LIBDIR}
	@echo INCLUDEDIR = ${INCLUDEDIR}
	@echo CFLAGS = ${CFLAGS}
	@echo PWD = ${PWD}
	@echo ROOT_DIR = ${ROOT_DIR}

.PHONY : all
all: headers
	mkdir -p ${SYSROOT}
	for dir in $(PROJECTS); do \
		$(MAKE) -C $$dir install; \
	done

headers:
	mkdir -p ${SYSROOT}
	for dir in $(PROJECTS); do \
		$(MAKE) -C $$dir install-headers; \
	done

clean:
	for dir in $(PROJECTS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -rf ${SYSROOT}
	rm -rf ${ROOT_DIR}/isodir
	rm -rf ${ROOT_DIR}/gtmos.iso

qemu: iso
	qemu-system-${HOSTARCH} -cdrom ${ROOT_DIR}/gtmos.iso -serial stdio

.ONESHELL:
iso: all
	mkdir -p isodir
	mkdir -p isodir/boot
	mkdir -p isodir/boot/grub

	cp ${SYSROOT}/boot/gtmos.kernel ${ROOT_DIR}/isodir/boot/gtmos.kernel

	cat > ${ROOT_DIR}/isodir/boot/grub/grub.cfg << EOF
		menuentry "gtmos" {
			multiboot /boot/gtmos.kernel
		}
	EOF

	grub-mkrescue -o gtmos.iso isodir
