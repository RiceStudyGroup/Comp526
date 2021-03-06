#include  "global.h"


extern int numInsCompleted;
extern int isHALT;

extern unsigned PC;
extern unsigned SHADOW_PC;
extern struct pipelineReg PR[];
extern struct pipelineReg SHADOW_PR[];

extern void displayPipelineRegister(int);

extern void displayRegisters();


void syncstage() {
    while (!isHALT) {
        if (TRACE)
            printf("In SYNC  Stage:  Time %2.0f\n", GetSimTime());
        do_sync();
        ProcessDelay(1.000);
    }
}


do_sync() {
    PR[4] = SHADOW_PR[4];
    PR[3] = SHADOW_PR[3];
    PR[2] = SHADOW_PR[2];
    PR[1] = SHADOW_PR[1];
    PR[0] = SHADOW_PR[0];
    PC = SHADOW_PC;

    numInsCompleted++;

    if (TRACE) {
        printf("*************************************************************\n");

        printf("Instruction Fetch Stage\n");
        printf("Next PC: %d \n", PC);

        printf("\nPipeline Register 0\n");
        displayPipelineReg(0);

        printf("\nPipeline Register 1\n");
        displayPipelineReg(1);

        printf("\nPipeline Register 2\n");
        displayPipelineReg(2);

        printf("\nPipeline Register 3\n");
        displayPipelineReg(3);

        printf("\nPipeline Register 4\n");
        displayPipelineReg(4);

        printf("\nREGISTER FILE\n");
        displayRegisterFile();
        printf("\n*************************************************************\n");
        printf("*************************************************************\n");
    }

}
 



