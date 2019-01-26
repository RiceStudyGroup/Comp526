#include "global.h"

extern unsigned MEM[];
extern unsigned insMEM[];


extern unsigned REG_FILE[];


loadProgram() {
    int i;

    for (i = 0; i < INSTR_MEM_SIZE; i++)
        insMEM[i] = 0;



    // PROGRAM  2
    // Adds two arrays elemen-by-element and stores the result in a third array
    //  The base addresses of the source arrays are in Registers R2 and R4
    // The base address  of the destination array is R6
    // R8 is initialized with the number of iterations: Default is set at 5


    // Use your optimized program from PART 1
    // Choose correct initialization for REG[2] and REG[4] in loadRegFile below.
}


loadRegFile() {

    REG_FILE[0] = 0;
    REG_FILE[1] = BASE_ARRAY;
    //      REG_FILE[2] = BASE_ARRAY_SRC1;  
    //        REG_FILE[2] = BASE_ARRAY_SRC1 - 1;  
    REG_FILE[3] = 1;
    //  REG_FILE[4] = BASE_ARRAY_SRC2;  
    //     REG_FILE[4] = BASE_ARRAY_SRC2 - 1;  
    REG_FILE[5] = 0;
    REG_FILE[6] = BASE_ARRAY_DEST;
    REG_FILE[7] = 0;
    REG_FILE[8] = NUM_ITERATIONS;
    REG_FILE[9] = -1;
}

