#include "global.h"
/*
WRITE: This stage checks the pipeline register PR[3] to see if the instruction 
should write to a register (writeback flag) and if so updates the destination 
register with the result.
*/

extern unsigned REG_FILE[];
extern struct pipelineReg PR[];
extern struct pipelineReg SHADOW_PR[];


int isHALT;

void writestage() {
    int job_num;
    job_num = ActivityArgSize(ME) - 1;
    while (!isHALT) {
        if (TRACE) {
            printf("In WRITE Stage at time %2.0f  Instruction: %x\n", GetSimTime(), PR[3].INSTRUCTION);
        }
        do_write();
        ProcessDelay(1.000);
    }
}


do_write() {
    int destReg;

    SHADOW_PR[4] = PR[3];

    destReg = PR[3].destReg;
    if (PR[3].writeBack)
        REG_FILE[destReg] = PR[3].result;
}

