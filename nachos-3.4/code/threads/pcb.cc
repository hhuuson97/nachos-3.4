#include "pcb.h"
#include "system.h"

PCB::PCB(int id) {
    joinsem = new Semaphore("join", 0);
    exitsem = new Semaphore("exit", 0);
    mutex = new Semaphore("mutex", 1);
    exitcode = 0;
    thread = NULL;
    parentID = id;
    numwait = 0;
    if (id == -1) {
        thread = currentThread;
        pid = 0;
    }
}

PCB::~PCB() {
    delete joinsem;
    delete exitsem;
    delete mutex;
    if (thread->space != NULL) delete thread->space;
}

void StartProcess_2(int pointer)
{
    Thread *thread = (Thread *) pointer;
    AddrSpace *space = new AddrSpace(thread->getName());

    thread->space = space;

    space->InitRegisters();		// set the initial register values
    space->RestoreState();		// load page table register

    scheduler->Run(currentThread);
    scheduler->Run(thread);
    machine->Run();
}

int PCB::Exec(char *filename, int pid) {
    mutex->P();
    if (filename == NULL || pid < 0 || thread != NULL) {
        mutex->V();
        return -1;
    }

    thread = new Thread(filename);
    if (thread == NULL) {
        printf("Not enough memory.\n");
        mutex->V();
        return -1;
    }

    thread->Fork(StartProcess_2, (int)thread);

    this->pid = pid;
    mutex->V();
    return pid;
}

int PCB::GetID() {return pid;}

int PCB::GetNumWait() {return numwait;}

void PCB::JoinWait() {joinsem->P();}

void PCB::ExitWait() {exitsem->P();}

void PCB::JoinRelease() {joinsem->V();}

void PCB::ExitRelease() {exitsem->V();}

void PCB::IncNumWait() {numwait++;}

void PCB::DecNumWait() {numwait--;}

void PCB::SetExitCode(int ec) {exitcode = ec;}

int PCB::GetExitCode() {return exitcode;}

char *PCB::GetFileName() {return thread->getName();}