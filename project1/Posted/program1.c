#include "global.h"

extern unsigned MEM[];
extern unsigned insMEM[];


extern unsigned REG_FILE[];


loadProgram() {
    int i;

    for (i = 0; i < INSTR_MEM_SIZE; i++)  // Initialize all Instruction memory to NOPs
        insMEM[i] = 0;


    // PROGRAM  1
    // Accumulates the sum of an array of n consecutive memory words into Register R2
    // The base address of the array is in Register R1
    // R8 is initialized  with the number of iterations n : Default is set at 5

    insMEM[0] = 0x10200000;       // LOAD  R0,(R1)       top:  R0 = MEM[R1];
    insMEM[1] = 0x1508FFFF;       // ADDI  R8, R8, -1           count = count - 1;
    insMEM[2] = 0X04401000;       // ADD   R2, R2, R0           sum = sum + R0;
    insMEM[3] = 0x14210001;       // ADDI  R1, R1, 1            R1 = R1 + 1;
    insMEM[4] = 0x2500FFE0;       // BNEZ  R8  -20              if (count != 0) goto top
    insMEM[5] = 0x00000000;       //  Do not remove. Needed to make HALT work correctly
    insMEM[6] = 0x28000000;       // HALT
}


loadRegFile() {

    REG_FILE[0] = 0;
    REG_FILE[1] = BASE_ARRAY;
    REG_FILE[2] = BASE_ARRAY_SRC1;
    REG_FILE[3] = 1;
    REG_FILE[4] = BASE_ARRAY_SRC2;
    REG_FILE[5] = 0;
    REG_FILE[6] = BASE_ARRAY_DEST;
    REG_FILE[7] = 0;
    REG_FILE[8] = NUM_ITERATIONS;
    REG_FILE[9] = -1;
}

