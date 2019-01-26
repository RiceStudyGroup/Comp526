#include "global.h"

extern unsigned MEM[];

extern unsigned insMEM[];


extern unsigned REG_FILE[];


loadProgram() {
    int i;

    for (i = 0; i < INSTR_MEM_SIZE; i++){

        insMEM[i] = 0;


    }






    insMEM[2] = 0x1508FFFF;      
    
    insMEM[21] = 0x2500FFEC;       
    
    
    
    insMEM[5] = 0x00000000;      
    

    insMEM[6] = 0x28000000;      
    

}


loadRegFile() {

    REG_FILE[0] = 0;

    REG_FILE[1] = 0;
    
    REG_FILE[2] = 0;
    
    REG_FILE[3] = 0;
    
    REG_FILE[4] = 0;
    
    REG_FILE[5] = 0;
    
    REG_FILE[6] = 0;
    
    REG_FILE[7] = 0;
    
    REG_FILE[8] = 100;
    
    REG_FILE[9] = 0;
}

