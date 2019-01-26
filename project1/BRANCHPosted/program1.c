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

    // Use your optimized code from PART 1
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
