#include "global.h"
/*
fetch is the first stage.
1. read an instruction from instruct memory according to the 
program counter
2. update the pc to the next instruction 
the next instruction is either the current plus 4 
or the target address of a branch. 



*/
// 2. “extern” keyword is used to extend the visibility of variables/functions().
extern struct pipelineReg SHADOW_PR[];
// the reason we used a shadow here is try to micic
//
extern unsigned SHADOW_PC;
extern unsigned insMEM[]; // Instruction Memory

extern int stallIF;
extern int isHALT;

extern int updatePC;
extern unsigned nextPC;

// Output Signals for ISSUE stage
extern unsigned INSTRUCTION, PC4;
extern unsigned PC;

extern int numStallCycles; // Statistics Counter

void fetchstage()
{
    int job_num;
    job_num = ActivityArgSize(ME) - 1;
    // ActivityArgSize method will Returns the size of an argument
    // return the size of ME, what is ME here?
    //

    while (!isHALT)
    {
        if (TRACE)
            printf("In FETCH  Stage at time %2.0f  PC: %x\n", GetSimTime(), PC);
        do_fetch();
        ProcessDelay(1.0);
        //Suspends the current process for a time period
    }
}

/**
 * 
 * 
 */
do_fetch()
{

    INSTRUCTION = insMEM[PC / 4];

    SHADOW_PR[0].INSTRUCTION = INSTRUCTION;
    SHADOW_PR[0].PC4 = PC + 4;

    if (!stallIF) // what does stall if mean? 
        SHADOW_PC = (updatePC) ? nextPC : PC + 4;
}
