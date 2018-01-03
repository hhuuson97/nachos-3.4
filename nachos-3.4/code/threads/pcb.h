#ifndef PCB_H
#define PCB_H
#include "thread.h"
#include "synch.h"
class PCB{
private:
    Semaphore *joinsem;
    Semaphore *exitsem;
    Semaphore *mutex;
    int exitcode;
    Thread *thread;
    int pid;
    int numwait;

public:
    int parentID;
    PCB(int id); 
    ~PCB(); 
    int Exec(char *filename, int pid);
    int GetID();
    int GetNumWait();
    void JoinWait();
    void ExitWait();
    void JoinRelease();
    void ExitRelease();
    void IncNumWait();
    void DecNumWait();
    void SetExitCode(int ec);
    int GetExitCode();
    char *GetFileName();
};
#endif