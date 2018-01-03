#include "syscall.h"

char str[2], tmp[2];

int main() {
    int n = 0;
    int i;
    OpenFileId input = Open("input.txt", 0);
    OpenFileId file, output, voinuoc;
    SpaceId id;
    CreateFile("output.txt");
    output = Open("output.txt", 0);
    while (1) {
        Read(str, 1, input);
        if ('0' <= str[0] && str[0] <= '9')
            n = n * 10+ (int) str[0] - 48;
        else break;
    }
    CreateSemaphore("Sinh Vien", 1);
    CreateSemaphore("Voi Nuoc", 1);
    for (i = 0; i < n; i++) {
        CreateFile("voinuoc.txt");
        voinuoc = Open("voinuoc.txt", 0);
        Write("0 0", 3, voinuoc);
        Close(voinuoc);
        while (1) {
            int t = 0;
            int c, ec;
            CreateFile("main.txt");
            file = Open("main.txt", 0);
            while (1) {
                c = Read(str, 1, input);
                if (c <= 0) break;
                if ('0' <= str[0] && str[0] <= '9') {
                    t = t * 10+ (int) str[0] - 48;
                    Write(str, 1, file);
                }
                else break;
            }
            id = Exec("test/sinhvien");
            ec = Join(id);
            tmp[0] = '0' + ec;
            Write(tmp, 1, output);
            Close(file);
            if (str[0] != ' ' || c <= 0) break;
            Write(" ", 1, output);
        }
        Write("\n", 1, output);
    }
    Close(input);
    Close(output);
}