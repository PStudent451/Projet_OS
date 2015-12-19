#include "Memory.h"


void allocate_First_Fit(const int length,const int idUser){

    Segment* segment = MEM_MANAGER.firstSegment;
    while(segment != NULL) {
        Block* block = segment->firstBlock;
        while(block != NULL) {
            if(block->id == -1) { // if the block is not in use
                int diff = block->length - length;
                if(diff > 0) { // if the block's size is smaller than the free block's size.
                    Block* newBlock = malloc(sizeof(Block)); // creation of the block
                    newBlock->id = idUser;
                    newBlock->length = length;
                    newBlock->start_address = diff;
                    newBlock->nextBlock = block->nextBlock;
                    block->nextBlock = newBlock;
                    block->length = diff;
                    return;
                }
                if(diff == 0) {
                    block->id = idUser;
                    return;
                }
            }
            block = block->nextBlock;
        }
        segment = segment->nextSegment;
    }
    printf("Allocation failed : You have to wait or to try to defragmented\n");
}


void releaseMemoryArea(const int start_address, const int length){

}


void viewMemoryState(){

    Segment* segment = MEM_MANAGER.firstSegment;
    printf("Segments : \n");
    while(segment != NULL) {
        printf("[ ");
        Block* block = segment->firstBlock;
        while(block != NULL) {
            if(block->id == -1) {
                 printf("f");
            } else {
                 printf("u");
            }
            printf("[%d,%d] ",block->start_address,block->length + block->start_address);
            block = block->nextBlock;
        }
        printf(" ]\n");
        segment = segment->nextSegment;
    }
}


void defragmentation() {

}
