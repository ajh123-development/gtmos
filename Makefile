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

build: headers
	mkdir -p ${SYSROOT}
	for dir in $(PROJECTS); do \
		"$(MAKE)" -C $$dir install; \
	done

headers:
	mkdir -p ${SYSROOT}
	for dir in $(PROJECTS); do \
		"$(MAKE)" -C $$dir install-headers; \
	done

clean:
	for dir in $(PROJECTS); do \
		"$(MAKE)" -C $$dir clean; \
	done
	rm -rf ${SYSROOT}
	rm -rf ${BOOTDIR}
	rm -rf ${ROOT_DIR}/isodir
	rm -rf ${ROOT_DIR}/gtmos.iso

run: iso
	qemu-system-x86_64 -M q35 -m 2G -cdrom ${ROOT_DIR}/gtmos.iso -boot d -serial stdio

run-uefi: ovmf-x64 iso
	qemu-system-x86_64 -M q35 -m 2G -bios ${ROOT_DIR}/ovmf-x64/OVMF.fd -cdrom ${ROOT_DIR}/gtmos.iso -boot d  -serial stdio

ovmf-x64:
	mkdir -p ${ROOT_DIR}/ovmf-x64
	cd ${ROOT_DIR}/ovmf-x64 && curl -o OVMF-X64.zip https://efi.akeo.ie/OVMF/OVMF-X64.zip && 7z x OVMF-X64.zip

limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1
	make -C limine

iso: limine build
	rm -rf ${ROOT_DIR}/iso_root
	mkdir -p ${ROOT_DIR}/iso_root
	cp ${BOOTDIR}/gtmos.elf \
		${BOOTDIR}/limine.cfg ${ROOT_DIR}/limine/limine.sys ${ROOT_DIR}/limine/limine-cd.bin ${ROOT_DIR}/limine/limine-cd-efi.bin ${ROOT_DIR}/iso_root/
	xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-cd-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		${ROOT_DIR}/iso_root -o ${ROOT_DIR}/gtmos.iso
	limine/limine-deploy ${ROOT_DIR}/gtmos.iso
	rm -rf ${ROOT_DIR}/iso_root