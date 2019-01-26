#include "global.h"
/*
EXECUTE: 
The execute stage reads the pipeline register PR[1] to find the 
operation it needs to perform and the operands it needs. It performs the 
requested operation and places the results in the Shadow Pipeline Register 
SHADOW_PR[2].
*/
extern struct pipelineReg PR[];
//External variables are also known as global variables
// what is pipeline reg? 
extern struct pipelineReg SHADOW_PR[];

extern void displayPipelineReg(int);

extern void displaySHadowPipelineReg(int);

extern int isHALT;

void executestage() {
    while (!isHALT) {
        if (TRACE) // what is trace here? // a global variable from global.h
            printf("\nIn EXECUTE Stage at time %2.0f INSTRUCTION: %x\n", GetSimTime(), PR[1].INSTRUCTION);
            // /* Returns the current simulation time                 */
        do_execute();
        ProcessDelay(1.000);
    }
}


int isBranchInstr(int control) {
    return ((control & 0x8) >> 3);
}

int branchCondition(int op) {
    switch (op) {
        case BNEZ:
            return (PR[1].operand1 != 0);
    }
}

do_execute() {
    int operation;
    int operand1, operand2;
    int result;
    int offset;
    int control;

    operand1 = PR[1].operand1;
    operand2 = PR[1].operand2;
    operation = PR[1].opCode;
    offset = PR[1].offset;
    control = PR[1].control;


    switch (operation) {
        case ADD:
            result = operand1 + operand2;
            break;
        case ADDI:
            result = operand1 + offset;
            break;
        case LOAD:
            result = operand1 + offset;
            break;
        case STORE:
            result = operand1 + offset;
            break;
        case BNEZ: // BNEZ that takes the branch if the value in the specified register is non-zero.
        // if operand1 is not 0, return true else, false
            result = (operand1 != 0) ? TRUE : FALSE;
            break;
    }

    SHADOW_PR[2] = PR[1];
    SHADOW_PR[2].result = result;
}


