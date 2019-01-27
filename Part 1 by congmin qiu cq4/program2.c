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

    insMEM[0] = 0x14840001; //  ADDI R4, R4, 1   top1: index2++ 
    insMEM[3] = 0x10810000; //  LOAD R1, 0(R4)         element2 = MEM[index2]
    insMEM[4] = 0x14420001; //  ADDI R2, R2, 1         index1++
    insMEM[7] = 0x10400000; //  LOAD R0, 0(R2)         element1 = MEM[index1]
    insMEM[10] = 0x04012800; //  ADD R5, R0, R1         temp = element1 + element2
    insMEM[13] = 0x18C50000; //  STORE R5, 0(R6)        MEM[index3] = temp
    insMEM[14] = 0x14C60001; //  ADDI R6, R6, 1         index3++
    insMEM[15] = 0x1508FFFF; //  ADDI R8, R8, -1        count--
    insMEM[18] = 0x2500FFB4; //  BNEZ R8 -16*5 + 4 = -76 = 19 * 4          if (count != 0) goto top
    insMEM[19] = 0x00000000; //  NOP 
    insMEM[22] = 0x28000000; // HALT


    /*
         0  1  2  3   4  5
    ADDI0IF ID EX ME WB                            // ADDI R4, R4, 1
    NOP    1_  _  _  _  _       
    NOP       2_  _  _  _  _       
    Load         3IF ID EX ME WB                      // LOAD R1, 0(R4) 
    ADDI            4IF ID EX ME WB                   //  ADDI R2, R2, 1  
    NOP                5_  _  _  _  _
    NOP                   6_  _  _  _  _
    Load                     7IF ID EX ME WB             //  LOAD R0, 0(R2)
    NOP                         8_  _  _  _  _
    NOP                            9_  _  _  _  _
    ADD                              10IF ID EX MEM WB       //  ADD R5, R0, R1
    NOP                                 11_  _  _  _  _
    NOP                                    12_  _  _  _  _
    STORE R5, 0(R6)                           13IF ID EX MEM WB   
    ADDI R6, R6, 1                               14IF ID EX MEM WB  
    ADDI R8, R8, -1                                 15IF ID EX MEM WB 
    NOP                                                 16
    NOP                                                    17
    BNEZ R8 -32 + 4 = -36                                    18IF ID EX MEM WB  // 18 * 4 = 72 = 16*6
    NOP                                                         19
    NOP                                                             20
    NOP                                                                 21
    HALT                                                                    22 

    * After optimization *
    
        0  1  2  3   4  5
    ADDI0IF ID EX ME WB                             // ADDI R4, R4, 1
    ADDI   1IF ID EX ME WB                          // ADDI R2, R2, 1  
    ADDI      2IF ID EX ME WB                       // R8, R8, -1  
    Load         3IF ID EX ME WB                    // LOAD R1, 0(R4) 
    Load            4IF ID EX ME WB                 // LOAD R0, 0(R2)
    NOP                5_  _  _  _  _
    NOP                   6_  _  _  _  _
    ADD                      7IF ID EX ME WB        //  ADD R5, R0, R1
    BNEZ R8 -32 + 4 = -36       8IF ID EX ME WB     // 18 * 4 = 72 = 16*6
    ADDI R6, R6, 1                 9IF ID EX ME WB  
    STORE R5, 0(R6)                  10IF ID EX ME WB   
    HALT                                11
    */

    /* After optimization */
    for (i = 0; i < INSTR_MEM_SIZE; i++)
        insMEM[i] = 0;

    insMEM[0] = 0x14840001; //  ADDI R4, R4, 1   top1: index2++ 
    insMEM[1] = 0x14420001; //  ADDI R2, R2, 1         index1++
    insMEM[2] = 0x1508FFFF; //  ADDI R8, R8, -1        count--
    insMEM[3] = 0x10810000; //  LOAD R1, 0(R4)         element2 = MEM[index2]
    insMEM[4] = 0x10400000; //  LOAD R0, 0(R2)         element1 = MEM[index1]
    insMEM[7] = 0x04012800; //  ADD R5, R0, R1         temp = element1 + element2
    insMEM[8] = 0x2500FFDC; //  BNEZ R8 -16*2 + 4 = -36 = 9 * 4          if (count != 0) goto top
    insMEM[9] = 0x14C60001; //  ADDI R6, R6, 1         index3++
    insMEM[10] = 0x18C50000; //  STORE R5, 0(R6)        MEM[index3] = temp
    insMEM[11] = 0x00000000; //  NOP 
    insMEM[12] = 0x28000000; // HALT

}


loadRegFile() {

    REG_FILE[0] = 0;
    REG_FILE[1] = BASE_ARRAY;
    //REG_FILE[2] = BASE_ARRAY_SRC1;  
    REG_FILE[2] = BASE_ARRAY_SRC1 - 1;
    REG_FILE[3] = 1;
    //REG_FILE[4] = BASE_ARRAY_SRC2;
    REG_FILE[4] = BASE_ARRAY_SRC2 - 1;
    REG_FILE[5] = 0;
    REG_FILE[6] = BASE_ARRAY_DEST;
    REG_FILE[7] = 0;
    REG_FILE[8] = NUM_ITERATIONS;
    REG_FILE[9] = -1;
}

