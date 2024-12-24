#include "common.h"

extern OSThread D_8005BE30;
extern s32 D_80061D88;
extern void (*D_80061F6C)(void);
extern u8 D_8005BFEC[32];
void func_80031164(void);

#ifdef NON_MATCHING
void func_80031D60(void) {
    func_80031164();
    osSetThreadPri(&D_8005BE30, 0);
    D_80061D88 = osGetCount();

    while (TRUE) {
        if (D_80061F6C != NULL) {
            D_80061F6C();
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/ovl_main/20B0", func_80031D60);
#endif

void func_80031DC4(void (*arg0)(void)) {
    D_80061F6C = arg0;
}

void func_80031DD0(void) {
}

void func_80031DD8(void* arg0) {
    while (TRUE) {
        func_800364C4();
        func_80031DD0();
    }
}

extern OSThread D_80061D98;
extern s8 D_80059A30[0x100];

void func_80031E04(void) {
    osSetThreadPri(&D_8005BE30, 0);
    osDestroyThread(&D_80061D98);
    osCreateThread(&D_80061D98, 4, func_80031DD8, 0, D_80059A30 + sizeof(D_80059A30), 50);
    osStartThread(&D_80061D98);
    osSetThreadPri(&D_8005BE30, 0);
    func_80031DC4(NULL);
}


void func_80031E94(void) {
    func_80041580();
}

void func_80031EB0(void) {
    func_800415A0();
}

void func_80031ECC(void) {
    func_80031E94();
}

void func_80031EE8(void) {
    func_80031290();
    func_800C8000();
}

void func_80031F0C(s32 arg0) {
    while (arg0) {
        func_80031F40();
        arg0--;
    }
}

INCLUDE_ASM("asm/nonmatchings/ovl_main/20B0", func_80031F40);

s32 func_800321C4(u32 arg0) {
    if (arg0 >= 256) {
        return FALSE;   
    } else {
        return (D_8005BFEC[arg0 >> 3] & (0x80 >> (arg0 & 7))) != 0;
    }
}

void func_80032200(u32 arg0) {
    if (arg0 < 256) {
        D_8005BFEC[arg0 >> 3] |= (0x80 >> (arg0 & 7));
    }
}

void func_8003223C(u32 arg0) {
    if (arg0 < 256) {
        D_8005BFEC[arg0 >> 3] &= ((u16)~0x80 >> (arg0 & 7));
    }
}

void func_80032278(u32 arg0) {
    if (arg0 < 256) {
        D_8005BFEC[arg0 >> 3] ^= (0x80 >> (arg0 & 7));
    }
}

void func_800322B4(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        D_8005BFEC[i] = 0;
    }
}