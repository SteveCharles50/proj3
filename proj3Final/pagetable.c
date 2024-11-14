#include <stdio.h>
#include <stdlib.h>

#define PAGE_TABLE_SIZE 8  // Number of entries in the page table

typedef struct {
    int frame_number;
    int last_access_time;  // For LRU tracking
} PageTableEntry;

PageTableEntry page_table[PAGE_TABLE_SIZE];

// Initialize the page table
void initialize_page_table() {
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i].frame_number = -1;  // -1 indicates that the page is not mapped
        page_table[i].last_access_time = 0;
    }
}

// Update access time for LRU policy
void update_access_time(int page_number, int current_time) {
    page_table[page_number].last_access_time = current_time;
}

// Find the least recently used page for replacement
int find_lru_page() {
    int lru_page = 0;
    int min_time = page_table[0].last_access_time;
    for (int i = 1; i < PAGE_TABLE_SIZE; i++) {
        if (page_table[i].frame_number != -1 && page_table[i].last_access_time < min_time) {
            lru_page = i;
            min_time = page_table[i].last_access_time;
        }
    }
    return lru_page;
}
