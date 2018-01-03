#include "syscall.h"

char str[256];

int
main()
{
    OpenFileId input = Open("stdin", 1);
    OpenFileId output = Open("stdout", 0);
    if (input != -1 && output != -1) {
        int leng = Read(str, 255, input);
        if (leng > 0) Write(str, leng, output);
    }
    Halt();
    /* not reached */
}
