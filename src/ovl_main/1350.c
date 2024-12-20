#include "common.h"

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_80031000);

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_80031164);

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_8003125C);

INCLUDE_ASM("asm/nonmatchings/ovl_main/1350", func_80031290);

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
