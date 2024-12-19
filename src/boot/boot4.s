.include "macro.inc"

#define	KUSIZE		0x80000000

#define	ICACHE_SIZE		0x4000			/* 16K */
#define	ICACHE_LINESIZE		32			/* 8 words */
#define	ICACHE_LINEMASK		(ICACHE_LINESIZE-1)

#define	CACH_PI		0x0	/* specifies primary inst. cache */
#define	C_IINV		0x0	/* index invalidate (inst, 2nd inst) */
#define	C_HINV		0x10	/* hit invalidate (all) */

#define CACHE(op, reg)  \
    .set noreorder     ;\
        cache op, reg  ;\
    .set reorder

.section .text, "ax"

glabel boot_osInvalICache
    blez $a1, 2f

	li $t3, ICACHE_SIZE
	bgeu $a1, $t3, 3f

	addu $t0, $a0, $zero
	addu $t1, $a0, $a1
	bgeu $t0, $t1, 2f

	addiu $t1, $t1, -ICACHE_LINESIZE
	andi $t2, $t0, ICACHE_LINEMASK
	subu $t0, $t0, $t2
1:
	CACHE((C_HINV|CACH_PI), ($t0))
    .set noreorder
	bltu $t0, $t1, 1b
	addiu $t0, $t0, ICACHE_LINESIZE
    .set reorder
2:
	jr $ra

3:
	li $t0, KUSIZE
	addu $t1, $t0, $t3
	addiu $t1, $t1, -ICACHE_LINESIZE
4:
	CACHE((C_IINV|CACH_PI), ($t0))
    .set noreorder
	bltu $t0, $t1, 4b
	addiu $t0, $t0, ICACHE_LINESIZE
    .set reorder

	jr $ra
.size boot_osInvalICache, . - boot_osInvalICache
