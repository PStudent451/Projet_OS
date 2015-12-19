#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef enum {
       FALSE,
       TRUE
} bool_t;

// structure representing a block of memory
// These blocks are linked together to form a list sorted by ascending addresses
typedef struct Block
{
    int id; // must correspond to the id of the user if the user want to release this memory block : id = -1 if the block is free
    int start_address;
    int length;
    struct Block* nextBlock;
}Block;

// structure representing a segment
// These blocks are linked together to form a list sorted by ascending addresses
typedef struct Segment
{
    int start_address;
    int length;
    struct Segment* nextSegment;
    Block* firstBlock;     // Pointer to the first Block of the block's chained list
}Segment;

// structure managing the memory blocks
typedef struct Memory_Manager
{
    int length; // Total size of the memory
    Segment* firstSegment; // Pointer to the first Segment of the chained list
}Memory_Manager;

Memory_Manager MEM_MANAGER;


// Function used to allocate a Block of memory using first-fit algorithm (the parameter length is the size of the block going to be allocated)
void allocate_First_Fit(const int length,const int idUser);


// Function used to release a Block of memory
void releaseMemoryArea(const int start_address, const int length);


// Function which find and return the predecessor of the block having the first address equal to the first address parameter.
Block* findPrec(const int start_address);

// Function used to view the memory occupation
void viewMemoryState();

// Function used to defragmented the memory
void defragmentation();

#endif // MEMORY_H_INCLUDED
