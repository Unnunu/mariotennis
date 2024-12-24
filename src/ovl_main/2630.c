#include "common.h"

extern s8 D_80049AA8;

extern void* D_80061F7C;
extern void* D_80061FB4;

s8 func_800322E0(void) {
    return D_80049AA8;
}

void** func_800322EC(void) {
    return &D_80061F7C;
}

void** func_800322F8(void) {
    return &D_80061FB4;
}

INCLUDE_ASM("asm/nonmatchings/ovl_main/2630", func_80032304);

INCLUDE_ASM("asm/nonmatchings/ovl_main/2630", func_8003244C);

INCLUDE_ASM("asm/nonmatchings/ovl_main/2630", func_800324C0);

INCLUDE_ASM("asm/nonmatchings/ovl_main/2630", func_800324C8);

INCLUDE_ASM("asm/nonmatchings/ovl_main/2630", func_80032538);

INCLUDE_ASM("asm/nonmatchings/ovl_main/2630", func_800325A0);

INCLUDE_ASM("asm/nonmatchings/ovl_main/2630", func_800326FC);

INCLUDE_ASM("asm/nonmatchings/ovl_main/2630", func_80032910);

INCLUDE_ASM("asm/nonmatchings/ovl_main/2630", func_80032990);

INCLUDE_ASM("asm/nonmatchings/ovl_main/2630", func_8003299C);

INCLUDE_ASM("asm/nonmatchings/ovl_main/2630", func_800329A8);
