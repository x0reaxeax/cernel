#define textsect    __attribute__((section(".text")))
#define align(b)    __attribute__((aligned(b)))
#define naked       __attribute__((naked))

textsect align(4) int _multiboot_spec[3] = {
    0x1BADB002,     /* magic */
    0x00,           /* flags */
    0xe4524ffe      /* checksum */
};

void kmain(void);

void start(void) {
    /* 
       * the ESP register is set to 0x6f04 when leaving SeaBIOS.
       * by creating a local variable of 0xFFF06CD0 bytes in size,
       * the compiler will subtract this size from the ESP register,
       * causing a 32bit overflow, which will effectively set
       * the stack pointer to 0x100028 - 8 bytes from the top of our stack.
    */
    unsigned char _shift[0xFFF06CD0];
    kmain();
    while(1);
}

align(16) unsigned int stack[128] = {
    [127] = 0xffffffff  /* top of the stack - reserved 4 bytes */
};

void kmain(void) {
    /* return from kmain back to start to test the stack */
    return;
}
