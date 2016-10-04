/*
Reference from
linux.die.net/man/mprotect
*/

#include "memlayout.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

unsigned int PAGESIZE = 4096;

int main(){
        struct memregion *thediff = (struct memregion*)malloc(sizeof(struct memregion)*20);
        struct memregion *regions = (struct memregion*)malloc(sizeof(struct memregion)*20);
        int numberOfRegion = get_mem_layout(regions, 20);

        char *mode[3] = {"RW", "RO","NO"};
        int i = 0;
        for(i=0;i<numberOfRegion;i++){ 
                printf("%p - %p, %s\n",regions[i].from, regions[i].to, mode[regions[i].mode]);
        }
                
        long *space = (long *)memalign(10*PAGESIZE, 4*PAGESIZE);
        mprotect(space,PAGESIZE, PROT_READ);
        
        int diff = get_mem_diff(regions, numberOfRegion, thediff, 20);
        printf("The difference: %d\n", diff);
        for(i=0;i<diff;i++){
		printf("%p - %p, %s\n",thediff[i].from, thediff[i].to, mode[thediff[i].mode]);
        }
        free(space);
        free(regions);
        free(thediff);
        return 0;
}

