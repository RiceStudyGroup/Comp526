#include "global.h"
extern unsigned  MEM[];
extern unsigned insMEM[];


extern unsigned REG_FILE[];


loadProgram() {
  int i;

  for (i=0; i < INSTR_MEM_SIZE; i++) 
      insMEM[i] =  0;  
  

    
  // PROGRAM  2
  // Adds two arrays elemen-by-element and stores the result in a third array
  //  The base addresses-1 of the source arrays are in Registers R2 and R4
  // The base address  of the destination array is R6
  // Initialize R8 with the number of iterations: Default is set at 5
  

  insMEM[0] = 0x14840001;       // ADDI  R4, R4, 1          top:  index1++
  insMEM[1] = 0x10810000;       // LOAD R1, 0(R4)                  val1 = MEM[index1]
  insMEM[2] = 0x14420001;       // ADDI  R2, R2, 1                 index2++
  insMEM[3] = 0x10400000;       // LOAD R0, 0(R2)                  val2 = MEM[index2]
  insMEM[4] = 0x04012800;       // ADD R5, R0, R1                  sum = val1+val2
  insMEM[5] = 0x18C50000;       // STORE R5, 0(R6)                 MEM[index3] = sum
  insMEM[6] = 0x14C60001;       // ADDI  R6, R6, 1                 index3++
  insMEM[7] = 0x1508FFFF;       // ADDI  R8, R8, -1                count = count-1; 
  insMEM[8] = 0x2500FFDC;       // BNEZ R8  -36                    if (count != 0) goto top   
  insMEM[9] = 0x00000000;       //NOP   
  insMEM[10] = 0x28000000;       //HALT 
}



loadRegFile() {
  
  REG_FILE[0] = 0;  
  REG_FILE[1] = BASE_ARRAY;  
  //              REG_FILE[2] = BASE_ARRAY_SRC1; 
  REG_FILE[2] = BASE_ARRAY_SRC1 - 1;  
  REG_FILE[3] = 1;    
  //              REG_FILE[4] = BASE_ARRAY_SRC2;  
  REG_FILE[4] = BASE_ARRAY_SRC2 - 1;  
  REG_FILE[5] = 0;  
  REG_FILE[6] = BASE_ARRAY_DEST;  
  REG_FILE[7] = 0;  
  REG_FILE[8] = NUM_ITERATIONS;
  REG_FILE[9] = -1;
}

