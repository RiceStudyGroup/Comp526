#include "global.h"

extern struct pipelineReg PR[];
extern struct pipelineReg SHADOW_PR[];
extern void displayPipelineReg(int);
extern void displaySHadowPipelineReg(int);

extern int isHALT;

int forwardMEM_WBOp1, forwardMEM_WBOp2, forwardEX_MEMOp1, forwardEX_MEMOp2;

void executestage()
{
  while (!isHALT)
  {
    if (TRACE)
      printf("\nIn EXECUTE Stage at time %2.0f INSTRUCTION: %x\n", GetSimTime(), PR[1].INSTRUCTION);
    do_execute();
    ProcessDelay(1.000);
  }
}

int isBranchInstr(int control)
{
  return ((control & 0x8) >> 3);
}

int branchCondition(int op)
{
  switch (op)
  {
  case BNEZ:
    return (PR[1].operand1 != 0);
  }
}

void handleForwarding()
{

  /*  Set  signals 
  (i) forwardEX_MEMOp1  
  (ii) forwardMEM_WBOp1 
  (iiii) forwardEX_MEMOp2  
  (iv) forwardMEM_WBOp2
  to TRUE or to FALSE.

  1. 
  forwardEX_MEMOp1 is set to TRUE if the instruction in the MEM stage (EX/MEM pipeline register)  should forward its
  result to the instruction in the EX stage (i.e. in the ISSUE/EX Pipeline register) as the first operand (operand1).
  2. 
  forwardMEM_WBOp1 is set to TRUE if the instruction in the WB stage (MEM.WB pipeline register)  should forward its
  result to the instruction in the EX stage (i.e. in the ISSUE/EX Pipeline register) as the first operand (operand1).
  3. 
  forwardEX_MEMOp2 and forwardMEM_WBOp2 do the same as above for the second operand in the EX stage.

  These signals are used by the "getOperand1" and "getOperand2" functions below to select the correct operands.
  Explictly set them to TRUE or FALSE in this function.

  */
  forwardEX_MEMOp1 = PR[3].destReg == PR[1].srcReg1 && PR[3].INSTRUCTION != 0;
  forwardEX_MEMOp2 = PR[3].destReg == PR[1].srcReg2 && PR[3].INSTRUCTION != 0;
  forwardMEM_WBOp1 = PR[4].destReg == PR[1].srcReg1 && PR[4].INSTRUCTION != 0;
  forwardMEM_WBOp2 = PR[4].destReg == PR[1].srcReg1 && PR[4].INSTRUCTION != 0;

}

int getOperand1()
{
  // Return the correct value of  operand1 to be used. This should be one of (i) the original value read from the
  // register file (ii) forwarded (register bypassed) value from pipeline register PR[2]  or (iii) forwarded  value from
  // pipeline register PR[3].

  // Currently the code  does not support forwarding and  always returns (i).
  // Use signals "forwardEX_MEMOp1" and "forwardMEM_WBOp1" set in "handleForwarding" above to select the correct operand.
  if (forwardMEM_WBOp1){
    return PR[4].result;
  }
  if (forwardEX_MEMOp1) {
    return PR[3].result;
  }

  return (PR[1].operand1);
}

int getOperand2()
{
  // Return the correct value of  operand1. It should be one of (i) the original value read from the
  // register file (ii) forwarded (register bypassed) value from pipeline register PR[2]  or (iii) forwarded value from
  // pipeline register PR[3]

  // Currently it does not support forwarding and  always returns (i).
  // Use signals "forwardEX_MEMOp2" and "forwardMEM_WBOp2" set in "handleForwarding" aboveto select the correct operand.
  if (forwardMEM_WBOp2){
    return PR[4].result;
  }
  if (forwardEX_MEMOp2) {
    return PR[3].result;
  }
  
  return (PR[1].operand2);
}

do_execute()
{
  int operation;
  int operand1, operand2;
  int result;
  int offset;
  int control;

  SHADOW_PR[2] = PR[1];

  handleForwarding();                    // Need to implement this above
  SHADOW_PR[2].operand1 = getOperand1(); // Need to change the function above
  SHADOW_PR[2].operand2 = getOperand2(); // Need to change the function aboe

  operand1 = getOperand1();
  operand2 = getOperand2();
  operation = PR[1].opCode;
  offset = PR[1].offset;
  control = PR[1].control;

  switch (operation)
  {
  case ADD:
    result = operand1 + operand2;
    break;
  case ADDI:
    result = operand1 + offset;
    break;
  case LOAD:
    result = operand1 + offset;
    break;
  case STORE:
    result = operand1 + offset;
    break;
  case BNEZ:
    result = (operand1 != 0) ? TRUE : FALSE;
    break;
  }

  SHADOW_PR[2].result = result;
}
