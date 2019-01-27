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

    /* Before optimization */
    insMEM[0] = 0x10200000;        // LD   R0, 0(R1)         COPY: value = MEM[index]
    insMEM[3] = 0x18200200;        // STORE  R0, 512(R1)           MEM[index+512] = value
    insMEM[4] = 0x1508FFFF;       // ADDI  R8, R8, -1              count--
    insMEM[5] = 0x14210001;       // ADDI  R1, R1, 1               index++
    insMEM[7] = 0x2500FFE0;       // BNEZ R8  -20   (7+1)*4 = 32                if (count != 0) goto COPY
    insMEM[8] = 0x00000000;       // NOP
    insMEM[11] = 0x28000000;       // HALT
    /*
                            0  1  2  3  4  5
    LD      R0, 0(R1)      0IF ID EX ME WB   
    NOP                       1_  _  _  |  _
    NOP                          2_  _  |  _  _ 
    STORE   R0, 512(R1)             3IF ID EX ME WB   
    ADDI    R8, R8, -1                 4IF ID EX ME WB 
    ADDI    R1, R1, 1                     5IF ID EX ME WB 
    NOP                                             |
    BNEZ    R8  -20                             7IF ID EX ME WB 
    NOP 8
    NOP 9
    NOP 10
    HALT 11

                                0  1  2  3  4  5
    ADDI    R8, R8, -1         0IF ID EX ME WB 
    LD      R0, 0(R1)             1IF ID EX ME WB  
    ADDI    R1, R1, 1                2IF ID EX ME WB 
    BNEZ    R8  -20                     3IF ID EX ME WB 
    STORE   R0, 512(R1)                    4IF ID EX ME WB   
    NOP   5                                     
    NOP   6
    HALT  7
    */

    /* After optimization */
    for (i = 0; i < INSTR_MEM_SIZE; i++)
        insMEM[i] = 0;

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

