#ifndef PTABLE_H
#define PTABLE_H
#include "bitmap.h"
#include "pcb.h"
#include "semaphore.h"

#define MAXPROCESS 10

class PTable {
private:
    BitMap *bm;
    PCB *pcb[MAXPROCESS];
    int psize;
    Semaphore *bmsem;
public:
    PTable();

    ~PTable();

    int ExecUpdate(char *name);

    int ExitUpdate(int ec); // return PID

    int JoinUpdate(int id);

    int GetFreeSlot();

    bool IsExist(int pid);

    void Remove(int pid);

    char *GetFileName(int id);
};
#endif