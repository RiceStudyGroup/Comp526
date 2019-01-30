#include "global.h"
extern unsigned  MEM[];
extern unsigned insMEM[];


extern unsigned REG_FILE[];


loadProgram() {
  int i;

  for (i=0; i < INSTR_MEM_SIZE; i++) 
      insMEM[i] =  0;  
  

  

  // PROGRAM  3
  // Accumulates the sum of an array of n consecutive memory words into Register R2
  // The base address of the array is in Register R1
  // Initialize R8 with the number of iterations n : Default is set at 20
    
  
  insMEM[0] = 0x10200000;       // LD   R0, 0(R1)         COPY: R0 = MEM[index];
  insMEM[1] = 0x18200200;        // STORE  R0, 512(R1)          MEM[index+512] = R0
  insMEM[2] = 0x1508FFFF;       // ADDI  R8, R8, -1             count = count - 1;
  insMEM[3] = 0x14210001;       // ADDI  R1, R1, 1              index  = index + 1;
  insMEM[4] = 0x2500FFEC;       // BNEZ R8  -20                 if (count != 0) goto COPY 
  insMEM[5] = 0x00000000;       //NOP   
  insMEM[8] = 0x28000000;       //HALT 

/*
  for (i = 0; i < BASE_ARRAY_DEST; i++)
    // base array dest = 512
    // so base[0] = 500
    // base[512] = 1012
    0   1   2   3       256 257 ... 
    500 501 502 ...     756 757 ... 
    MEM[i] = 500 + i;

    255 -> 256 -> 257 ,,, 
    -1 -> 0 -> 1 ,,, 

    */
}



loadRegFile() {
  
  REG_FILE[0] = 0;  
  REG_FILE[1] = BASE_ARRAY;   // 0
  REG_FILE[2] = BASE_ARRAY_SRC1;   // 0
      //   REG_FILE[2] = BASE_ARRAY_SRC1 - 1;  
  REG_FILE[3] = 1;    
  REG_FILE[4] = BASE_ARRAY_SRC2;   // 256
      //  REG_FILE[4] = BASE_ARRAY_SRC2 - 1;  
  REG_FILE[5] = 0;  
  REG_FILE[6] = BASE_ARRAY_DEST;  // 512
  REG_FILE[7] = 0;  
  REG_FILE[8] = NUM_ITERATIONS; // 100
  REG_FILE[9] = -1;
}

