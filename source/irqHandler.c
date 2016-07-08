#include "irqstate.h"
#include "sam3x8e.h"
#include "console.h"

void handle_fault_irq(uint32_t isrnumber,irqstate* state)
{
  //CFSR
  switch (isrnumber) {
      case 3:
        uprintf("Hard-Fault gefunden\n");
        break;
      case 4:
          uprintf("Memory-Fault gefunden\n");
          break;
      case 5:
          uprintf("Bus-Fault gefunden\n");
          break;
      case 6:
        uprintf("Usage-Fault gefunden\n");
        uprintf("Register:%x\n",(SCB->CFSR & SCB_CFSR_USGFAULTSR_Msk) >> SCB_CFSR_USGFAULTSR_Pos);
        break;
      default:
        uprintf("Interupt gefunden\n");
        uprintf("Number: [%d] \n",isrnumber);
        break;

  }
  uprintf("Pointer: [%x] \n",state);
  uprintf("R0: [%x] \n",state->r0);
  uprintf("R1: [%x] \n",state->r1);
  uprintf("R2: [%x] \n",state->r2);
  uprintf("R3: [%x] \n",state->r3);
  uprintf("R4: [%x] \n",state->r4);
  uprintf("R5: [%x] \n",state->r5);
  uprintf("R6: [%x] \n",state->r6);
  uprintf("R7: [%x] \n",state->r7);
  uprintf("R8: [%x] \n",state->r8);
  uprintf("R9: [%x] \n",state->r9);
  uprintf("R10: [%x] \n",state->r10);
  uprintf("R11: [%x] \n",state->r11);
  uprintf("R12: [%x] \n",state->r12);
  uprintf("LR: [%x] \n",state->lr);
  uprintf("PC: [%x] \n",state->pc);
  uprintf("PSR: [%x] \n",state->psr);
  uprintf("SP: [%x] \n",state->sp);
  uprintf("Response: [%x] \n",state->response);


  while (1) {}
}

irqstate* handle_irq(irqstate* state)
{
  IPSR_Type type;
  type.w = __get_IPSR();

  //Schwere Fehler
  if (type.b.ISR >= 3 && type.b.ISR <= 6 ) {
    handle_fault_irq(type.b.ISR,state);
  }
  else if( type.b.ISR == 15)
  {
  }
  else
  {

  }


  return state;
}
