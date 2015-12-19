#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Memory.h"



int main()
{
    srand(time(NULL));
    int idUser = rand()%(1000-1)+1;

    MEM_MANAGER.length = 100;

    // definition of the blocks
    Segment s1,s2,s3;
    Block b1,b2,b3;

    s1.length = 50;
    s1.start_address = 0;
    s1.nextSegment = &s2;
    s1.firstBlock = &b1;

    s2.length = 25;
    s2.start_address = s1.length;
    s2.nextSegment = &s3;
    s2.firstBlock = &b2;

    s3.length = 25;
    s3.start_address = s2.start_address + s2.length;
    s3.nextSegment = NULL;
    s3.firstBlock = &b3;

    b1.length = s1.length;
    b1.id = -1;
    b1.start_address = s1.start_address;
    b1.nextBlock = NULL;

    b2.length = s2.length;
    b2.id = -1;
    b2.start_address = s2.start_address;
    b2.nextBlock = NULL;

    b3.length = s3.length;
    b3.id = -1;
    b3.start_address = s3.start_address;
    b3.nextBlock = NULL;

    MEM_MANAGER.firstSegment = &s1;

    viewMemoryState(MEM_MANAGER);

    allocate_First_Fit(55,idUser);
    //viewMemoryState(MEM_MANAGER);
    allocate_First_Fit(45,idUser);
    viewMemoryState(MEM_MANAGER);
    allocate_First_Fit(2,idUser);
    viewMemoryState(MEM_MANAGER);
    allocate_First_Fit(25,idUser);
    viewMemoryState(MEM_MANAGER);
    allocate_First_Fit(10,idUser);
    allocate_First_Fit(10,idUser);

    viewMemoryState(MEM_MANAGER);
    return 0;
}
