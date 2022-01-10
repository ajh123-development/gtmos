qemu-system-x86_64 -s -kernel kernel/duckk32 -append "" -drive file=gtmos.img,cache=directsync,format=raw,id=disk,if=ide -m 512M -serial stdio
