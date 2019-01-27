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
    insMEM[3] = 0X04401000;       // ADD   R2, R2, R0           sum = sum + R0;
    insMEM[4] = 0x14210001;       // ADDI  R1, R1, 1            R1 = R1 + 1;
    insMEM[5] = 0x2500FFE8;       // BNEZ  R8  -24  = 6 * 4 = 16 + 8 if (count != 0) goto top
    insMEM[6] = 0x00000000;       //  Do not remove. Needed to make HALT work correctly
    insMEM[9] = 0x28000000;       // HALT

    /*
                        0  1  2  3  4  5  6  7  8  9 10
    LOAD  R0,(R1)      0IF ID EX ME WB 
    ADDI  R8, R8, -1      1IF ID EX ME WB
    NOP                      2_  _  _  _  _
    ADD   R2, R2, R0            3IF ID EX ME WB
    ADDI  R1, R1, 1                4IF ID EX ME WB
    BNEZ  R8  -20                     5IF ID EX ME WB
    NOP                                  6_  _  _  _  _
    NOP                                     7_  _  _  _  _
    NOP                                        8_  _  _  _  _
    HALT 9

    After optimization

                        0  1  2  3  4  5  6  7  8  9 10
    ADDI  R8, R8, -1   0IF ID EX ME WB
    LOAD  R0,(R1)         1IF ID EX ME WB 
    ADDI  R1, R1, 1          2IF ID EX ME WB
    BNEZ  R8  -20               3IF ID EX ME WB
    ADD   R2, R2, R0               4IF ID EX ME WB
    NOP                               5_  _  _  _  _
    NOP                                  6_  _  _  _  _
    HALT 7


    for (i = 0; i < BASE_ARRAY_DEST; i++)
        MEM[i] = 500 + i;
    */

    /* After optimization */
    for (i = 0; i < INSTR_MEM_SIZE; i++)
        insMEM[i] = 0;

    insMEM[0] = 0x1508FFFF;       // ADDI  R8, R8, -1           count = count - 1;
    insMEM[1] = 0x10200000;       // LOAD  R0,(R1)       top:  R0 = MEM[R1];
    insMEM[2] = 0x14210001;       // ADDI  R1, R1, 1            R1 = R1 + 1;
    insMEM[3] = 0x2500FFF0;       // BNEZ  R8  -20              if (count != 0) goto top
    insMEM[4] = 0X04401000;       // ADD   R2, R2, R0           sum = sum + R0;
    insMEM[5] = 0x00000000;       //  Do not remove. Needed to make HALT work correctly
    insMEM[7] = 0x28000000;       // HALT
    
}


loadRegFile() {

    REG_FILE[0] = 0;
    REG_FILE[1] = BASE_ARRAY; // 0
    REG_FILE[2] = BASE_ARRAY_SRC1; // 0
    REG_FILE[3] = 1;
    REG_FILE[4] = BASE_ARRAY_SRC2; // 256 
    REG_FILE[5] = 0;
    REG_FILE[6] = BASE_ARRAY_DEST; // 512
    REG_FILE[7] = 0;
    REG_FILE[8] = NUM_ITERATIONS; // 100
    REG_FILE[9] = -1;
}

