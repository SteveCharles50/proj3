#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>


uint32_t returnBinary(uint32_t value[3]) {
    uint32_t final = (value[0] << 8) | (value[1] << 4) | value[2];
    return final;
}

//getting the first five bits
uint32_t pageNumb(uint32_t value){
    return (value >> 7) & 0x1F;
}


//gettng the last 7 bits
uint32_t address(uint32_t value){
    return value & 0x7F;
}



int main(int argc, char* argv[]){

    const char *finalFile = "part1out";

    FILE *fptr = fopen(finalFile, "w");

	FILE *file;
	file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

	//array that will store all of the hex characters
    uint64_t buffer[3561];

	fread(buffer, sizeof(uint64_t), 3561 , file);

    int tracker = 0;
    int pageTable[7] = {2,4,1,7,3,5,6};
	for(int i = 0; i < 3561; i++){

        uint64_t last2bytes = buffer[i] & 0xFFFF;

        //nibble representation
        uint8_t lastHexDigit = buffer[i] & 0xF;
        uint8_t secondtolastHexDigit = (buffer[i] >> 4) & 0xF;
        uint8_t thirdtolastHexDigit = (buffer[i] >> 8) & 0xF;
        uint8_t fourthtolastHexDigit = (buffer[i] >> 16) & 0xF;


        //array creation to pass to the function that makes the
        uint32_t arr[] = {thirdtolastHexDigit, secondtolastHexDigit, lastHexDigit};

        //printing the binary representation
        uint32_t finalResult = returnBinary(arr);
        uint32_t finalpageNumb = pageNumb(finalResult);
        uint32_t finalAddress = address(finalResult);

        //converting this representation into the physical address
        uint32_t finalPhysPage = 128*pageTable[finalpageNumb];
        uint32_t finalPhysAddress = finalAddress;
        uint32_t decimalFormPhy = finalPhysPage + finalPhysAddress;
        printf("Here is the physical address: 0x%03X \n", decimalFormPhy);
        fprintf(fptr, "0x%03X\n", decimalFormPhy);
        tracker++;
    }

    FILE *result_file = fopen("p1result.txt", "w");
    fclose(result_file);
    system("md5sum part1out >> p1result.txt");

    fprintf(fptr,"\n");
    fclose(fptr);
    fclose(file);
	return 0;
}
