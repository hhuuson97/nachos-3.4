#include "syscall.h"

char str[2];

int main() {
    SpaceId id;
    int ec = 0;
    Wait("Sinh Vien");
    id = Exec("test/voinuoc");
    ec = Join(id);
    Signal("Sinh Vien");
    Exit(ec);
}