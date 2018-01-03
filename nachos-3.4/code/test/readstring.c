#include "syscall.h"

char string[256];

int main() {
    ReadString(string, 255);
    PrintString(string);
    Halt();
}