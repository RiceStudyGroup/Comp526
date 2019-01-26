#include "global.h"
/*
read the pipeline PR to the the operation 
place the results in the shawod pr[2]


from pr[1] to shadow pr[2]

*/

extern struct pipelineReg PR[];
extern struct pipelineReg SHADOW_PR[];

extern int isHALT;


int isBranchInstr(int control) {
    return ((control & 0x8) >> 3);
}

int branchCondition(int op) {
    switch (op) {
        case BNEZ:
            return (PR[1].operand1 != 0);
    }
}


void executestage() {
    while (!isHALT) {
        if (TRACE)
            printf("In EXECUTE Stage at time %2.0f Instruction: %x\n", GetSimTime(), PR[1].INSTRUCTION);
        do_execute();
        ProcessDelay(1.000);
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
        case BNEZ:
            result = (operand1 != 0) ? TRUE : FALSE;
            break;
    }

    SHADOW_PR[2] = PR[1];
    SHADOW_PR[2].result = result;
}

