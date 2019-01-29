#include "global.h"

extern struct  pipelineReg   SHADOW_PR[];



extern unsigned  PC;  
extern unsigned SHADOW_PC;
extern unsigned insMEM[];  

extern int isHALT;
extern int updatePC;
extern unsigned nextPC;



extern int numStallCycles;  // Statistics Counter



void fetchstage() {
        int job_num;
	job_num = ActivityArgSize(ME) - 1;
	
	while(!isHALT){
	  if (TRACE)
	    printf("In FETCH  Stage at time %2.0f  PC: %x\n", GetSimTime(), PC);
	  do_fetch();
	  ProcessDelay(1.0);
	}

}




do_fetch() {
  SHADOW_PR[0].INSTRUCTION = insMEM[PC/4];
  SHADOW_PR[0].PC4 = PC+4;
 
  SHADOW_PC = (updatePC) ? nextPC : PC+4;
  printf("SHADOW_PC :%x\n", SHADOW_PC);
}




