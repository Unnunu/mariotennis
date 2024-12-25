#include "common.h"
#include "PRinternal/viint.h"
#include "nusys.h"

typedef struct UnkAlpha {
    /* 0x00 */ s8 unk_00[14];
} UnkAlpha; // size = 0xE

// rspboot
extern u8 D_8003DA00[];
extern u8 D_8003DAD0[];

// .text
extern u32 D_80041804;

// .data
extern s8 D_80059A30[0x100];
extern s8 D_80059E30[0x100];
extern s32 D_80059F54;

// .bss
static OSMesg D_8005BE10_[8];
static OSThread D_8005BE30_;
static NUScClient D_8005BFE0_;
static u8 sGlobalFlags[32];

extern char D_8005C010[0x400]; // nuScStack, static in nusched
extern char D_8005C410[0x400]; // nuScAudioStack
extern char D_8005C810[0x400]; // nuScAudioStack
extern s32 D_8005CC10[625];
// file split to nuGfxTaskMgr

extern s16 taskDoneMsg;
extern s16 swapBufMsg;
extern u32 nuGfxTaskSpool;

typedef struct RSPTask {
    /* 0x00 */ struct RSPTask* next;
    /* 0x04 */ char unk_04[0xC];
    /* 0x10 */ OSTask task;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ char unk_54[4];
} RSPTask; // size = 0x58

extern RSPTask D_80062610[10];

extern u8 D_800663D0[0x400];
extern u8 D_800657C0[0xC10];
extern RSPTask* D_8005D5E0;

extern void* D_80049B18;
extern OSMesgQueue D_80062988;
extern s32 D_800629CC;
extern OSMesgQueue D_80062B70;
extern OSMesg D_8005D5F0[1];
extern OSMesg D_8005D5F4[1];
extern OSContStatus D_800629A4[4];

extern UnkAlpha D_80063854[];
extern s32 D_800638BC[4];
extern s32 D_800638CC;
extern u8 D_800638D0;

s32 D_80061D74;
s32 D_80061D78;
s32 D_80061D7C;
extern s32 D_80061D80;
extern void (*D_80061F6C)(void);

extern s32 D_80061F48[2];
extern OSMesgQueue D_800650B0;
extern OSMesg D_8005DD70[8];
extern s8 D_8005EF40[];

extern void func_80100000(void);
extern char D_802EC000[];
extern void func_800C8000(void);
extern OSMesgQueue D_80061F50;
extern Gfx* D_800648EC[];
extern Gfx* D_800648E8;
extern OSThread siMgrThread;
extern void func_80031ECC(void);

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

extern OSThread D_80061D98;
extern s32 D_80061D84;
extern void func_80031EE8(void*);
void func_80033210(s32, s32, s32);
void func_80040F20(void);
void nuScCreateScheduler(u8, u8);
void func_800317B4(u32);

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
    osCreateThread(&D_8005BE30_, 1, &func_80031D60, NULL, D_80059E30 + sizeof(D_80059E30), 10);
    func_80031C4C(&D_8005BE30_);
}

void func_80031164(void) {
    func_8003AC10();
    func_80033210(0xA0100000, 0x300000, 0);
    D_80061F6C = NULL;
    func_80040F20();
    nuScCreateScheduler(OS_TV_MPAL, 1);
    D_80061D7C = osGetCount();
    osViSetSpecialFeatures(0x9A);
    osUnmapTLBAll();
    func_8003125C();
    func_800317B4(0);
    D_80061D80 = osGetCount();
    osSetThreadPri(&D_8005BE30_, 10);
    D_80061F48[0] = 0;
    D_80061D84 = osGetCount();
    osSetThreadPri(&D_8005BE30_, 0);
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

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_80031290);
/*
void func_80031290(void) {
    void* s0;
    void* a1;

    s0 = 0x4E;
    s0 = func_80037CC0(s0);
    func_80035CC0(s0, func_80100000, func_80037D44(s0));
    osInvalICache(func_80100000, s0 = 0x10000);
    func_80100000();
    func_800322B4();

    func_80037DFC(s0 = 0x13, s0 = D_802EC000);
    osInvalICache(s0, s0 = 0xC000);

    func_80037DFC(0x0, func_800C8000);
    osInvalICache(func_800C8000, 0x2000);
}*/
/*
void func_80031290(void) {
    s32 temp_s0;
    Gfx* gfxPtr;
    Gfx* gfxPtr2;

    temp_s0 = func_80037CC0(D_4E);
    func_80035CC0(temp_s0, func_80100000, func_80037D44(D_4E));
    osInvalICache(func_80100000, D_10000);
    func_80100000();
    func_800322B4();
    func_80037DFC(D_13, D_802EC000);
    osInvalICache(D_802EC000, D_C000);
    func_80037DFC(D_0, func_800C8000);
    osInvalICache(func_800C8000, D_2000);
    func_80031AAC();
    func_802EC048();
    osCreateMesgQueue(&D_80061F50, D_8005BE10_, 8);
    func_8003244C(D_8005BFE0_, &D_80061F50, 3);
    func_800365F0();
    func_8003698C(0);
    func_8003698C(1);
    D_800648E8 = gfxPtr = D_800648EC[D_80059F54];
    func_800369A0(gfxPtr, 0);
    gfxPtr2 = func_80036970(0, func_80036748(D_80059F54, gfxPtr, 1));
    gSPEndDisplayList(gfxPtr2++);
    D_800648E8 = gfxPtr2;
    func_80035F30(D_800648E8);
    func_80040E60(func_80031ECC);
}
*/

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", nuScCreateScheduler);

#ifdef NON_MATCHING
void func_800317B4(u32 seed) {
    u32 i;
    u32* ptr = D_8005CC10;

    bzero(D_8005CC10, sizeof(D_8005CC10));
    if (seed == 0) {
        seed = 0x1105;
    } else if ((seed % 2) == 0) {
        seed = seed * 2 + 1;        
    }
    
    for (i = 1; i < 624; seed *= 0x10DCD) {
        ptr[i] = seed;
        i++;
    }

    ptr[0] = &ptr[625];
}
#else
INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_800317B4);
void func_800317B4(u32 seed);
#endif

void nuGfxTaskMgrInit(void) {
    u32 i;

    taskDoneMsg = 8;
    swapBufMsg = 4;
    nuGfxTaskSpool = 0;
    nuGfxDisplayOff();

    for (i = 0; i < 10; i++) {
        D_80062610[i].next = &D_80062610[i + 1];
        D_80062610[i].unk_50 = -1;
        D_80062610[i].task.t.type = M_GFXTASK;
        D_80062610[i].task.t.flags = 0;
        D_80062610[i].task.t.ucode_boot = D_8003DA00;
        D_80062610[i].task.t.ucode_boot_size = (u32)D_8003DAD0 - (u32)D_8003DA00;
        D_80062610[i].task.t.ucode_size = SP_UCODE_SIZE;
        D_80062610[i].task.t.ucode_data_size = SP_UCODE_DATA_SIZE;
        D_80062610[i].task.t.dram_stack = D_800663D0;
        D_80062610[i].task.t.dram_stack_size = sizeof(D_800663D0);
        D_80062610[i].task.t.yield_data_ptr = D_800657C0;
        D_80062610[i].task.t.yield_data_size = sizeof(D_800657C0);
    }
    D_8005D5E0 = D_80062610[9].next = &D_80062610[0];
}

// nuContMgrInit
#ifdef NON_MATCHING
u8 nuContMgrInit(void) {
    s32 i;
    s32 a;
    s32 mask;

    func_80033AB4();
    osCreateMesgQueue(&D_80062988, D_8005D5F0, 1);
    osCreateMesgQueue(&D_80062B70, D_8005D5F4, 1);
    func_8003A880(&D_80049B18);
    func_80033A84();
    
    for (i = 0, D_800629CC = 0, mask = 1, a = 0; i < 4; mask <<= 1, i++) {
        if (D_800629A4[i].errno == 0 && (D_800629A4[i].type & CONT_TYPE_MASK) == CONT_TYPE_NORMAL) {
            D_800629CC++;
            a |= mask;            
        }
    }

    return a;
}
#else
u8 nuContMgrInit(void);
INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", nuContMgrInit);
#endif

// nuContInit
u8 func_80031A78(void) {
    u8 temp_s0;
    
    temp_s0 = func_80031B50();
    nuContMgrInit();
    func_80041020();
    return temp_s0;
}


void func_80031AAC(void) {
    s32 i;
    
    for (i = 0, D_800638D0 = func_80031A78(), D_800638CC = 0; i < 4; i++) {
        if ((D_800638D0 >> i) & 1) {
            D_800638BC[D_800638CC++] = i;
        }
        bzero(&D_80063854[i], sizeof(UnkAlpha));
    }
}

void nuSiMgrThread(void* arg);

// nuSiMgrInit
u8 func_80031B50(void) {
    u8 sp28;
    s32 i;
    OSContStatus sp18[4];

    osCreateMesgQueue(&D_800650B0, D_8005DD70, 8);
    osSetEventMesg(OS_EVENT_SI, &D_800650B0, 0);
    osContInit(&D_800650B0, &sp28, sp18);

    for (i = 0; i < 4; i++) {
        if (!((sp28 >> i) & 1) || sp18[i].errno != 0 || (sp18[i].type & CONT_TYPE_MASK) != CONT_TYPE_NORMAL) {
            sp28 &= ~(1 << i);
        }
    }

    osCreateThread(&siMgrThread, 6, nuSiMgrThread, NULL, D_8005EF40, 115);
    osStartThread(&siMgrThread);
    return sp28;
}

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

extern OSThread D_8005BE30_;
extern s32 D_80061D88;

void func_80031164(void);

#ifdef NON_MATCHING
void func_80031D60(void) {
    func_80031164();
    osSetThreadPri(&D_8005BE30_, 0);
    D_80061D88 = osGetCount();

    while (TRUE) {
        if (D_80061F6C != NULL) {
            D_80061F6C();
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_80031D60);
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
    osSetThreadPri(&D_8005BE30_, 0);
    osDestroyThread(&D_80061D98);
    osCreateThread(&D_80061D98, 4, func_80031DD8, 0, D_80059A30 + sizeof(D_80059A30), 50);
    osStartThread(&D_80061D98);
    osSetThreadPri(&D_8005BE30_, 0);
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

void func_80031EE8(void* arg) {
    func_80031290();
    func_800C8000();
}

void func_80031F0C(s32 arg0) {
    while (arg0) {
        func_80031F40();
        arg0--;
    }
}

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_80031F40);

s32 func_800321C4(u32 arg0) {
    if (arg0 >= 256) {
        return FALSE;   
    } else {
        return (sGlobalFlags[arg0 >> 3] & (0x80 >> (arg0 & 7))) != 0;
    }
}

void func_80032200(u32 arg0) {
    if (arg0 < 256) {
        sGlobalFlags[arg0 >> 3] |= (0x80 >> (arg0 & 7));
    }
}

void func_8003223C(u32 arg0) {
    if (arg0 < 256) {
        sGlobalFlags[arg0 >> 3] &= ((u16)~0x80 >> (arg0 & 7));
    }
}

void func_80032278(u32 arg0) {
    if (arg0 < 256) {
        sGlobalFlags[arg0 >> 3] ^= (0x80 >> (arg0 & 7));
    }
}

void func_800322B4(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        sGlobalFlags[i] = 0;
    }
}

static u8 filler[0x1d60]; // BSSFILL