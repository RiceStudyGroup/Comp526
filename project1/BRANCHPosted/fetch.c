#include "global.h"

/**
Read an instruction from the Instruction Memory location pointed to by the program counter PC and update PC 
to the address of the next instruction to be executed. This is either the current PC value plus 4 or the target 
address of a branch. The stallIF signal will not be used in this assignment (1A).
*/

extern struct pipelineReg SHADOW_PR[]; // pr pipeline register
extern unsigned SHADOW_PC; // program counter
extern struct pipelineReg dummy;
extern unsigned insMEM[]; // instruct memory location


extern int stallIF;
extern int isHALT;

extern int updatePC;
extern unsigned nextPC;


// Output Signals for ISSUE stage
extern unsigned INSTRUCTION, PC4;
extern unsigned PC;

extern int numStallCycles;  // Statistics Counter



void fetchstage() {
    int job_num;
    job_num = ActivityArgSize(ME) - 1;

    while (!isHALT) {
        if (TRACE) // seems like trace means if you want it to print some logs.
            printf("In FETCH  Stage at time %2.0f  PC: %x\n", GetSimTime(), PC);
        do_fetch();
        ProcessDelay(1.0);
    }

}


handleBranchSpeculation() {
    // If  there is a  speculated branch that can be  resolved (recorded by Mem stage in its shadow PR)
    // Nullify incorrect instructions in the pipeline.
    // If speculation was incorrect, resume inline execution (recorded by Mem stage in its shadow PR)
    // TODO 

    // If there is a branch that is being issued:
    // If so, set PC to the target address (recorded by Issue stage in its Shadow PR)
}


do_fetch() {
    // how to write comment for a method in c? 
    updatePC = FALSE;

    INSTRUCTION = insMEM[PC / 4]; // where does these instruction from? 
    SHADOW_PR[0].INSTRUCTION = INSTRUCTION;
    SHADOW_PR[0].PC4 = PC + 4;

    handleBranchSpeculation();

    if (!stallIF)
        SHADOW_PC = (updatePC) ? nextPC : PC + 4;
}




