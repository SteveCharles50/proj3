#include <stdbool.h>

#define MAX_FRAMES 8  // Number of available frames (1KB physical memory / 128 bytes per frame)

bool frame_occupied[MAX_FRAMES] = {true, false, false, false, false, false, false, false};  // Frame 0 is reserved

// Function to find the next available frame
int allocate_frame() {
    for (int i = 1; i < MAX_FRAMES; i++) {
        if (!frame_occupied[i]) {
            frame_occupied[i] = true;
            return i;
        }
    }
    return -1;  // No available frame
}

// Function to deallocate a frame (used in LRU replacement)
void deallocate_frame(int frame_number) {
    if (frame_number >= 1 && frame_number < MAX_FRAMES) {
        frame_occupied[frame_number] = false;
    }
}
