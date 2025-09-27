#include <tonc.h>

typedef struct
{
    u32 x;
    u32 y;
} Pos;

int main(void) {
    irq_init(NULL);
    irq_add(II_VBLANK, NULL);
    REG_DISPCNT= DCNT_MODE5 | DCNT_BG2;

    while(1)
    {
        VBlankIntrWait();
    }

    return 0;
}


