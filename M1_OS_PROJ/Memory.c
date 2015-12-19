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
                    newBlock->start_address = block->start_address + diff;
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

    Block* currentBlock = NULL;
    Block* predBlock = NULL;

    // Check if the block has a predecessor :
    bool_t hasPredecessor = TRUE;
    Segment* segment = MEM_MANAGER.firstSegment;
    while(segment != NULL) {
        if(segment->start_address == start_address) {
            currentBlock = segment->firstBlock;
            hasPredecessor = FALSE;
            break;
        }
        segment = segment->nextSegment;
    }
    if(hasPredecessor) {
        predBlock = findPrec(start_address);
        if(predBlock == NULL) {
            printf("Wrong start address !\n");
            return;
        }
        currentBlock = predBlock->nextBlock;
    }

    if(length < currentBlock->length) { // we have to create another block and to split the current block into two blocks : one free and one in use;
        Block* newBlock = malloc(sizeof(Block));
        newBlock->id = currentBlock->id;
        newBlock->length = currentBlock->length - length;
        newBlock->start_address = currentBlock->start_address + length;
        newBlock->nextBlock = currentBlock->nextBlock;
        currentBlock->nextBlock = newBlock;
        currentBlock->length = length;
        currentBlock->id = -1;
    } else if (length == currentBlock->length) {
        currentBlock->id = -1; // The block is entirely free
        if(currentBlock->nextBlock->id == -1) { // if the next block is free : merge these two blocks
           currentBlock->length += currentBlock->nextBlock->length;
           Block* tempBlock = currentBlock->nextBlock->nextBlock;
           free(currentBlock->nextBlock);
           currentBlock->nextBlock = tempBlock;
        }
    } else {
        printf("Incorrect length!\n");
    }

    if(hasPredecessor) {
        if(predBlock->id == -1) {// if the predecessor block is free we have to merge the predBlock and the currentBlock
            predBlock->length += currentBlock->length;
            predBlock->nextBlock = currentBlock->nextBlock;
            free(currentBlock);
        }
    }

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

Block* findPrec(const int start_address){

    Segment* segment = MEM_MANAGER.firstSegment;
    while(segment != NULL) {
        Block* block = segment->firstBlock;
        while(block != NULL) {
            if(block->nextBlock != NULL && start_address == block->nextBlock->start_address) {
                return block;
            }
            block = block->nextBlock;
        }
        segment = segment->nextSegment;
    }
    return NULL;
}


void defragmentation() {

}
