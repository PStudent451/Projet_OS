#include "Memory.h"



int main()
{
    initializeMemoryManager();
    // Generation of the user's id
    srand(time(NULL));
    int idUser = rand()%(1000-1)+1;

    do
    {
        system("CLS");
        printf("\n\t Mini-Project on Memory Management by Paul Fryson and Richard Gruet \n");
        unsigned int choice=0;

        do
        {
            printf("\nWhat do you want to do ? \n\n");
            printf("1. Allocation of a memory area\n");
            printf("2. Release of a memory area\n");
            printf("3. Viewing the memory occupation\n");
            printf("4. Defragmentation of the memory\n");
            printf("5. Quit\n\n");
            printf("Your choice : ");
            scanf("%u",&choice);
        }
        while(choice > 5 || choice == 0);


        switch(choice)
        {
            case 1 :
                allocation_menu(idUser);
                pause();
                break;
            case 2 :
                release_menu(idUser);
                pause();
                break;
            case 3 :
                viewMemoryState();
                pause();
                break;
            case 4 :
                defragmentation();
                pause();
                break;
            case 5 :
                return 0;
            default :
                return -1;
        }
    }
    while(TRUE);


    return 0;
}
