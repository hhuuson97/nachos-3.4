#include "syscall.h"

int main() {
    int t = ReadInt();
    PrintInt(t);
    Halt();
}