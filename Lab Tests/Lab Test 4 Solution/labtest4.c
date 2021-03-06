#include <stdio.h>

#define PAGE_NUMBER_MASK 255		//2^8 -1
#define OFFSET_MASK 255			// 2^8 -1
#define PAGES 8
#define OFFSET_BITS  8			//Number of bits to represent an offset = number of bits to 							represent page size.
#define PAGE_SIZE 256	

int main(int argc, char *argv[]) {
	unsigned int page_number, frame_number;
	int offset;
	unsigned int virtual_address, physical_address;
	char buff[10];
        int page_table[PAGES] = {6,4,3,7,0,1,2,5};
	/*Print Usage*/
	if (argc != 2) {
		fprintf(stderr,"Usage: ./a.out <virtual address input file>\n");
		return -1;
	}

	/*Declare a file pointer fptr. fopen initializes an obect of type file.
	 This is stored in fptr. The mode 'r' indicates that the file is for 
	read only purpose.*/
	FILE *fptr = fopen(argv[1], "r");

	if (fptr == NULL) {
		printf("Error in opening file \n");
		return -1;
	}
	/*Read 10-1 = 9 characters from the file at a time. 
	These characters are stored in buff*/

	while(fgets(buff, 10, fptr) != NULL) {
		virtual_address = atoi(buff);
		/*Mask the page number, this will enable you get your 
		page number bits, then do a bit shift to the right by the 
		number of offset bits. To get all the page number bits.
		The compiler automatically outputs the correct decimal 
		representation of it.*/
		page_number = (virtual_address >> OFFSET_BITS) & PAGE_NUMBER_MASK;
		frame_number = page_table[page_number];
		offset = virtual_address & OFFSET_MASK;
		/*Move the bits in frame_number to left by the number of bits in
		the offset bit, then or it will the offset to get the physical address.*/
		physical_address = (frame_number << OFFSET_BITS) | offset;
		printf("Virtual addr is %d: Page# = %d & Offset = %d. Physical addr = %d. \n", 			virtual_address, page_number, offset, physical_address);
	}
	/*Close the file.*/
 	fclose(fptr);

	return 0;
}
