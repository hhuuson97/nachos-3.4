#include "syscall.h"

char str[256];
char string[101];

int main()
{
    int leng;
    OpenFileId id;
    OpenFileId output;
    int i;
    PrintString("Nhap ten file: ");
    ReadString(string, 100);
    id = Open(string, 0);
    output = Open("stdout", 0);
    if (id != -1 && output != -1) {
        leng = Seek(-1, id);
        Seek(0, id);
        for (i = 0; i < leng; i++) {
            Read(str, 1, id);
            Write(str, 1, output);
        }
        if (id > 1) Close(id);
    }
    else PrintString("Error\n");
    Halt();
}
