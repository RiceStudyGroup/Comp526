#include  "global.h"
/*
this stage, performs load and store inst. 

read from the memory and write to memory


*/


extern struct pipelineReg PR[];
extern struct pipelineReg SHADOW_PR[];
extern int MEM[];

extern unsigned nextPC;
extern int updatePC;
extern int isHALT;

void memstage() {
    while (!isHALT) {
        if (TRACE)
            printf("In MEM Stage at time %2.0f Instruction: %x\n", GetSimTime(), PR[2].INSTRUCTION);
        do_mem();
        ProcessDelay(1.000);
    }
}

do_mem() {
    unsigned address = PR[2].result;

    int data = PR[2].operand2;

    updatePC = FALSE;

    // PR and SHADOW_PR 's size are both 5, 
    SHADOW_PR[3] = PR[2];

    if (PR[2].control & 0x2)  // LOAD;
        SHADOW_PR[3].result = MEM[address];

    if (PR[2].control & 0x4) // STORE;
        MEM[address] = data;

    if (PR[2].control & 0x8) { // BNEZ
        if (PR[2].result) {
            updatePC = TRUE;
            nextPC = PR[2].PC4 + PR[2].offset;
        }
    }


}


