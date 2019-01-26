#include "global.h"

extern unsigned MEM[];
extern unsigned insMEM[];


extern unsigned REG_FILE[];
extern struct pipelineReg PR[];
extern struct pipelineReg SHADOW_PR[];
extern struct pipelineReg dummy;

extern unsigned PC;
extern unsigned nextPC;
extern unsigned stallIF;
extern int isHALT;
extern unsigned INSTRUCTION;
extern int numInsCompleted;
extern int updatePC;


void displayPipelineReg(int reg) {
    printf("INSTRUCTION = %x\n", PR[reg].INSTRUCTION);
    printf("OPCODE = %x\n", PR[reg].opCode);
    printf("OFFSET = %x\n", PR[reg].offset);

    printf("srcReg1: %d  srcReg2: %d  destReg: %d\n", PR[reg].srcReg1, PR[reg].srcReg2, PR[reg].destReg);
    printf("OPRAND1: %d  OPERAND2: %d  RESULT: %d\n", PR[reg].operand1, PR[reg].operand2, PR[reg].result);


    printf("writeBack = %d\n", PR[reg].writeBack);
    printf("PC4 = %d\n", PR[reg].PC4);
}


void reset() {
    int i;

    // Initialize Data Memory
    for (i = 0; i < BASE_ARRAY_DEST; i++)
        MEM[i] = 500 + i;

    // Initialize Registers
    for (i = 0; i < NUM_REGISTERS; i++) {
        REG_FILE[i] = 0;
    }

    for (i = 0; i < PIPELINE_REG; i++) {

        PR[i].INSTRUCTION = 0;
        PR[i].opCode = 0;
        PR[i].offset = 0;
        PR[i].srcReg1 = 0;
        PR[i].srcReg2 = 0;
        PR[i].operand1 = 0;
        PR[i].operand2 = 0;
        PR[i].destReg = 0;
        PR[i].result = 0;
        PR[i].writeBack = 0;
        PR[i].PC4 = 0;

        SHADOW_PR[i].INSTRUCTION = 0;
        SHADOW_PR[i].opCode = 0;
        SHADOW_PR[i].offset = 0;
        SHADOW_PR[i].srcReg1 = 0;
        SHADOW_PR[i].srcReg2 = 0;
        SHADOW_PR[i].operand1 = 0;
        SHADOW_PR[i].operand2 = 0;
        SHADOW_PR[i].destReg = 0;
        SHADOW_PR[i].result = 0;
        SHADOW_PR[i].writeBack = 0;
        SHADOW_PR[i].PC4 = 0;
    }


    dummy.INSTRUCTION = 0;
    dummy.opCode = 0;
    dummy.offset = 0;
    dummy.srcReg1 = 0;
    dummy.srcReg2 = 0;
    dummy.operand1 = 0;
    dummy.operand2 = 0;
    dummy.destReg = 0;
    dummy.result = 0;
    dummy.writeBack = 0;
    dummy.PC4 = 0;


    PC = 0;
    nextPC = 0;
    updatePC = FALSE;
    stallIF = FALSE;
    isHALT = FALSE;
    INSTRUCTION = NOP;
    numInsCompleted = 0;

    loadRegFile();
    loadProgram();
}


void displayRegisterFile() {
    int i, j;

    for (i = 0; i < NUM_REGISTERS / 4; i++) {
        for (j = 0; j < 4; j++)
            printf("REG[%d] : %d\t", i * 4 + j, REG_FILE[i * 4 + j]);
        printf("\n");
    }
}


void displayMemory(int startAddress, int num) {
    int i;
    for (i = startAddress; i < startAddress + num; i++)
        printf("MEM[%d]: %d\n", i, MEM[i]);
}
