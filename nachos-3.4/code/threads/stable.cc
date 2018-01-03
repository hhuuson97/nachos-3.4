#include "stable.h"

STable::STable() {
    bm = new BitMap(MAX_SEMAPHORE);
    for (int i = 0; i < MAX_SEMAPHORE; i++)
        lockTab[i] = NULL;
}

STable::~STable() {
    for (int i = 0; i < MAX_SEMAPHORE; i++)
        if (lockTab[i] != NULL) delete lockTab;
    delete bm;
}

int STable::Create(char *name, int semval) {
    for (int i = 0; i < MAX_SEMAPHORE; i++)
        if (lockTab[i] != NULL && strcmp(lockTab[i]->getName(), name) == 0)
            return -1;
    int i = bm->Find();
    if (i == -1) {
        return -1;
    }
    bm->Mark(i);
    lockTab[i] = new Semaphore(name, semval);
    return i;
}

int STable::Wait(char *name) {
    for (int i = 0; i < MAX_SEMAPHORE; i++)
        if (lockTab[i] != NULL && strcmp(lockTab[i]->getName(), name) == 0) {
            lockTab[i]->P();
            return 0;
        }
    return -1;
}

int STable::Signal(char *name) {
    for (int i = 0; i < MAX_SEMAPHORE; i++)
        if (lockTab[i] != NULL && strcmp(lockTab[i]->getName(), name) == 0) {
            lockTab[i]->V();
            return 0;
        }
    return -1;
}