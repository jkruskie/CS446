#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LINELENGTH 10
#define PAGESIZE 256
int pageTable[PAGESIZE]; 
int pageFrame[PAGESIZE];
#define TLB_LENGTH 16
int TLBPage[TLB_LENGTH];
int TLBFrame[TLB_LENGTH];
int TLBNum = 0;
int TLBCounter = 0;
#define FRAMELENGTH 256
char readBacker[FRAMELENGTH];
#define physicalMemoryBytes 65536
int physicalMemory[physicalMemoryBytes];
int pageFault = 0;

void initializeInfo(int *arr, int n) {

        int i = 0;

        for(i = 0; i < n; i++) {
                arr[i] = -1;
        }
}
int readBackStore(int page) {

        int i = 0, j = 0, availableFrame = 0, startFrameIndex = 0;

        /* SEEK_SET is in fseek() - it seeks from the beginning of the file */
        if(fseek(backStore, page * PAGESIZE, SEEK_SET) != 0) {
                printf("ERROR\n");
        }

        if(fread(readBacker, sizeof(signed char), PAGESIZE, backStore) == 0) {
                printf("ERROR\n");
        }

        /* Get available frame by looking for unused index in pageFrame */
        for(i =0; i < PAGESIZE; i++) {

                if(pageFrame[i] == -1) {

                        pageFrame[i] = 0;
                        availableFrame = i;
                        break;
                }

        }

        /* Start at specific index for each frame */
        startFrameIndex = PAGESIZE * availableFrame;

        for(j = 0; j < PAGESIZE; j++) {

                physicalMemory[startFrameIndex] = readBacker[j];
                startFrameIndex++;

        }

        pageTable[page] = availableFrame;
        pageFault++;
        
        return availableFrame;

}

int changeAddress(int logAddress) {


        int page = 0, i = 0, frameNum = -1, offset = 0;
        double origPage, decPage, intPage, offsetDub = 0.0;

        page = logAddress/PAGESIZE;

        origPage = (double)logAddress/PAGESIZE;
        decPage = modf(origPage, &intPage);

        offsetDub = decPage * PAGESIZE;
        offset = (int)offsetDub;


        /* check if page is in TLB frame */
        for(i = 0; i< TLB_LENGTH; i++) {

                if(TLBPage[i] == page) {

                        frameNum = TLBFrame[i];
                        TLBNum++;
                }

        }

        /* if page was not in TLB, read from BACK_STORE, or
        get page from pageTable */
        if(frameNum == -1) {

                /* if not in either, page fault */
                if(pageTable[page] == -1) {

                        frameNum = readBackStore(page);

                } else {
                        /* if not in TLB frame, get from pageTable */
                        frameNum = pageTable[page];
                }

                TLBPage[TLBCounter%TLB_LENGTH] = page;
                TLBFrame[TLBCounter%TLB_LENGTH] = frameNum;
                TLBCounter++;

        }

        return (frameNum * PAGESIZE) + offset;  
}


int main(int argc, char *argv[]) {

        int translations = 0, logAddress = 0, address = 0;
        char line[LINELENGTH];

        if(argc != 2) {
                printf("Please enter two arguements.\nEx: ./file addresses.txt\n");
        }

        /* Open Files */
        backStore = fopen("BACKING_STORE.bin", "r");

        if(backStore == NULL) {

                printf("1 Null\n");
                return -1;
        }

        addressFile = fopen(argv[1], "r");

        if(addressFile == NULL) {

                printf("2 Null\n");
                return -1;
        }

        /* Initialize arrays */
        initializeInfo(pageTable, PAGESIZE);
        initializeInfo(pageFrame, PAGESIZE);
        initializeInfo(TLBPage, TLB_LENGTH);
        initializeInfo(TLBFrame, TLB_LENGTH);
        
        /* Go through each line of address file and pass logical address
        to Change address, which will translate the ino to a physical address */
        while(fgets(line, LINELENGTH, addressFile) != NULL) {

                logAddress = atoi(line);
                address = changeAddress(logAddress);

                printf("Logical Address: %d, Physical Memory: %d, Value: %d\n", logAddress, address, physicalMemory[address]);
                translations++;

        }

        /* Print out results */
        printf("\n*** Final Info ***\n");
        printf("Number of translations: %d\n", translations);
        printf("Number of Page Faults: %d\n", pageFault);
        printf("Page Fault Rate: %f\n",(float)pageFault/(float)translations);
        printf("Number of TLB Hits: %d\n", TLBNum);
        printf("TLB Rate: %f\n", (float)TLBNum/(float)translations);

        /* Close files */
        fclose(addressFile);
        fclose(backStore);

        return 0;
}