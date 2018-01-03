#include "syscall.h"

int main() {
    char t = ReadChar();
    PrintChar(t);
    Halt();
}