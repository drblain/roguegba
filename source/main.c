#include <tonc.h>

typedef struct
{
    u32 x;
    u32 y;
} Pos;

int main(void) {
    irq_init(NULL);
    irq_add(II_VBLANK, NULL);
    REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;

    Pos player;
    player.x = SCREEN_WIDTH / 2;
    player.y = SCREEN_HEIGHT / 2;

    M3_CLEAR();

    while(1)
    {
        VBlankIntrWait();
        m3_plot(player.x, player.y, CLR_BLACK);
        key_poll();
        
        if (key_held(KEY_LEFT))
            player.x = (player.x + SCREEN_WIDTH - 1) % SCREEN_WIDTH;

        if (key_held(KEY_RIGHT))
            player.x = (player.x + 1) % SCREEN_WIDTH;

        if (key_held(KEY_UP))
            player.y = (player.y + SCREEN_HEIGHT - 1) % SCREEN_HEIGHT;

        if (key_held(KEY_DOWN))
            player.y = (player.y + 1) % SCREEN_HEIGHT;

        m3_plot(player.x, player.y, CLR_RED);
    }

    return 0;
}


