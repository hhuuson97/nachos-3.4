#ifndef STABLE_H
#define STABLE_H
#include "synch.h"
#include "bitmap.h"
#define MAX_SEMAPHORE 10

class STable {
private:
    BitMap *bm;
    Semaphore *lockTab[MAX_SEMAPHORE];
public:
    STable();
    ~STable();
    int Create(char *name, int semval);
    int Wait(char *name);
    int Signal(char *name);
};
#endif