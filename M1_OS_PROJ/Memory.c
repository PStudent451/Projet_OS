#include "Memory.h"

void initializeMemoryManager() {

    MEM_MANAGER.length = 100;

    // definition of the Segments
    Segment* s1 = malloc(sizeof(Segment));
    Segment* s2 = malloc(sizeof(Segment));
    Segment* s3 = malloc(sizeof(Segment));

    // definition of the Blocks
    Block* b1 = malloc(sizeof(Block));
    Block* b2 = malloc(sizeof(Block));
    Block* b3 = malloc(sizeof(Block));

    s1->length = 50;
    s1->start_address = 0;
    s1->nextSegment = s2;
    s1->firstBlock = b1;

    s2->length = 25;
    s2->start_address = s1->length;
    s2->nextSegment = s3;
    s2->firstBlock = b2;

    s3->length = 25;
    s3->start_address = s2->start_address + s2->length;
    s3->nextSegment = NULL;
    s3->firstBlock = b3;

    b1->length = s1->length;
    b1->id = -1;
    b1->start_address = s1->start_address;
    b1->nextBlock = NULL;

    b2->length = s2->length;
    b2->id = -1;
    b2->start_address = s2->start_address;
    b2->nextBlock = NULL;

    b3->length = s3->length;
    b3->id = -1;
    b3->start_address = s3->start_address;
    b3->nextBlock = NULL;

    MEM_MANAGER.firstSegment = s1;
}


void allocate_First_Fit(const int length,const int idUser){

    Segment* segment = MEM_MANAGER.firstSegment;
    while(segment != NULL) {
        Block* block = segment->firstBlock;
        while(block != NULL) {
            if(block->id == -1) { // if the block is not in use
                int diff = block->length - length;
                if(diff == 0) {
                    block->id = idUser;
                    printf("Allocation of a block with a size of %d using First Fit algorithm done\n",length);
                    return;
                }
                if(diff > 0) { // if the block's size is smaller than the free block's size.
                    Block* newBlock = malloc(sizeof(Block)); // creation of the block
                    newBlock->id = idUser;
                    newBlock->length = length;
                    newBlock->start_address = block->start_address + diff;
                    newBlock->nextBlock = block->nextBlock;
                    block->nextBlock = newBlock;
                    block->length = diff;
                    printf("Allocation of a block with a size of %d using First Fit algorithm done\n",length);
                    return;
                }

            }
            block = block->nextBlock;
        }
        segment = segment->nextSegment;
    }
    printf("Allocation failed : You have to wait or to try to defragmented\n");
}


void allocate_Best_Fit(const int length,const int idUser){

    Block* bestBlock = NULL;

    Segment* segment = MEM_MANAGER.firstSegment;
    while(segment != NULL) {
        Block* block = segment->firstBlock;
        while(block != NULL) {
            if(block->id == -1) {// if the block is free
                int diff = block->length - length;
                if(diff == 0) { // if the block match perfectly just do the allocation
                    block->id = idUser;
                    printf("Allocation of a block with a size of %d using Best Fit algorithm done\n",length);
                    return;
                }
                if(diff > 0) { // if the block is large enough
                    if(bestBlock == NULL || diff < (bestBlock->length - length)) {
                        bestBlock = block;
                    }
                }
            }
            block = block->nextBlock;
        }
        segment = segment->nextSegment;
    }

    if(bestBlock == NULL) {
        printf("Allocation failed : You have to wait or to try to defragmented\n");
    } else {
        int diff = bestBlock->length - length;
        Block* newBlock = malloc(sizeof(Block)); // creation of the block
        newBlock->id = idUser;
        newBlock->length = length;
        newBlock->start_address = bestBlock->start_address + diff;
        newBlock->nextBlock = bestBlock->nextBlock;
        bestBlock->nextBlock = newBlock;
        bestBlock->length = diff;
        printf("Allocation of a block with a size of %d using Best Fit algorithm done\n",length);
    }
}


void allocate_Worst_Fit(const int length,const int idUser){

    Block* worstBlock = NULL;

    Segment* segment = MEM_MANAGER.firstSegment;
    while(segment != NULL) {
        Block* block = segment->firstBlock;
        while(block != NULL) {
            if(block->id == -1) {// if the block is free
                if(block->length - length > 0) { // if the block is large enough
                    if(worstBlock == NULL || block->length > (worstBlock->length)) {
                        worstBlock = block;
                    }
                }
            }
            block = block->nextBlock;
        }
        segment = segment->nextSegment;
    }


    if(worstBlock == NULL) {
        printf("Allocation failed : You have to wait or to try to defragmented\n");
    } else {
        int diff = worstBlock->length - length;
        if(diff == 0) { // if the block match perfectly just do the allocation
            worstBlock->id = idUser;
            return;
        }
        Block* newBlock = malloc(sizeof(Block)); // creation of the block
        newBlock->id = idUser;
        newBlock->length = length;
        newBlock->start_address = worstBlock->start_address + diff;
        newBlock->nextBlock = worstBlock->nextBlock;
        worstBlock->nextBlock = newBlock;
        worstBlock->length = diff;
        printf("Allocation of a block with a size of %d using Worst Fit algorithm done\n",length);
    }
}


void allocation_menu(const int idUser){
    system("CLS");
    unsigned int length = 0;
    unsigned int choice=0;
    do
    {
        printf("\nWhat algorithm do you want to use ? \n\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Quit\n\n");
        printf("Your choice : ");
        scanf("%u",&choice);
        printf("\n");
    }
    while(choice > 4 || choice == 0);

    if(choice != 4) {
        printf("Size of the block needed : ");
        scanf("%u",&length);
    }

    switch(choice)
    {
        case 1 :
            allocate_First_Fit(length,idUser);
            break;
        case 2 :
            allocate_Best_Fit(length,idUser);
            break;
        case 3 :
            allocate_Worst_Fit(length,idUser);
            break;
        case 4 :
            return;
        default :
            return;
    }
}


void releaseMemoryArea(const int start_address, const int length,const int idUser){

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
    if(currentBlock->id != idUser) {
        if(idUser == -1){
            printf("You can't release a free block!\n");
        } else {
            printf("You can't release this block because it doesn't belong to you.\n");
        }
        return;
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
        return;
    }

    if(hasPredecessor) {
        if(predBlock->id == -1) {// if the predecessor block is free we have to merge the predBlock and the currentBlock
            predBlock->length += currentBlock->length;
            predBlock->nextBlock = currentBlock->nextBlock;
            free(currentBlock);
        }
    }
    printf("Block released!\n");

}


void release_menu(const int idUser) {
    viewMemoryState();

    unsigned int start_address = 0;
    unsigned int length = 0;
    printf("\nThe start address must be the address of a block in use.\n");
    printf("Start address : ");
    scanf("%u",&start_address);
    printf("Size : ");
    scanf("%u",&length);

    releaseMemoryArea(start_address,length,idUser);
}


void viewMemoryState(){

    system("CLS");
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
    printf("\n");
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

    Segment* segment = MEM_MANAGER.firstSegment;
    while(segment != NULL) {
        Block* block = segment->firstBlock;
        Block* succBlock = NULL;
        while(block != NULL) {
            if(block->id == -1) { // if the block is free
                succBlock = block->nextBlock;
                if(succBlock == NULL) {
                    break;
                }
                if(succBlock->id == -1) { // we have to merge these two free blocks
                    block->length += succBlock->length;
                    Block* tempBlock = succBlock->nextBlock;
                    free(succBlock);
                    block->nextBlock = tempBlock;
                } else { // we have to swap the value of the two blocks
                    int s_id = succBlock->id;
                    int s_length = succBlock->length;
                    succBlock->id = block->id; // should be -1
                    succBlock->start_address = block->start_address + succBlock->length;
                    succBlock->length = block->length;
                    block->id = s_id;
                    block->length = s_length;
                    block = block->nextBlock;
                }
            } else {
                block = block->nextBlock;
            }
        }

        segment = segment->nextSegment;
    }
    system("CLS");
    printf("Defragmentation done!");
}

void pause() {
    int c;
    printf("\nPress Enter to go back to the menu...\n");
    fflush(stdin);
    while ((c = getchar()) != '\n' && c != EOF)
    {}
}
