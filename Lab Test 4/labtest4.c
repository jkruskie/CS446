#include <stdio.h>
#include <stdlib.h>

#define PAGE_NUMBER_MASK                0xFFFFF000
#define OFFSET_MASK                     0x00000FFF
#define PAGES                           8
#define OFFSET_BITS                     12
#define PAGE_SIZE                       (4 * 1024)
#define BUFFER_SIZE 10
char buff[BUFFER_SIZE];
int page_table[PAGES] = {6, 4, 3, 7, 0, 1, 2, 5};

int main(int argc, char *argv[])
{
    FILE *fptr = fopen(argv[1], "r");
    if(fptr == NULL)
    {
        printf("\n\nCould not open file. Aborting.\n\n");
        return 0;
    }

    while(fgets(buff, BUFFER_SIZE, fptr) != NULL)
    {
        unsigned int virtual_addr = atof(buff);
        unsigned int page_number = (virtual_addr & PAGE_NUMBER_MASK) >> OFFSET_BITS;
        unsigned int page_offset = virtual_addr & OFFSET_MASK;
        unsigned int physical_addr = (page_table[page_number] << OFFSET_BITS) + page_offset;

        printf("Virtual addr is %u: Page# = %u & Offset = %u. Physical addr = %u.\n", 
                virtual_addr, page_number, page_offset, physical_addr);
    }

    fclose(fptr);

    return 0;
}
