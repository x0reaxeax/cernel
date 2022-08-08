clang -m32 -c kernel.c -o kernel.o -fno-stack-check -fomit-frame-pointer -nostdlib -fno-stack-protector -ffreestanding
ld -o kernel -m elf_i386 -T link.ld kernel.o
