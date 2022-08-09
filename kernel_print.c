#define textsect    __attribute__((section(".text")))
#define align(b)    __attribute__((aligned(b)))
#define naked       __attribute__((naked))

textsect align(4) int _multiboot_spec[3] = {
    0x1BADB002,     /* magic */
    0x00,           /* flags */
    0xe4524ffe      /* checksum */
};

void kmain(void);
void clearscr(void);
void print(unsigned int line, char *msg, unsigned int len);

void start(void) {
    volatile char _shift[0xFFF06CD0];
    kmain();
    while(1);
}

align(16) unsigned int stack[128] = {
    [127] = 0xffffffff  /* top of the stack - reserved 4 bytes */
};

/* 
  * clang throws a fit about "undefined reference to `memcpy'",
  * even though we're `-ffreestanding` and `-nostdlib`, whatever..
*/
void memcpy(char *dest, const char *src, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        dest[i] = src[i];
    }
}

void kmain(void) {
    /* return from kmain back to start to test the stack */
    char msg[] = "SUPA 1337 K3RN3L TEST OMG";
    clearscr();
    print(0, msg, sizeof(msg));
    return;
}

void clearscr(void) {
    volatile char *vmem = (volatile char *) 0xb8000;
    for (unsigned int i = 0; i < (80*25*2);) {
        vmem[i++] = ' ';
        vmem[i++] = 0x4;
    }
}


void print(unsigned int line, char *msg, unsigned int len) {
    volatile char *vmem = (volatile char *) 0xb8000;
    unsigned int i = (line * 80 * 2);
    
    while (0 != (*msg)) {
        vmem[i++] = *(msg++);
        vmem[i++] = 0x4;
    }
}
