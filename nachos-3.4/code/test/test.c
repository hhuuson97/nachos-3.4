#include "syscall.h"

int check;

int main()
{
    int d;
    check = CreateFile("test.txt");
    if (check == 0) PrintString("Success\n");
    else PrintString("Failed\n");
    d = 0;
    while (Open("test.txt",0) > 0) d++;
    PrintInt(d);
    Halt();
}
