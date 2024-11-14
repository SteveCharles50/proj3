#include <stdio.h>
#include <stdlib.h>
#include "phyframe.c"
#include "pagetable.c"

int current_time = 0;  // Global counter for LRU tracking

unsigned long translate_address(unsigned long virtual_address) {
    unsigned int page_number = (virtual_address >> 7) & 0xF;
    unsigned int offset = virtual_address & 0x7F;

    if (page_table[page_number].frame_number == -1) {
        // Page fault handling
        int frame_number = allocate_frame();
        if (frame_number == -1) {
            // Perform LRU replacement
            int lru_page = find_lru_page();
            frame_number = page_table[lru_page].frame_number;
            page_table[lru_page].frame_number = -1;
            deallocate_frame(frame_number);
        }
        page_table[page_number].frame_number = frame_number;
    }

    update_access_time(page_number, ++current_time);
    unsigned long physical_address = (page_table[page_number].frame_number << 7) | offset;
    return physical_address;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_sequence_filename>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "rb");
    if (!input_file) {
        perror("Failed to open input file");
        return 1;
    }

    FILE *output_file = fopen("part2out", "w");
    if (!output_file) {
        perror("Failed to open output file");
        fclose(input_file);
        return 1;
    }

    initialize_page_table();
    unsigned long virtual_address;
    int page_faults = 0;

    while (fread(&virtual_address, sizeof(unsigned long), 1, input_file) == 1) {
        unsigned int page_number = (virtual_address >> 7) & 0xF;
        if (page_table[page_number].frame_number == -1) {
            page_faults++;
        }
        unsigned long physical_address = translate_address(virtual_address);
        fprintf(output_file, "0x%04lx\n", physical_address);
    }

    fclose(input_file);
    fclose(output_file);

    // Write page fault count and md5sum to p2result.txt
    FILE *result_file = fopen("p2result.txt", "w");
    fprintf(result_file, "Page faults: %d\n", page_faults);
    fclose(result_file);

    system("md5sum part2out >> p2result.txt");

    return 0;
}
