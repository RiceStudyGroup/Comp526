#include  "global.h"

/*
MEM: 
This stage performs Load and Store instructions. It reads the address from the 
result field of the pipeline register PR[2] and the data for a store from the operand2 
field (which will be the value of register rt) of PR[2], and performs the read (write) 
from (to) memory. For a LOAD, the value read from memory is placed in the shadow pipeline 
register SHADOW_PR[3].
*/

extern struct pipelineReg PR[];
extern struct pipelineReg SHADOW_PR[];
extern int MEM[];

extern void displayPipelineReg(int);

extern void displayShadowPipelineReg(int);

extern struct branchInfo memBranchInfo;
extern int branchTaken;
extern unsigned nextPC;
extern int updatePC;

int isHALT;

extern struct pipelineReg dummy;

void memstage() {
    while (!isHALT) {
        if (TRACE)
            printf("\nIn MEM Stage at time %2.0f  INSTRUCTION: %x\n", GetSimTime(), PR[2].INSTRUCTION);
        do_mem();
        ProcessDelay(1.000);
    }
}


handleSpeculativeBranch() {
    // If Branch Instruction set "isBranchInstrMem" in my SHADOW_PR.
    // If speculation is correct set "conditionMem" to TRUE in my SHADOW_PR; else set it FALSE.
    // Set "inlinePCMem" in my SHADOW_PR to the next inline instruction to be executed (if speculation s incorrect)
}


do_mem() {
    int address = PR[2].result;
    int data = PR[2].operand2;
    printf("PR[2].result :%d\n", PR[2].result);
    SHADOW_PR[3] = PR[2];

    updatePC = FALSE;

    if (PR[2].control & 0x2)  // LOAD;
        SHADOW_PR[3].result = MEM[address];

    if (PR[2].control & 0x4) // STORE;
        MEM[address] = data;

    if (PR[2].control & 0x8) // BNEZ
        handleSpeculativeBranch();
}
 




