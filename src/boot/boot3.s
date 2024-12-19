.include "macro.inc"

.set noat
.set noreorder
.set gp=64

.section .text, "ax"

/* Handwritten function */
/* Invalidates data cache from 0x80000000 to 0x80002000 */
glabel boot_invaldcache
    /* 12A0 803002A0 3C088000 */  lui        $t0, 0x8000
    /* 12A4 803002A4 240A2000 */  addiu      $t2, $zero, 0x2000
    /* 12A8 803002A8 010A4821 */  addu       $t1, $t0, $t2
    /* 12AC 803002AC 2529FFF0 */  addiu      $t1, $t1, -0x10
  1:
    /* 12B0 803002B0 BD010000 */  cache      0x01, 0x0($t0) /* handwritten instruction */
    /* 12B4 803002B4 0109082B */  sltu       $at, $t0, $t1
    /* 12B8 803002B8 1420FFFD */  bnez       $at, 1b
    /* 12BC 803002BC 25080010 */   addiu     $t0, $t0, 0x10
    /* 12C0 803002C0 03E00008 */  jr         $ra
    /* 12C4 803002C4 00000000 */   nop
    /* 12C8 803002C8 00000000 */  nop
    /* 12CC 803002CC 00000000 */  nop
.size boot_invaldcache, . - boot_invaldcache
