# CERNEL
PoC kernel with stack support written in C.  

**Requirements:**  
`clang` (tested with version `13.0.1-3+b2`)  
`ld`

The point is to demonstrate that the stack can be setup and used without depending on an external assembler or inline assembly.  

This is demonstrated by calling the `kmain()` function from the entry function `start()`, then hopping back to `kmain()` using the `return` statement (`ret` instruction)  and landing on infinite loop `while(1);` (`jmp 0x10000c`) located in `start()`.  

> Written with [StackEdit](https://stackedit.io/).
