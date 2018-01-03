#include "syscall.h"

int main() {
    unsigned char c = (unsigned char)(0);
    while (c<=(unsigned char)255) {
        PrintChar(c);
        PrintChar(' ');
        PrintInt((int)c);
        PrintChar('\n');
        if (c==(unsigned char)255) break;
        c++;
    }
    Halt();
}