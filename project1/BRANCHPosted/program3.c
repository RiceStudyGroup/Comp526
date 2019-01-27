#include "global.h"

extern unsigned MEM[];
extern unsigned insMEM[];


extern unsigned REG_FILE[];


loadProgram() {
    int i;

    for (i = 0; i < INSTR_MEM_SIZE; i++)
        insMEM[i] = 0;




    // PROGRAM  3
    // Accumulates the sum of an array of n consecutive memory words into Register R2
    // The base address of the array is in Register R1
    // Initialize R8 with the number of iterations n : Default is set at 20



    insMEM[0] = 0x1508FFFF;       // ADDI  R8, R8, -1             count--
    insMEM[1] = 0x10200000;       // LD   R0, 0(R1)         COPY: value = MEM[index]
    insMEM[2] = 0x14210001;       // ADDI  R1, R1, 1              index++
    insMEM[3] = 0x2500FFF0;       // BNEZ R8  -20   (3+1)*4 = 16  if (count != 0) goto COPY
    insMEM[4] = 0x18200200;       // STORE  R0, 512(R1)           MEM[index+512] = value
    insMEM[7] = 0x28000000;       // HALT
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

