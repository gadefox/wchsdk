#pragma once

#include "wch/hw/base.h"
#include "wch/hw/def.h"

/******************************************************************************/
/*                     Program Fast Interrupt Controller                      */
/******************************************************************************/

#define PFIC_BASE  (CORE_PERIPH_BASE + 0xE000)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define PFIC_ISR       0
#define PFIC_IPR       32
#define PFIC_ITHRESDR  64
#define PFIC_CFGR      72
#define PFIC_GISR      76
#define PFIC_VTFIDR    80
#define PFIC_VTFADDR   96
#define PFIC_IENR      256
#define PFIC_IRER      352
#define PFIC_IPSR      448
#define PFIC_IPRR      544
#define PFIC_IACTR     640
#define PFIC_IPRIOR    864
#define PFIC_SCTLR     2932

#else

//------------------------------------------------------------------------------

/* memory mapped structure for Program Fast Interrupt Controller (PFIC) */
typedef struct {
   __I uint32_t ISR[8];             /* Interrupt Enable Status Register x                  */
   __I uint32_t IPR[8];             /* Interrupt Pending Status Register x                 */
  __IO uint32_t ITHRESDR;           /* Interrupt Priority Threshold Configuration Register */
  __IO uint32_t RESERVED;
  __IO uint32_t CFGR;               /* Interrupt Configuration Register                    */
   __I uint32_t GISR;               /* Interrupt Global Status Register                    */
  __IO uint8_t  VTFIDR[4];          /* VTF ID Configuration Regsite                        */
       uint8_t  RESERVED0[12];
  __IO uint32_t VTFADDR[4];         /* VTF x Offset register                               */
       uint8_t  RESERVED1[0x90];
   __O uint32_t IENR[8];            /* Interrupt Enable Setting Register x                 */
       uint8_t  RESERVED2[0x60];
   __O uint32_t IRER[8];            /* Interrupt Enable Clear Register x                   */
       uint8_t  RESERVED3[0x60];
   __O uint32_t IPSR[8];            /* Interrupt Pending Status Register x                 */
       uint8_t  RESERVED4[0x60];
   __O uint32_t IPRR[8];            /* Interrupt Pending Clear Register x                  */
       uint8_t  RESERVED5[0x60];
  __IO uint32_t IACTR[8];           /* Interrupt Activation Status Register x              */
       uint8_t  RESERVED6[0xE0];
  __IO uint8_t  IPRIOR[256];        /* Interrupt Priority Configuration Register           */
       uint8_t  RESERVED7[0x810];
  __IO uint32_t SCTLR;              /* System Control Register                             */
} pfic_t;

#define PFIC  ((pfic_t *)PFIC_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* Preemption_Priority_Group */
#define PFIC_PRIORITY_GROUP_0 ((uint32_t)0x00)
#define PFIC_PRIORITY_GROUP_1 ((uint32_t)0x01)
#define PFIC_PRIORITY_GROUP_2 ((uint32_t)0x02)
#define PFIC_PRIORITY_GROUP_3 ((uint32_t)0x03)
#define PFIC_PRIORITY_GROUP_4 ((uint32_t)0x04)

//------------------------------------------------------------------------------

/*******************  Bit definition for PFIC_SCTLR register  ******************/
#define PFIC_SCTLR_SYSRESET    ((uint32_t)0x80000000) /* Bit 31  : System reset (write 1 to reset, auto clear) */
#define PFIC_SCTLR_SETEVENT    ((uint32_t)0x00000020) /* Bit 5  : Set event for WFE wakeup */
#define PFIC_SCTLR_SEVONPEND   ((uint32_t)0x00000010) /* Bit 4  : 1 = All events and all interrupts (even disabled) wake system; 0 = Only enabled events and enabled interrupts wake system */
#define PFIC_SCTLR_WFITOWFE    ((uint32_t)0x00000008) /* Bit 3  : 1 = Treat WFI as WFE; 0 = Normal WFI behavior */
#define PFIC_SCTLR_SLEEPDEEP   ((uint32_t)0x00000004) /* Bit 2  : 1 = DEEPSLEEP; 0 = SLEEP */
#define PFIC_SCTLR_SLEEPONEXIT ((uint32_t)0x00000002) /* Bit 1  : 1 = Enter sleep after ISR exit; 0 = Return to main program */

/*******************  Bit definition for PFIC_ISR1 register  ****************/
#define PFIC_ISR1_INTENSTA2  ((uint32_t)0x00000004) /* Bit 2  : Interrupt 2 enable status */
#define PFIC_ISR1_INTENSTA3  ((uint32_t)0x00000008) /* Bit 3  : Interrupt 3 enable status */
#define PFIC_ISR1_INTENSTA12 ((uint32_t)0x00001000) /* Bit 12 : Interrupt 12 enable status */
#define PFIC_ISR1_INTENSTA14 ((uint32_t)0x00004000) /* Bit 14 : Interrupt 14 enable status */
#define PFIC_ISR1_INTENSTA16 ((uint32_t)0x00010000) /* Bit 16 : Interrupt 16 enable status */
#define PFIC_ISR1_INTENSTA17 ((uint32_t)0x00020000)
#define PFIC_ISR1_INTENSTA18 ((uint32_t)0x00040000)
#define PFIC_ISR1_INTENSTA19 ((uint32_t)0x00080000)
#define PFIC_ISR1_INTENSTA20 ((uint32_t)0x00100000)
#define PFIC_ISR1_INTENSTA21 ((uint32_t)0x00200000)
#define PFIC_ISR1_INTENSTA22 ((uint32_t)0x00400000)
#define PFIC_ISR1_INTENSTA23 ((uint32_t)0x00800000)
#define PFIC_ISR1_INTENSTA24 ((uint32_t)0x01000000)
#define PFIC_ISR1_INTENSTA25 ((uint32_t)0x02000000)
#define PFIC_ISR1_INTENSTA26 ((uint32_t)0x04000000)
#define PFIC_ISR1_INTENSTA27 ((uint32_t)0x08000000)
#define PFIC_ISR1_INTENSTA28 ((uint32_t)0x10000000)
#define PFIC_ISR1_INTENSTA29 ((uint32_t)0x20000000)
#define PFIC_ISR1_INTENSTA30 ((uint32_t)0x40000000)
#define PFIC_ISR1_INTENSTA31 ((uint32_t)0x80000000)

/*******************  Bit definition for PFIC_ISR2 register  ****************/
#define PFIC_ISR2_INTENSTA_MASK ((uint32_t)0x0000007F) /* Mask for IRQ32–38 */

#define PFIC_ISR2_INTENSTA32 ((uint32_t)0x00000001) /* Bit 0  : Interrupt 32 enable status */
#define PFIC_ISR2_INTENSTA33 ((uint32_t)0x00000002) /* Bit 1  : Interrupt 33 enable status */
#define PFIC_ISR2_INTENSTA34 ((uint32_t)0x00000004) /* Bit 2  : Interrupt 34 enable status */
#define PFIC_ISR2_INTENSTA35 ((uint32_t)0x00000008) /* Bit 3  : Interrupt 35 enable status */
#define PFIC_ISR2_INTENSTA36 ((uint32_t)0x00000010) /* Bit 4  : Interrupt 36 enable status */
#define PFIC_ISR2_INTENSTA37 ((uint32_t)0x00000020) /* Bit 5  : Interrupt 37 enable status */
#define PFIC_ISR2_INTENSTA38 ((uint32_t)0x00000040) /* Bit 6  : Interrupt 38 enable status */

/*******************  Bit definition for PFIC_IPR1 register  ****************/
#define PFIC_IPR1_PENDSTA2  ((uint32_t)0x00000004) /* Bit 2  : Interrupt 2 pending status */
#define PFIC_IPR1_PENDSTA3  ((uint32_t)0x00000008) /* Bit 3  : Interrupt 3 pending status */
#define PFIC_IPR1_PENDSTA12 ((uint32_t)0x00001000) /* Bit 12 : Interrupt 12 pending status */
#define PFIC_IPR1_PENDSTA14 ((uint32_t)0x00004000) /* Bit 14 : Interrupt 14 pending status */
#define PFIC_IPR1_PENDSTA16 ((uint32_t)0x00010000) /* Bit 16 : Interrupt 16 pending status */
#define PFIC_IPR1_PENDSTA17 ((uint32_t)0x00020000)
#define PFIC_IPR1_PENDSTA18 ((uint32_t)0x00040000)
#define PFIC_IPR1_PENDSTA19 ((uint32_t)0x00080000)
#define PFIC_IPR1_PENDSTA20 ((uint32_t)0x00100000)
#define PFIC_IPR1_PENDSTA21 ((uint32_t)0x00200000)
#define PFIC_IPR1_PENDSTA22 ((uint32_t)0x00400000)
#define PFIC_IPR1_PENDSTA23 ((uint32_t)0x00800000)
#define PFIC_IPR1_PENDSTA24 ((uint32_t)0x01000000)
#define PFIC_IPR1_PENDSTA25 ((uint32_t)0x02000000)
#define PFIC_IPR1_PENDSTA26 ((uint32_t)0x04000000)
#define PFIC_IPR1_PENDSTA27 ((uint32_t)0x08000000)
#define PFIC_IPR1_PENDSTA28 ((uint32_t)0x10000000)
#define PFIC_IPR1_PENDSTA29 ((uint32_t)0x20000000)
#define PFIC_IPR1_PENDSTA30 ((uint32_t)0x40000000)
#define PFIC_IPR1_PENDSTA31 ((uint32_t)0x80000000)

/*******************  Bit definition for PFIC_IPR2 register  ****************/
#define PFIC_IPR2_PENDSTA_MASK ((uint32_t)0x0000007F) /* Mask for IRQ32–38 */

#define PFIC_IPR2_PENDSTA32 ((uint32_t)0x00000001) /* Bit 0  : Interrupt 32 pending status */
#define PFIC_IPR2_PENDSTA33 ((uint32_t)0x00000002) /* Bit 1  : Interrupt 33 pending status */
#define PFIC_IPR2_PENDSTA34 ((uint32_t)0x00000004) /* Bit 2  : Interrupt 34 pending status */
#define PFIC_IPR2_PENDSTA35 ((uint32_t)0x00000008) /* Bit 3  : Interrupt 35 pending status */
#define PFIC_IPR2_PENDSTA36 ((uint32_t)0x00000010) /* Bit 4  : Interrupt 36 pending status */
#define PFIC_IPR2_PENDSTA37 ((uint32_t)0x00000020) /* Bit 5  : Interrupt 37 pending status */
#define PFIC_IPR2_PENDSTA38 ((uint32_t)0x00000040) /* Bit 6  : Interrupt 38 pending status */

/*******************  Bit definition for PFIC_CFGR register  ****************/
#define PFIC_CFGR_RESETSYS ((uint32_t)0x00000080) /* Bit 7 : System reset (write 1 to reset, auto clear) */

#define PFIC_CFGR_KEY1 ((uint32_t)0xFA050000) /* KEY1 */
#define PFIC_CFGR_KEY2 ((uint32_t)0xBCAF0000) /* KEY2 */
#define PFIC_CFGR_KEY3 ((uint32_t)0xBEEF0000) /* KEY3 */

/*******************  Bit definition for PFIC_GISR register  ****************/
#define PFIC_GISR_GPENDSTA ((uint32_t)0x00000200) /* Bit 9  : Any interrupt pending */
#define PFIC_GISR_GACTSTA  ((uint32_t)0x00000100) /* Bit 8  : Any interrupt active */

/*******************  Bit definition for PFIC_VTFADDRR0 register  ***********/
#define PFIC_VTFADDRR0_VTF0EN ((uint32_t)0x00000001) /* Bit 0 : Enable VTF0 interrupt */

/*******************  Bit definition for PFIC_VTFADDRR1 register  ***********/
#define PFIC_VTFADDRR1_VTF1EN ((uint32_t)0x00000001) /* Bit 0 : Enable VTF1 interrupt */

/*******************  Bit definition for PFIC_IENR1 register  ***************/
#define PFIC_IENR1_INTEN16 ((uint32_t)0x00010000) /* Bit 16 : Enable IRQ16 */
#define PFIC_IENR1_INTEN17 ((uint32_t)0x00020000)
#define PFIC_IENR1_INTEN18 ((uint32_t)0x00040000)
#define PFIC_IENR1_INTEN19 ((uint32_t)0x00080000)
#define PFIC_IENR1_INTEN20 ((uint32_t)0x00100000)
#define PFIC_IENR1_INTEN21 ((uint32_t)0x00200000)
#define PFIC_IENR1_INTEN22 ((uint32_t)0x00400000)
#define PFIC_IENR1_INTEN23 ((uint32_t)0x00800000)
#define PFIC_IENR1_INTEN24 ((uint32_t)0x01000000)
#define PFIC_IENR1_INTEN25 ((uint32_t)0x02000000)
#define PFIC_IENR1_INTEN26 ((uint32_t)0x04000000)
#define PFIC_IENR1_INTEN27 ((uint32_t)0x08000000)
#define PFIC_IENR1_INTEN28 ((uint32_t)0x10000000)
#define PFIC_IENR1_INTEN29 ((uint32_t)0x20000000)
#define PFIC_IENR1_INTEN30 ((uint32_t)0x40000000)
#define PFIC_IENR1_INTEN31 ((uint32_t)0x80000000)

/*******************  Bit definition for PFIC_IENR2 register  ***************/
#define PFIC_IENR2_INTEN_MASK ((uint32_t)0x0000007F) /* Mask for IRQ32–38 */

#define PFIC_IENR2_INTEN32 ((uint32_t)0x00000001) /* Bit 0 : Enable IRQ32 */
#define PFIC_IENR2_INTEN33 ((uint32_t)0x00000002)
#define PFIC_IENR2_INTEN34 ((uint32_t)0x00000004)
#define PFIC_IENR2_INTEN35 ((uint32_t)0x00000008)
#define PFIC_IENR2_INTEN36 ((uint32_t)0x00000010)
#define PFIC_IENR2_INTEN37 ((uint32_t)0x00000020)
#define PFIC_IENR2_INTEN38 ((uint32_t)0x00000040)

/*******************  Bit definition for PFIC_IRER1 register  ***************/
#define PFIC_IRER1_INTRSET16 ((uint32_t)0x00010000) /* Bit 16 : Disable IRQ16 */
#define PFIC_IRER1_INTRSET17 ((uint32_t)0x00020000)
#define PFIC_IRER1_INTRSET18 ((uint32_t)0x00040000)
#define PFIC_IRER1_INTRSET19 ((uint32_t)0x00080000)
#define PFIC_IRER1_INTRSET20 ((uint32_t)0x00100000)
#define PFIC_IRER1_INTRSET21 ((uint32_t)0x00200000)
#define PFIC_IRER1_INTRSET22 ((uint32_t)0x00400000)
#define PFIC_IRER1_INTRSET23 ((uint32_t)0x00800000)
#define PFIC_IRER1_INTRSET24 ((uint32_t)0x01000000)
#define PFIC_IRER1_INTRSET25 ((uint32_t)0x02000000)
#define PFIC_IRER1_INTRSET26 ((uint32_t)0x04000000)
#define PFIC_IRER1_INTRSET27 ((uint32_t)0x08000000)
#define PFIC_IRER1_INTRSET28 ((uint32_t)0x10000000)
#define PFIC_IRER1_INTRSET29 ((uint32_t)0x20000000)
#define PFIC_IRER1_INTRSET30 ((uint32_t)0x40000000)
#define PFIC_IRER1_INTRSET31 ((uint32_t)0x80000000)

/*******************  Bit definition for PFIC_IRER2 register  ***************/
#define PFIC_IRER2_INTRSET_MASK ((uint32_t)0x0000007F) /* Mask for IRQ32–38 */

#define PFIC_IRER2_INTRSET32 ((uint32_t)0x00000001) /* Bit 0 : Disable IRQ32 */
#define PFIC_IRER2_INTRSET33 ((uint32_t)0x00000002)
#define PFIC_IRER2_INTRSET34 ((uint32_t)0x00000004)
#define PFIC_IRER2_INTRSET35 ((uint32_t)0x00000008)
#define PFIC_IRER2_INTRSET36 ((uint32_t)0x00000010)
#define PFIC_IRER2_INTRSET37 ((uint32_t)0x00000020)
#define PFIC_IRER2_INTRSET38 ((uint32_t)0x00000040)

/*******************  Bit definition for PFIC_IPSR1 register  ****************/
#define PFIC_IPSR1_PENDSET2  ((uint32_t)0x00000004) /* Bit 2  : Set pending IRQ2 */
#define PFIC_IPSR1_PENDSET3  ((uint32_t)0x00000008) /* Bit 3  : Set pending IRQ3 */
#define PFIC_IPSR1_PENDSET12 ((uint32_t)0x00001000) /* Bit 12 : Set pending IRQ12 */
#define PFIC_IPSR1_PENDSET14 ((uint32_t)0x00004000) /* Bit 14 : Set pending IRQ14 */
#define PFIC_IPSR1_PENDSET16 ((uint32_t)0x00010000) /* Bit 16 : Set pending IRQ16 */
#define PFIC_IPSR1_PENDSET17 ((uint32_t)0x00020000)
#define PFIC_IPSR1_PENDSET18 ((uint32_t)0x00040000)
#define PFIC_IPSR1_PENDSET19 ((uint32_t)0x00080000)
#define PFIC_IPSR1_PENDSET20 ((uint32_t)0x00100000)
#define PFIC_IPSR1_PENDSET21 ((uint32_t)0x00200000)
#define PFIC_IPSR1_PENDSET22 ((uint32_t)0x00400000)
#define PFIC_IPSR1_PENDSET23 ((uint32_t)0x00800000)
#define PFIC_IPSR1_PENDSET24 ((uint32_t)0x01000000)
#define PFIC_IPSR1_PENDSET25 ((uint32_t)0x02000000)
#define PFIC_IPSR1_PENDSET26 ((uint32_t)0x04000000)
#define PFIC_IPSR1_PENDSET27 ((uint32_t)0x08000000)
#define PFIC_IPSR1_PENDSET28 ((uint32_t)0x10000000)
#define PFIC_IPSR1_PENDSET29 ((uint32_t)0x20000000)
#define PFIC_IPSR1_PENDSET30 ((uint32_t)0x40000000)
#define PFIC_IPSR1_PENDSET31 ((uint32_t)0x80000000)

/*******************  Bit definition for PFIC_IPSR2 register  ****************/
#define PFIC_IPSR2_PENDSET_MASK ((uint32_t)0x0000007F) /* Mask for IRQ32–38 */

#define PFIC_IPSR2_PENDSET32 ((uint32_t)0x00000001) /* Bit 0  : Set pending IRQ32 */
#define PFIC_IPSR2_PENDSET33 ((uint32_t)0x00000002) /* Bit 1  : Set pending IRQ33 */
#define PFIC_IPSR2_PENDSET34 ((uint32_t)0x00000004) /* Bit 2  : Set pending IRQ34 */
#define PFIC_IPSR2_PENDSET35 ((uint32_t)0x00000008) /* Bit 3  : Set pending IRQ35 */
#define PFIC_IPSR2_PENDSET36 ((uint32_t)0x00000010) /* Bit 4  : Set pending IRQ36 */
#define PFIC_IPSR2_PENDSET37 ((uint32_t)0x00000020) /* Bit 5  : Set pending IRQ37 */
#define PFIC_IPSR2_PENDSET38 ((uint32_t)0x00000040) /* Bit 6  : Set pending IRQ38 */

/*******************  Bit definition for PFIC_IPRR1 register  ****************/
#define PFIC_IPRR1_PENDRST2  ((uint32_t)0x00000004) /* Bit 2  : Clear pending IRQ2 */
#define PFIC_IPRR1_PENDRST3  ((uint32_t)0x00000008) /* Bit 3  : Clear pending IRQ3 */
#define PFIC_IPRR1_PENDRST12 ((uint32_t)0x00001000) /* Bit 12 : Clear pending IRQ12 */
#define PFIC_IPRR1_PENDRST14 ((uint32_t)0x00004000) /* Bit 14 : Clear pending IRQ14 */
#define PFIC_IPRR1_PENDRST16 ((uint32_t)0x00010000) /* Bit 16 : Clear pending IRQ16 */
#define PFIC_IPRR1_PENDRST17 ((uint32_t)0x00020000)
#define PFIC_IPRR1_PENDRST18 ((uint32_t)0x00040000)
#define PFIC_IPRR1_PENDRST19 ((uint32_t)0x00080000)
#define PFIC_IPRR1_PENDRST20 ((uint32_t)0x00100000)
#define PFIC_IPRR1_PENDRST21 ((uint32_t)0x00200000)
#define PFIC_IPRR1_PENDRST22 ((uint32_t)0x00400000)
#define PFIC_IPRR1_PENDRST23 ((uint32_t)0x00800000)
#define PFIC_IPRR1_PENDRST24 ((uint32_t)0x01000000)
#define PFIC_IPRR1_PENDRST25 ((uint32_t)0x02000000)
#define PFIC_IPRR1_PENDRST26 ((uint32_t)0x04000000)
#define PFIC_IPRR1_PENDRST27 ((uint32_t)0x08000000)
#define PFIC_IPRR1_PENDRST28 ((uint32_t)0x10000000)
#define PFIC_IPRR1_PENDRST29 ((uint32_t)0x20000000)
#define PFIC_IPRR1_PENDRST30 ((uint32_t)0x40000000)
#define PFIC_IPRR1_PENDRST31 ((uint32_t)0x80000000)

/*******************  Bit definition for PFIC_IPRR2 register  ****************/
#define PFIC_IPRR2_PENDRST_MASK ((uint32_t)0x0000007F) /* Mask for IRQ32–38 */

#define PFIC_IPRR2_PENDRST32 ((uint32_t)0x00000001) /* Bit 0  : Clear pending IRQ32 */
#define PFIC_IPRR2_PENDRST33 ((uint32_t)0x00000002) /* Bit 1  : Clear pending IRQ33 */
#define PFIC_IPRR2_PENDRST34 ((uint32_t)0x00000004) /* Bit 2  : Clear pending IRQ34 */
#define PFIC_IPRR2_PENDRST35 ((uint32_t)0x00000008) /* Bit 3  : Clear pending IRQ35 */
#define PFIC_IPRR2_PENDRST36 ((uint32_t)0x00000010) /* Bit 4  : Clear pending IRQ36 */
#define PFIC_IPRR2_PENDRST37 ((uint32_t)0x00000020) /* Bit 5  : Clear pending IRQ37 */
#define PFIC_IPRR2_PENDRST38 ((uint32_t)0x00000040) /* Bit 6  : Clear pending IRQ38 */

/*******************  Bit definition for PFIC_IACTR1 register  ****************/
#define PFIC_IACTR1_IACTS2  ((uint32_t)0x00000004) /* Bit 2  : Interrupt 2 active */
#define PFIC_IACTR1_IACTS3  ((uint32_t)0x00000008) /* Bit 3  : Interrupt 3 active */
#define PFIC_IACTR1_IACTS12 ((uint32_t)0x00001000) /* Bit 12 : Interrupt 12 active */
#define PFIC_IACTR1_IACTS14 ((uint32_t)0x00004000) /* Bit 14 : Interrupt 14 active */
#define PFIC_IACTR1_IACTS16 ((uint32_t)0x00010000) /* Bit 16 : Interrupt 16 active */
#define PFIC_IACTR1_IACTS17 ((uint32_t)0x00020000)
#define PFIC_IACTR1_IACTS18 ((uint32_t)0x00040000)
#define PFIC_IACTR1_IACTS19 ((uint32_t)0x00080000)
#define PFIC_IACTR1_IACTS20 ((uint32_t)0x00100000)
#define PFIC_IACTR1_IACTS21 ((uint32_t)0x00200000)
#define PFIC_IACTR1_IACTS22 ((uint32_t)0x00400000)
#define PFIC_IACTR1_IACTS23 ((uint32_t)0x00800000)
#define PFIC_IACTR1_IACTS24 ((uint32_t)0x01000000)
#define PFIC_IACTR1_IACTS25 ((uint32_t)0x02000000)
#define PFIC_IACTR1_IACTS26 ((uint32_t)0x04000000)
#define PFIC_IACTR1_IACTS27 ((uint32_t)0x08000000)
#define PFIC_IACTR1_IACTS28 ((uint32_t)0x10000000)
#define PFIC_IACTR1_IACTS29 ((uint32_t)0x20000000)
#define PFIC_IACTR1_IACTS30 ((uint32_t)0x40000000)
#define PFIC_IACTR1_IACTS31 ((uint32_t)0x80000000)

/*******************  Bit definition for PFIC_IACTR2 register  ****************/
#define PFIC_IACTR2_IACTS_MASK ((uint32_t)0x0000007F) /* Mask for Interrupts 32–38 active status */

#define PFIC_IACTR2_IACTS0  ((uint32_t)0x00000001) /* Bit 0  : Interrupt 32 active status */
#define PFIC_IACTR2_IACTS1  ((uint32_t)0x00000002) /* Bit 1  : Interrupt 33 active status */
#define PFIC_IACTR2_IACTS2  ((uint32_t)0x00000004) /* Bit 2  : Interrupt 34 active status */
#define PFIC_IACTR2_IACTS3  ((uint32_t)0x00000008) /* Bit 3  : Interrupt 35 active status */
#define PFIC_IACTR2_IACTS4  ((uint32_t)0x00000010) /* Bit 4  : Interrupt 36 active status */
#define PFIC_IACTR2_IACTS5  ((uint32_t)0x00000020) /* Bit 5  : Interrupt 37 active status */
#define PFIC_IACTR2_IACTS6  ((uint32_t)0x00000040) /* Bit 6  : Interrupt 38 active status */

//------------------------------------------------------------------------------

/*
 * This file contains various parts of the official WCH EVT Headers which
 * were originally under a restrictive license.
 *
 * The collection of this file was generated by
 * cnlohr, 2023-02-18 and
 * AlexanderMandera, 2023-06-23
 * It was significantly reworked into several files cnlohr, 2025-01-29
 *
 * While originally under a restrictive copyright, WCH has approved use
 * under MIT-licensed use, because of inclusion in Zephyr, as well as other
 * open-source licensed projects.
 *
 * These copies of the headers from WCH are available now under:
 *
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
