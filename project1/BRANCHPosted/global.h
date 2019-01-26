#include <math.h>
#include <stdio.h>
#include "sim.h"

#define MAX_SIMULATION_TIME 5000.000

#define epsilon 0.001

#define TRUE 1
#define FALSE 0
#define DEBUG TRUE
#define TRACE TRUE
#define DEBUG2  FALSE

#define PIPELINE_REG 5

#define NOP 0
#define ADD 1
#define SUB 2
#define MUL 3
#define LOAD 4
#define ADDI  5
#define STORE 6
#define COPYFP 7
#define BRANCH 8
#define BNEZ 9
#define HALT 10


#define NUM_REGISTERS 16
#define MEM_SIZE 1024
#define INSTR_MEM_SIZE 1024

#define NUM_ITERATIONS 100
#define BASE_ARRAY 0
#define BASE_ARRAY_SRC1 0
#define BASE_ARRAY_SRC2 256
#define BASE_ARRAY_DEST 512

struct branchInfo {
    int isBranchInstr;
    int condition;
    int inlinePC;
    int branchTargetAddress;
};


struct pipelineReg {
    unsigned INSTRUCTION;
    unsigned opCode;
    unsigned offset;
    unsigned srcReg1;
    unsigned srcReg2;
    unsigned destReg;
    unsigned operand1;
    unsigned operand2;
    unsigned result;
    unsigned writeBack;
    unsigned PC4;
    unsigned control;
    unsigned isBranchInstrIssue;
    unsigned branchTargetAddressIssue;
    unsigned isBranchInstrMem;
    unsigned conditionMem;
    unsigned inlinePCMem;
};
