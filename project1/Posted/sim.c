#include "global.h"
#include <stdlib.h>
// sim means simulate?

extern void displayRegisterFile();

extern void displayMemory();

extern void reset();

extern void fetchstage(), issuestage(), executestage(), memstage(), writestage(), syncstage();

PROCESS *fetch, *issue, *execute, *mem, *write, *sync;

unsigned MEM[MEM_SIZE];
unsigned insMEM[INSTR_MEM_SIZE];
unsigned REG_FILE[NUM_REGISTERS];

struct pipelineReg PR[PIPELINE_REG];
struct pipelineReg SHADOW_PR[PIPELINE_REG];
struct pipelineReg dummy;

unsigned PC;
unsigned SHADOW_PC;
unsigned nextPC;
int updatePC;

int isHALT;
int stallIF;

unsigned INSTRUCTION;
double timeInsCompleted;
int numInsCompleted;

void UserMain(int argc, char *argv[])
{
    int i, j;

    reset();

    // Create a process for each pipeline stage

    write = NewProcess("write", writestage, 0);
    ActivitySetArg(write, NULL, 1);
    ActivitySchedTime(write, 0.000000, INDEPENDENT);

    mem = NewProcess("mem", memstage, 0);
    ActivitySetArg(mem, NULL, 1);
    ActivitySchedTime(mem, 0.000000, INDEPENDENT);

    execute = NewProcess("execute", executestage, 0);
    ActivitySetArg(execute, NULL, 1);
    ActivitySchedTime(execute, 0.000001, INDEPENDENT);

    issue = NewProcess("issue", issuestage, 0);
    ActivitySetArg(issue, NULL, 1);
    ActivitySchedTime(issue, 0.00003, INDEPENDENT);

    fetch = NewProcess("fetch", fetchstage, 0);
    ActivitySetArg(fetch, NULL, 1);
    ActivitySchedTime(fetch, 0.00004, INDEPENDENT);

    sync = NewProcess("sync", syncstage, 0);
    ActivitySetArg(sync, NULL, 1);
    ActivitySchedTime(sync, 0.00005, INDEPENDENT);

    printf("\n\n*******  CREATED ALL PROCESSES  **********\n\n");

    // Initialization is done, now start the simulation

    DriverRun(MAX_SIMULATION_TIME);
    printf("\n\n*********************************************************\n\n");
    printf("Simulation ended  at %3.0f\n", GetSimTime());
    printf("Execution completed at time  %5.2f\n", timeInsCompleted);
    printf("Number Instructions Executed  %d\n", numInsCompleted);

    displayRegisterFile();

    // Uncomment if you want to see destination array in Programs 2 and 3

    printf("\nFinal Destination Memory Array\n");
    displayMemory(BASE_ARRAY_DEST, NUM_ITERATIONS);
}
