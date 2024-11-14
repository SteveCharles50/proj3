Group 5 Project 3

  Steve Charles CSUID:2850400 50%

  Daniel Torres CSUID:2776824 50%


  Design Ideas
          part1:
                  Basic Idea: to take a sequence of virtual addresses as input and convert these addresses to 12 bit physical address


                  Methods:
                          returnBinary: Takes an array of nibbles and concatenates to create one 12 bit virtual address

                          pageNumb: takes in the full 12 bit value and shifts the bits 7 to the right and performs a mask to reveal the first
                                          5 bits that correspond to the page in the physical address

                          address: takes in the full 12 bit value and masks the first seven to reveal the address(offset) of the provided address

                          Main method:
                            -creates both input and output file names.
                            -Input file specified in argument line. Will show how to the input works in execution details
                            -opens the input file
                            -creates a buffer of size 3561 to hold the sequence file
                            -fread used to read and store from input file
                            -pagetable with hardcoded addresses spaces
                            -for loop which will run through the index of addresses in buffer
                            -variables:lastHexDigit, secondtolastHexDigit, thirdtolastHexDigit, fourthtolastHexDigit(never used because address is 12bits not 16)
                            -created array to pass to returnBinary to combine values
                            -used functions described above to get every part of address and concatenate
                            -multiplying the corresponding page number value from the pagetable array based on index by the page size(128) to get where the physical frame begins
                            -adding the offset value to the beginning portion of the frame to give the final physical address.
                            -The program will print out the physical addresses to the console as well as to the output file in 3 nibbles with 0x beginning to indicate hex.
                            -prints extra \n as requested
                            -closes both the input and the output file and returns zero for the main method

                  Sample input and output:
                    Input:
                        -compilation on mac machine: clang -o run mempart1.c
                        -running on mac machine: ./run part1test (using the test file for this example)
                    Output:
                        Here is the physical address: 0x144
                        Here is the physical address: 0x1A4
                        Here is the physical address: 0x0E8
                        Here is the physical address: 0x28C
                        Here is the physical address: 0x25C
                        Here is the physical address: 0x1B4
                        Here is the physical address: 0x218
                        Here is the physical address: 0x250

                        NOTE: Will create part1out which contains just the addresses
                              I also created part1result.txt which has the md5sum part1out




          Part 2:


                 mempart2.c
                 -current_time: A global counter used for tracking the Least Recently Used (LRU) pages.
                 Global Variables Functions

                 -translate_address(unsigned long virtual_address): This function takes a virtual address as input, extracts the page number and offset, and translates the virtual address to a physical address. If the page is not in memory (page fault), it handles the page fault by allocating a frame or performing LRU replacement if no frames are available. It updates the access time for the page and returns the physical address.
                 Main Function

                 -The main function performs the following steps:
                        1. Checks if the correct number of command-line arguments is provided.
                        2. Opens the input file specified by the user in binary read mode.
                        3. Opens an output file named "part2out" in write mode.
                        4. Initializes the page table.
                        5. Reads virtual addresses from the input file one by one.
                        6. For each address, it checks if the page is in memory and counts page faults.
                        7. Translates the virtual address to a physical address using the translate_address
                                function.
                        8. Writes the physical address to the output file in hexadecimal format.
                        9. Closes both the input and output files.
                        10. Writes the total number of page faults to a result file named "p2result.txt".
                        11. Appends the MD5 checksum of the output file to the result file using a system
                                command.


                 Phyframe.c
                 -MAX_FRAMES: Defines the number of available frames as 8 (1KB physical memory divided by 128 bytes per frame).
                 Global Variables
                 -frame_occupied: An array that tracks whether each frame is occupied. Frame 0 is reserved and marked as occupied.
                 Functions
                 -allocate_frame(): This function searches for the next available frame (starting from frame 1) and marks it as occupied. It returns the frame number if an available frame is found, or -1 if no frames are available.
                 -deallocate_frame(int frame_number): This function deallocates a specified frame by marking it as not occupied. It ensures that the frame number is within the valid range (1 to MAX_FRAMES - 1).

                 Pagetable.c

                 Constants
                 -PAGE_TABLE_SIZE: Defines the number of entries in the page table as 8. Data Structures
                 -PageTableEntry: A structure that represents an entry in the page table. It contains:
                 -frame_number: The frame number to which the page is mapped. A value of -1
                        indicates that the page is not mapped.
                 -last_access_time: The last access time of the page, used for LRU tracking.
                        Global Variables
                 -page_table: An array of PageTableEntry structures representing the page table. Functions
                 -initialize_page_table(): This function initializes the page table by setting the frame_number of each entry to -1 (indicating that the page is not mapped) and the last_access_time to 0.
                 -update_access_time(int page_number, int current_time): This function updates the access time of a specified page to the current time. It is used to track the last access time for LRU replacement.
                 -find_lru_page(): This function finds the least recently used page by iterating through the page table and comparing the last_access_time of each mapped page. It returns the page number of the least recently used page.


                 Input Output:
                    Input:
                        -compilation on mac machine: clang -o run mempart2.c
                        -running on mac machine: ./run part2sequence
                    Output:(only first couple of lines because it is long)

















