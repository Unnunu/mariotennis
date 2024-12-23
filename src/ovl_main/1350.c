#include "common.h"

extern u32 D_80041804;
extern s8 D_80059A30[0x100];
extern s8 D_80059E30[0x100];
extern OSThread D_8005BE30;

extern s32 D_80061F6C;
extern s32 D_80061D74;
extern s32 D_80061D78;
extern s32 D_80061D7C;
extern s32 D_80061D80;

extern s32 D_80061F48[2];

extern void __osEnqueueThread(OSThread** threadQueue, OSThread* thread);
extern void func_80033360(OSThread** threadQueue, OSThread* thread);

void func_8003AC10(void);

void func_80041E6C(void);
void func_800332DC(void);
void func_80033394(void);
void func_80031D60(void*);
void func_80031C4C(OSThread*);
void func_8003125C(void);
void func_80032CC0(s8* dst, s8* src, s32 length);

void func_80032BA0(void);

extern s32 different_80033360[];
extern void __osInitialize_autodetect(void);

void func_80031000(s32 arg0, s32 arg1, s32 arg2) {
    D_80041804 = *(u32*)(&func_80032BA0);
    func_8003AC10();
    osInvalICache(osEepromLongWrite, 0x400);

    func_80032CC0((s8*)func_80041E6C, (s8*)func_800332DC, (u32)different_80033360 - (u32)func_800332DC);
    func_80032CC0((s8*)__osEnqueueThread, (s8*)func_80033360, (u32)func_80033394 - (u32)func_80033360);
    func_8003AC10();
    osInvalICache(func_80041E6C, (u32)different_80033360 - (u32)func_800332DC);
    osInvalICache(__osEnqueueThread, (u32)func_80033394 - (u32)func_80033360);

    D_80061D74 = arg1;
    D_80061D78 = arg2;
    bzero(D_80061F48, 8);
    D_80061F48[1] = arg0;

    osInitialize();
    __osInitialize_autodetect(); // why ?

    osAiSetFrequency(32000);
    osCreateThread(&D_8005BE30, 1, &func_80031D60, NULL, D_80059E30 + sizeof(D_80059E30), 10);
    func_80031C4C(&D_8005BE30);
}

extern OSThread D_80061D98;
extern s32 D_80061D84;
extern void func_80031EE8(void*);
void func_80033210(s32, s32, s32);
void func_80040F20(void);
void func_80031420(s32, s32);
void func_800317B4(s32);
//INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_80031164);
void func_80031164(void) {
    func_8003AC10();
    func_80033210(0xA0100000, 0x300000, 0);
    D_80061F6C = 0;
    func_80040F20();
    func_80031420(2, 1);
    D_80061D7C = osGetCount();
    osViSetSpecialFeatures(0x9A);
    osUnmapTLBAll();
    func_8003125C();
    func_800317B4(0);
    D_80061D80 = osGetCount();
    osSetThreadPri(&D_8005BE30, 0xA);
    D_80061F48[0] = 0;
    D_80061D84 = osGetCount();
    osSetThreadPri(&D_8005BE30, 0);
    osCreateThread(&D_80061D98, 4, func_80031EE8, 0, D_80059A30 + sizeof(D_80059A30), 50);
    osStartThread(&D_80061D98);
}

void func_8003125C(void) {
    __asm__(
        ".set noreorder\n"
        "cfc1   $a0,    $31\n"
        "nop\n"
        "li     $a1,    ~(0xF0001F00)\n"
        "and    $a0,    $a0,    $a1\n"
        "li     $a1,    ~(0x00000F80)\n"
        "and    $a0,    $a0,    $a1\n"
        "li     $a1,    0xF00\n"
        "or     $a0,    $a0,    $a1\n"
        "ctc1   $a0,    $31\n"
        "nop\n"
        ".set reorder\n"
        );
}


extern void func_80100000(void);
extern char D_802EC000[];
extern void func_800C8000(void);
extern OSMesgQueue D_80061F50;
extern OSMesg D_8005BE10[8];
extern void* D_8005BFE0;
extern Gfx* D_800648EC[];
extern s32 D_80059F54;
extern Gfx* D_800648E8;
extern void func_80031ECC(void);
INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_80031290);
/*void func_80031290(void) {
    s32 temp_s0;
    void* temp_v0;

    temp_s0 = func_80037CC0(0x4E);
    func_80035CC0(temp_s0, func_80100000, func_80037D44(0x4E));
    osInvalICache(func_80100000, 0x10000);
    func_80100000();
    func_800322B4();
    func_80037DFC(0x13, D_802EC000);
    osInvalICache(D_802EC000, 0xC000);
    func_80037DFC(NULL, func_800C8000);
    osInvalICache(func_800C8000, 0x2000);
    func_80031AAC();
    func_802EC048();
    osCreateMesgQueue(&D_80061F50, D_8005BE10, 8);
    func_8003244C(&D_8005BFE0, &D_80061F50, 3);
    func_800365F0();
    func_8003698C(0);
    func_8003698C(1);
    D_800648E8 = D_800648EC[D_80059F54];
    func_800369A0(D_800648E8, 0);
    D_800648E8 = func_80036970(0, func_80036748(D_80059F54, D_800648E8, 1));
    gSPEndDisplayList(D_800648E8++);
    func_80035F30(D_800648E8);
    func_80040E60(func_80031ECC);
}*/

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_80031420);

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_800317B4);

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_80031860);

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_800319A0);

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_80031A78);

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_80031AAC);

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_80031B50);

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_80031C4C);
/*
#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PRinternal/osint.h"

void func_80031C4C(OSThread* t) {
    register u32 saveMask = __osDisableInt();

    switch (t->state) {
        case OS_STATE_WAITING:
            t->state = OS_STATE_RUNNABLE;
            __osEnqueueThread(&__osRunQueue, t);
            break;
        case OS_STATE_STOPPED:
            if (t->queue == NULL || t->queue == &__osRunQueue) {
                t->state = OS_STATE_RUNNABLE;
                __osEnqueueThread(&__osRunQueue, t);
            } else {
                t->state = OS_STATE_WAITING;
                __osEnqueueThread(t->queue, t);
                __osEnqueueThread(&__osRunQueue, __osPopThread(t->queue));
            }
            break;
#ifdef _DEBUG
        default:
            __osError(ERR_OSSTARTTHREAD, 0);
            __osRestoreInt(saveMask);
            return;
#endif
    }

    if (__osRunningThread == NULL) {
        __osDispatchThread();
    } else if (__osRunningThread->priority < __osRunQueue->priority) {
        __osRunningThread->state = OS_STATE_RUNNABLE;
        __osEnqueueAndYield(&__osRunQueue);
    }

    __osRestoreInt(saveMask);
}
*/

