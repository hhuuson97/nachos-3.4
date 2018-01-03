#include "syscall.h"

char str[256];
char string[101];

int main()
{
    int leng;
    OpenFileId input;
    OpenFileId output;
    int i;
    PrintString("Nhap ten file nguon: ");
    ReadString(string, 100);
    input = Open(string, 0);
    PrintString("Nhap ten file dich: ");
    ReadString(string, 100);
    CreateFile(string);
    output = Open(string, 0);
    if (input != -1 && output != -1) {
        leng = Seek(-1, input);
        Seek(0, input);
        for (i = 0; i < leng; i++) {
            Read(str, 1, input);
            Write(str, 1, output);
        }
        if (input > 1) Close(input);
        if (output > 1) Close(output);
        PrintString("Success\n");
    }
    else PrintString("Error\n");
    Halt();
}
