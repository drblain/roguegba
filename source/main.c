#include <tonc.h>

int main(void) {
    irq_init(NULL);
    irq_add(II_VBLANK, NULL);
    
    // --- Initial setup ---
    // Initialize video mode
    // Load assets into VRAM
    // Set up initial game state
    // Set up game inputs

    while(1)
    {
        // --- Input handling --- 

        // --- Game logic update ---

        // --- Rendering ---

        VBlankIntrWait();

        // --- VBlank operations ---
    }

    return 0;
}


