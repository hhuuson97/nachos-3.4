#include "syscall.h"

char str[20], tmp[2];

int main() {
    OpenFileId file, voinuoc;
    int t = 0, ec, v1 = 0, v2 = 0, i;
    Wait("Voi Nuoc");
    file = Open("main.txt", 0);
    voinuoc = Open("voinuoc.txt", 0);
    while (Read(str, 1, voinuoc) > 0) {
        if ('0' <= str[0] && str[0] <= '9') {
            v1 = v1 * 10+ (int) str[0] - 48;
        }
        else break;
    }
    while (Read(str, 1, voinuoc) > 0) {
        if ('0' <= str[0] && str[0] <= '9') {
            v2 = v2 * 10+ (int) str[0] - 48;
        }
        else break;
    }
    while (Read(str, 1, file) > 0) {
        if ('0' <= str[0] && str[0] <= '9') {
            t = t * 10+ (int) str[0] - 48;
        }
        else break;
    }
    Close(file);
    Close(voinuoc);
    if (v1 > v2) {
        v2 += t;
        ec = 2;
    }
    else {
        v1 += t;
        ec = 1;
    }
    CreateFile("voinuoc.txt");
    voinuoc = Open("voinuoc.txt", 0);
    i = 0;
    do {
        str[i++] = '0' + v1 % 10;
        v1 /= 10;
    } while (v1 > 0);
    while (i > 0) {
        tmp[0] = str[--i];
        Write(tmp, 1, voinuoc);
    }
    Write(" ", 1, voinuoc);
    i = 0;
    do {
        str[i++] = '0' + v2 % 10;
        v2 /= 10;
    } while (v2 > 0);
    while (i > 0) {
        tmp[0] = str[--i];
        Write(tmp, 1, voinuoc);
    }
    Close(voinuoc);
    Signal("Voi Nuoc");
    Exit(ec);
}