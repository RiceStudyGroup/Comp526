#include "global.h"

/*
Decode the instruction and read the source register(s) REGISTER_FILE[rs] and REGISTER_FILE[rt]. 
The decoded fields and register values are stored in different fields of the shadow pipeline register SHADOW_PR[1]. 
The writeback flag is used to indicate that this instruction will write to a destination register destRegister in the WRITE stage. 
The control field is a set of bits indicating the instruction (bit 0, 1, 2, 3, or 4 are set if the instruction is ADD, LOAD, 
STORE, BNE, or ADDI respectively).

isBranchInstrIssue and branchTargetAddressIssue which are set in the ISSUE

*/

extern struct pipelineReg PR[];
extern struct pipelineReg SHADOW_PR[];
extern unsigned REG_FILE[];

extern void displayPipelineReg(int);

extern void displayShadowPipelineReg(int);

extern int isHALT;


// Statistics
extern double timeInsCompleted;

/*******************************************************************************/
void issuestage() {
    int job_num;
    job_num = ActivityArgSize(ME) - 1;

    while (!isHALT) {
        if (TRACE)
            printf("In ISSUE  Stage at time %2.0f  Instruction: %x\n", GetSimTime(), PR[0].INSTRUCTION);
        do_issue();
        ProcessDelay(1.0);
    }
}


int isRRformat(int control) {
    return (control & 0x1) ? TRUE : FALSE;
}

int isImmformat(int control) {
    return (control & 0x10) ? TRUE : FALSE;
}

int isBranchInstruction(int control) {
    return (control & 0x8) ? TRUE : FALSE;
}


int isLoadInstruction(int control) {
    return (control & 0x2) ? TRUE : FALSE;
}

int isStoreInstruction(int control) {
    return (control & 0x4) ? TRUE : FALSE;
}

int isRegWrite(int control) {
    return (control & 0x1 || control & 0x2 || control & 0x10) ? TRUE : FALSE;
}


decode(unsigned instr, int *opCode, int *rs, int *rt, int *rd, int *offset, int *control) {
    int op, ALU2op, ALU1op, Load, Store, Branch;

    *opCode = (instr >> 26) & 0x3F; // INSTRUCTION[31:26]
    *rs = (instr >> 21) & 0x1F; // INSTRUCTION[25:21];
    *rt = (instr >> 16) & 0x1F; //INSTRUCTION[20:16];
    *rd = (instr >> 11) & 0x1F; //INSTRUCTION[15:11];
    *offset = ((instr >> 15) & 0x1) ? (0xFFFF0000 | (instr & 0xFFFF)) : (instr & 0xFFFF);
    *control = 0;

    op = (instr >> 26) & 0x3F; // INSTRUCTION[31:26]
    ALU2op = ((op == ADD) || (op == SUB));
    ALU1op = (op == ADDI);
    Load = (op == LOAD);
    Store = (op == STORE);
    Branch = (op == BNEZ);
    *control = (ALU1op << 4) | (Branch << 3) | (Store << 2) | (Load << 1) | ALU2op;
}


checkAndHandleSpeculativeBranch() {
    /*
    In the ISSUE stage, after decoding check if the instruction is BNE. 
    If so set the isBranchInstruction and branchTargetAddressIssue fields 
    of SHADOW PR[1]. The first is a flag that needs to set to TRUE if the 
    instruction is BNE and FALSE otherwise. The second is the target address 
    of the branch from where instruction will speculatively continue. These 
    need to be done by completing the stub checkAndHandleSpeculativeBranch() 
    in issue.c.
    */
   if(SHADOW_PR[1].opCode == BNEZ){
       SHADOW_PR[1].isBranchInstruction = true;
       SHADOW_PR[1].branchTargetAddressIssue =  SHADOW_PR[1].PC4  + SHADOW_PR[1].offset
   }else{
       SHADOW_PR[1].isBranchInstruction = false;
   }



    // If instruction is a Banch instruction set "isBranchInstrIssue" in my SHADOW_PR.
    // Set "BranchTargetAddressIssue" in my SHADOW_PR with the target addressof the branch.
}


do_issue() {
    int rs, rt; // Source Register fields
    int rd;  // Destination Register Fields
    int opCode;
    int offset;
    unsigned control;  // Bit fields -- ALU2op (bit 0), LD (bit 1), SD (bit 2)  BNEZ (bit 3) ALU1op (bit 4)
    unsigned instr = PR[0].INSTRUCTION;


    decode(instr, &opCode, &rs, &rt, &rd, &offset, &control);

    SHADOW_PR[1] = PR[0];
    SHADOW_PR[1].srcReg1 = rs;
    SHADOW_PR[1].srcReg2 = (isRRformat(control) || isStoreInstruction(control)) ? rt : -1;
    SHADOW_PR[1].operand1 = REG_FILE[rs];
    SHADOW_PR[1].operand2 = (SHADOW_PR[1].srcReg2 == -1) ? -1 : REG_FILE[rt];
    SHADOW_PR[1].offset = offset;
    SHADOW_PR[1].control = control;
    printf("OFFSET: %x  control: %x\n", SHADOW_PR[1].offset, SHADOW_PR[1].control);
    SHADOW_PR[1].writeBack = isRegWrite(control) ? TRUE : FALSE;
    SHADOW_PR[1].destReg = isRRformat(control) ? rd : (isLoadInstruction(control) || isImmformat(control)) ? rt : -1;
    SHADOW_PR[1].opCode = opCode;


    checkAndHandleSpeculativeBranch();

    if (opCode == HALT) {
        /* If the instruction is a HALT instruction an internal halt signal is asserted 
        and all stages will stop (and the simulation will end). */
        isHALT = TRUE;
        timeInsCompleted = GetSimTime();
    }

}

