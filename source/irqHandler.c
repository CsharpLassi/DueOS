#include "irqstate.h"
#include "sam3x8e.h"
#include "console.h"
#include "task.h"
#include "pmm.h"

void HandleFaultIrq(uint32_t isrnumber,IrqState* state)
{
  //CFSR
  switch (isrnumber) {
      case 3:
        PrintString("Hard-Fault gefunden\n");
        break;
      case 4:
          PrintString("Memory-Fault gefunden\n");
          break;
      case 5:
          PrintString("Bus-Fault gefunden\n");
          break;
      case 6:
        PrintString("Usage-Fault gefunden\n");
        PrintString("Register:%x\n",(SCB->CFSR & SCB_CFSR_USGFAULTSR_Msk) >> SCB_CFSR_USGFAULTSR_Pos);
        break;
      default:
        PrintString("Interupt gefunden\n");
        PrintString("Number: [%d] \n",isrnumber);
        break;

  }
  PrintString("Pointer: [%x] \n",state);
  PrintString("R0: [%x] \n",state->r0);
  PrintString("R1: [%x] \n",state->r1);
  PrintString("R2: [%x] \n",state->r2);
  PrintString("R3: [%x] \n",state->r3);
  PrintString("R4: [%x] \n",state->r4);
  PrintString("R5: [%x] \n",state->r5);
  PrintString("R6: [%x] \n",state->r6);
  PrintString("R7: [%x] \n",state->r7);
  PrintString("R8: [%x] \n",state->r8);
  PrintString("R9: [%x] \n",state->r9);
  PrintString("R10: [%x] \n",state->r10);
  PrintString("R11: [%x] \n",state->r11);
  PrintString("R12: [%x] \n",state->r12);
  PrintString("LR: [%x] \n",state->lr);
  PrintString("PC: [%x] \n",state->pc);
  PrintString("PSR: [%x] \n",state->psr);
  PrintString("SP: [%x] \n",state->sp);
  PrintString("Response: [%x] \n",state->response);

  while(1);
}

IrqState* HandleSysCall(IrqState* state)
{
  uint32_t* addr = (uint32_t*)(state->pc -2);
  uint8_t value = (*addr) & 0xFF;

  switch (value)
  {
    case 0:
      state =  CloseCurrentTask();
      break;
    case 1:
      state->r0 = (uint32_t)PmmMalloc(state->r0);
      break;
    default:
      break;
  }

  return state;
}

IrqState* HandleIrq(IrqState* state)
{
  IPSR_Type type;
  type.w = __get_IPSR();

  switch (type.b.ISR)
  {
    case 0:
    case 1:
    case 2:
      break;
    case 3:
    case 4:
    case 5:
    case 6:
      HandleFaultIrq(type.b.ISR,state);
      break;
    case 15:
      state = NextTask(state);
      break;
    case 16:
      state = HandleSysCall(state);
      break;
    default :
      break;
  }

  return state;
}
