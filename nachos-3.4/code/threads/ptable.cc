#include "ptable.h"
#include "system.h"

PTable::PTable() {
    bm = new BitMap(MAXPROCESS);
    bmsem = new Semaphore("Bitmap semaphore", 1);
    for (int i = 0; i < MAXPROCESS; i++)
        pcb[i] = NULL;
    pcb[0] = new PCB(-1);
    bm->Mark(0);
}

PTable::~PTable() {
    for (int i = 0; i < MAXPROCESS; i++)
        if (pcb[i] != NULL) delete pcb[i];
    delete bm;
    delete bmsem;
}

int PTable::ExecUpdate(char *name) {
    bmsem->P();

    if (name == NULL) {
        bmsem->V();
        return -1;
    }

    OpenFile *executable = fileSystem->Open(name);
    
    if (executable == NULL) {
        bmsem->V();
        return -1;
    }
    delete executable;

    if (strcmp(currentThread->getName(), name) == 0) {
        bmsem->V();
        return -1;
    }

    int pid = bm->Find();
    if (pid == -1) {
        bmsem->V();
        return -1;
    }
    int currentID = -1;
    for (int i = 0; i < MAXPROCESS; i++)
        if (pcb[i] != NULL && strcmp(currentThread->getName(), pcb[i]->GetFileName()) == 0)
            currentID = pcb[i]->GetID();
    if (currentID == -1) {
        bmsem->V();
        return -1;
    }
    pcb[pid] = new PCB(currentID);
    bm->Mark(pid);
    int status = pcb[pid]->Exec(name, pid);
    if (status == -1) {
        bm->Clear(pid);
        delete pcb[pid];
        bmsem->V();
        return -1;
    }
        
    bmsem->V();
    return pid;
}

int PTable::ExitUpdate(int ec) {
    int index = -1;
    for (int i = 0; i < MAXPROCESS; i++)
        if (pcb[i] != NULL && strcmp(currentThread->getName(), pcb[i]->GetFileName()) == 0)
            index = i;
    if (index == -1) return -1;
    int pid = pcb[index]->GetID();
    if (pid == 0) {
        interrupt->Halt();
        return 0;
    }
    int parentid = pcb[index]->parentID;
    pcb[index]->SetExitCode(ec);
    pcb[parentid]->JoinRelease();
    pcb[index]->ExitWait();
    Remove(pid);
    currentThread->Finish();
    return pid;
}

int PTable::JoinUpdate(int id) {
    if (id < 0 || id >= MAXPROCESS)
        return -1;
    int currentID = -1;
    for (int i = 0; i < MAXPROCESS; i++)
        if (pcb[i] != NULL && strcmp(currentThread->getName(), pcb[i]->GetFileName()) == 0)
            currentID = pcb[i]->GetID();
    if (pcb[id] == NULL || pcb[id]->parentID != currentID)
        return -1;
    pcb[currentID]->IncNumWait();
    pcb[currentID]->JoinWait();
    int ec = pcb[id]->GetExitCode();
    pcb[currentID]->DecNumWait();
    pcb[id]->ExitRelease();
    return ec;
}

int PTable::GetFreeSlot() {
    return bm->Find();
}

bool PTable::IsExist(int pid) {
    if (pid < 0 || pid >= MAXPROCESS || pcb[pid] == NULL)
        return false;
    return true;
}

void PTable::Remove(int pid) {
    if (pid < 0 || pid >= MAXPROCESS || pcb[pid] == NULL)
        return;
    delete pcb[pid];
    pcb[pid] = NULL;
    bm->Clear(pid);
}

char *PTable::GetFileName(int id) {
    if (id < 0 || id >= MAXPROCESS || pcb[id] == NULL)
        return NULL;
    return pcb[id]->GetFileName();
}