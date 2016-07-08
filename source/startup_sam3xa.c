/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2015, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

#include "sam3xa.h"

/* Initialize segments */
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _szero;
extern uint32_t _ezero;
extern uint32_t _sstack;
extern uint32_t _estack;

/** \cond DOXYGEN_SHOULD_SKIP_THIS */
int main(void);
/** \endcond */

void __libc_init_array(void);

/* Default empty handler */

extern void asm_handle_irq(void);


/* Exception Table */
__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {

        /* Configure Initial Stack Pointer, using linker-generated symbols */
        .pvStack = (void*) (&_estack),

        .pfnReset_Handler      = (void*) Reset_Handler,
        .pfnNMI_Handler        = (void*) (asm_handle_irq +1 ),
        .pfnHardFault_Handler  = (void*) (asm_handle_irq +1 ),
        .pfnMemManage_Handler  = (void*) (asm_handle_irq +1 ),
        .pfnBusFault_Handler   = (void*) (asm_handle_irq +1 ),
        .pfnUsageFault_Handler = (void*) (asm_handle_irq +1 ),
        .pfnReserved1_Handler  = (void*) (0UL),          /* Reserved */
        .pfnReserved2_Handler  = (void*) (0UL),          /* Reserved */
        .pfnReserved3_Handler  = (void*) (0UL),          /* Reserved */
        .pfnReserved4_Handler  = (void*) (0UL),          /* Reserved */
        .pfnSVC_Handler        = (void*) (asm_handle_irq +1 ),
        .pfnDebugMon_Handler   = (void*) (asm_handle_irq +1 ),
        .pfnReserved5_Handler  = (void*) (0UL),          /* Reserved */
        .pfnPendSV_Handler     = (void*) (asm_handle_irq +1 ) ,
        .pfnSysTick_Handler    = (void*) (asm_handle_irq +1 ),

        /* Configurable interrupts */
        .pfnSUPC_Handler   = (void*) (asm_handle_irq +1 ),   /* 0  Supply Controller */
        .pfnRSTC_Handler   = (void*) (asm_handle_irq +1 ),   /* 1  Reset Controller */
        .pfnRTC_Handler    = (void*) (asm_handle_irq +1 ),    /* 2  Real Time Clock */
        .pfnRTT_Handler    = (void*) (asm_handle_irq +1 ),    /* 3  Real Time Timer */
        .pfnWDT_Handler    = (void*) (asm_handle_irq +1 ),    /* 4  Watchdog Timer */
        .pfnPMC_Handler    = (void*) (asm_handle_irq +1 ),    /* 5  Power Management Controller */
        .pfnEFC0_Handler   = (void*) (asm_handle_irq +1 ),   /* 6  Enhanced Flash Controller 0 */
        .pfnEFC1_Handler   = (void*) (asm_handle_irq +1 ),   /* 7  Enhanced Flash Controller 1 */
        .pfnUART_Handler   = (void*) (asm_handle_irq +1 ),   /* 8  Universal Asynchronous Receiver Transceiver */
#ifdef _SAM3XA_SMC_INSTANCE_
        .pfnSMC_Handler    = (void*) (asm_handle_irq +1 ),    /* 9  Static Memory Controller */
#else
        .pvReserved9       = (void*) (0UL),          /* 9  Reserved */
#endif /* _SAM3XA_SMC_INSTANCE_ */
#ifdef _SAM3XA_SDRAMC_INSTANCE_
        .pfnSDRAMC_Handler = (void*) (asm_handle_irq +1 ), /* 10 Synchronous Dynamic RAM Controller */
#else
        .pvReserved10      = (void*) (0UL),          /* 10 Reserved */
#endif /* _SAM3XA_SDRAMC_INSTANCE_ */
        .pfnPIOA_Handler   = (void*) (asm_handle_irq +1 ),   /* 11 Parallel I/O Controller A, */
        .pfnPIOB_Handler   = (void*) (asm_handle_irq +1 ),   /* 12 Parallel I/O Controller B */
#ifdef _SAM3XA_PIOC_INSTANCE_
        .pfnPIOC_Handler   = (void*) (asm_handle_irq +1 ),   /* 13 Parallel I/O Controller C */
#else
        .pvReserved13      = (void*) (0UL),          /* 13 Reserved */
#endif /* _SAM3XA_PIOC_INSTANCE_ */
#ifdef _SAM3XA_PIOD_INSTANCE_
        .pfnPIOD_Handler   = (void*) (asm_handle_irq +1 ),   /* 14 Parallel I/O Controller D */
#else
        .pvReserved14      = (void*) (0UL),          /* 14 Reserved */
#endif /* _SAM3XA_PIOD_INSTANCE_ */
#ifdef _SAM3XA_PIOE_INSTANCE_
        .pfnPIOE_Handler   = (void*) (asm_handle_irq +1 ),   /* 15 Parallel I/O Controller E */
#else
        .pvReserved15      = (void*) (0UL),          /* 15 Reserved */
#endif /* _SAM3XA_PIOE_INSTANCE_ */
#ifdef _SAM3XA_PIOF_INSTANCE_
        .pfnPIOF_Handler   = (void*) (asm_handle_irq +1 ),   /* 16 Parallel I/O Controller F */
#else
        .pvReserved16      = (void*) (0UL),          /* 16 Reserved */
#endif /* _SAM3XA_PIOF_INSTANCE_ */
        .pfnUSART0_Handler = (void*) (asm_handle_irq +1 ), /* 17 USART 0 */
        .pfnUSART1_Handler = (void*) (asm_handle_irq +1 ), /* 18 USART 1 */
        .pfnUSART2_Handler = (void*) (asm_handle_irq +1 ), /* 19 USART 2 */
#ifdef _SAM3XA_USART3_INSTANCE_
        .pfnUSART3_Handler = (void*) (asm_handle_irq +1 ), /* 20 USART 3 */
#else
        .pvReserved20      = (void*) (0UL),          /* 20 Reserved */
#endif /* _SAM3XA_USART3_INSTANCE_ */
        .pfnHSMCI_Handler  = (void*) (asm_handle_irq +1 ),  /* 21 Multimedia Card Interface */
        .pfnTWI0_Handler   = (void*) (asm_handle_irq +1 ),   /* 22 Two-Wire Interface 0 */
        .pfnTWI1_Handler   = (void*) (asm_handle_irq +1 ),   /* 23 Two-Wire Interface 1 */
        .pfnSPI0_Handler   = (void*) (asm_handle_irq +1 ),   /* 24 Serial Peripheral Interface */
#ifdef _SAM3XA_SPI1_INSTANCE_
        .pfnSPI1_Handler   = (void*) (asm_handle_irq +1 ),   /* 25 Serial Peripheral Interface */
#else
        .pvReserved25      = (void*) (0UL),          /* 25 Reserved */
#endif /* _SAM3XA_SPI1_INSTANCE_ */
        .pfnSSC_Handler    = (void*) (asm_handle_irq +1 ),    /* 26 Synchronous Serial Controller */
        .pfnTC0_Handler    = (void*) (asm_handle_irq +1 ),    /* 27 Timer Counter 0 */
        .pfnTC1_Handler    = (void*) (asm_handle_irq +1 ),    /* 28 Timer Counter 1 */
        .pfnTC2_Handler    = (void*) (asm_handle_irq +1 ),    /* 29 Timer Counter 2 */
        .pfnTC3_Handler    = (void*) (asm_handle_irq +1 ),    /* 30 Timer Counter 3 */
        .pfnTC4_Handler    = (void*) (asm_handle_irq +1 ),    /* 31 Timer Counter 4 */
        .pfnTC5_Handler    = (void*) (asm_handle_irq +1 ),    /* 32 Timer Counter 5 */
#ifdef _SAM3XA_TC2_INSTANCE_
        .pfnTC6_Handler    = (void*) (asm_handle_irq +1 ),    /* 33 Timer Counter 6 */
#else
        .pvReserved33      = (void*) (0UL),          /* 33 Reserved */
#endif /* _SAM3XA_TC2_INSTANCE_ */
#ifdef _SAM3XA_TC2_INSTANCE_
        .pfnTC7_Handler    = (void*) (asm_handle_irq +1 ),    /* 34 Timer Counter 7 */
#else
        .pvReserved34      = (void*) (0UL),          /* 34 Reserved */
#endif /* _SAM3XA_TC2_INSTANCE_ */
#ifdef _SAM3XA_TC2_INSTANCE_
        .pfnTC8_Handler    = (void*) (asm_handle_irq +1 ),    /* 35 Timer Counter 8 */
#else
        .pvReserved35      = (void*) (0UL),          /* 35 Reserved */
#endif /* _SAM3XA_TC2_INSTANCE_ */
        .pfnPWM_Handler    = (void*) (asm_handle_irq +1 ),    /* 36 Pulse Width Modulation Controller */
        .pfnADC_Handler    = (void*) (asm_handle_irq +1 ),    /* 37 ADC Controller */
        .pfnDACC_Handler   = (void*) (asm_handle_irq +1 ),   /* 38 DAC Controller */
        .pfnDMAC_Handler   = (void*) (asm_handle_irq +1 ),   /* 39 DMA Controller */
        .pfnUOTGHS_Handler = (void*) (asm_handle_irq +1 ), /* 40 USB OTG High Speed */
        .pfnTRNG_Handler   = (void*) (asm_handle_irq +1 ),   /* 41 True Random Number Generator */
#ifdef _SAM3XA_EMAC_INSTANCE_
        .pfnEMAC_Handler   = (void*) (asm_handle_irq +1 ),   /* 42 Ethernet MAC */
#else
        .pvReserved42      = (void*) (0UL),          /* 42 Reserved */
#endif /* _SAM3XA_EMAC_INSTANCE_ */
        .pfnCAN0_Handler   = (void*) (asm_handle_irq +1 ),   /* 43 CAN Controller 0 */
        .pfnCAN1_Handler   = (void*) (asm_handle_irq +1 )    /* 44 CAN Controller 1 */
};

/**
 * \brief This is the code that gets called on processor reset.
 * To initialize the device, and call the main() routine.
 */
void Reset_Handler(void)
{
        uint32_t *pSrc, *pDest;

        /* Initialize the relocate segment */
        pSrc = &_etext;
        pDest = &_srelocate;

        if (pSrc != pDest) {
                for (; pDest < &_erelocate;) {
                        *pDest++ = *pSrc++;
                }
        }

        /* Clear the zero segment */
        for (pDest = &_szero; pDest < &_ezero;) {
                *pDest++ = 0;
        }

        /* Set the vector table base address */
        pSrc = (uint32_t *) & _sfixed;
        SCB->VTOR = ((uint32_t) pSrc & SCB_VTOR_TBLOFF_Msk);

        /* Initialize the C library */
        __libc_init_array();

        /* Branch to main function */
        main();

        /* Infinite loop */
        while (1);
}
