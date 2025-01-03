.include "macro.inc"

.set noat
.set noreorder
.set gp=64

.section .text, "ax"

/* Handwritten function */
glabel boot_main
    /* 1050 80300050 3C048030 */  lui        $a0, %hi(D_80300350)
    /* 1054 80300054 24840350 */  addiu      $a0, $a0, %lo(D_80300350)
    /* 1058 80300058 40124800 */  mfc0       $s2, $9 /* handwritten instruction */
    /* 105C 8030005C 0C0C0020 */  jal        boot_decompress
    /* 1060 80300060 00000000 */   nop
    /* 1064 80300064 3C040001 */  lui        $a0, %hi(D_116C0)
    /* 1068 80300068 248416C0 */  addiu      $a0, $a0, %lo(D_116C0)
    /* 106C 8030006C 40064800 */  mfc0       $a2, $9 /* handwritten instruction */
    /* 1070 80300070 0800C400 */  j          func_80031000
    /* 1074 80300074 02402821 */   addu      $a1, $s2, $zero
    /* 1078 80300078 00000000 */  nop
    /* 107C 8030007C 00000000 */  nop
.size boot_main, . - boot_main
