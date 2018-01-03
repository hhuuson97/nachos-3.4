#include "syscall.h"

char string[101];
int check;

int main()
{
    PrintString("Nhap ten file: ");
    ReadString(string, 100);
    check = CreateFile(string);
    if (check == 0) PrintString("Success\n");
    else PrintString("Failed\n");
    Halt();
}
