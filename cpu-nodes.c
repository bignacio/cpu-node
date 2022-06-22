/**
 * @file cpu-nodes.c
 * @author Bira Ignacio
 * @brief CPU Core and NUMA nodes identification tool
 * @version 1.0
 * @date 2022-05-20
 *
 * @copyright Copyright Bira Ignacio (c) 2022
 *
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <linux/getcpu.h>
#include <sched.h>

const size_t MaxCoreCount = 2<<12;
const size_t CPUSetMaskSize = sizeof(cpu_set_t);

bool getCoreAffinityMask(cpu_set_t* mask){
    int result = sched_getaffinity(0, CPUSetMaskSize, mask);

    if(result != 0){
        printf("Failed to get core affinity mask. Error %d\n", result);
        return false;
    }


    return true;
}

// Informative functionality: prints all cores the process is can use
void printCurrentCoreUsage() {
    cpu_set_t mask;

    if(getCoreAffinityMask(&mask)){
        printf("Current process affinity list: ");

        for(size_t i = 0 ; i < MaxCoreCount ; i++){
            if(CPU_ISSET_S(i, CPUSetMaskSize, &mask)){
                printf("%ld ",i);
            }
        }

        printf("\n");
    }
}

bool getCoreNUMANode(unsigned int coreNum, const cpu_set_t* mask, unsigned int* numaNode){
    if(CPU_ISSET_S(coreNum, CPUSetMaskSize, mask)){
        int result = sched_setaffinity(0, CPUSetMaskSize, mask);

        if(result != 0){
            return false;
        }

        unsigned int currentCoreNum;
        if(getcpu(&currentCoreNum, numaNode) != 0){
            return false;
        }
        return true;
    }

    return false;
}

bool printCPUInfo(){
    printCurrentCoreUsage();

    cpu_set_t mask;
    int coresFound = 0;

    if(getCoreAffinityMask(&mask)){
        printf("\nFinding NUMA nodes for a maximum of %ld cores\n", MaxCoreCount);

        for(unsigned int i = 0 ; i < MaxCoreCount ; i++){
            unsigned int numaNode;

            if(getCoreNUMANode(i, &mask, &numaNode)){
                printf("Core %d on node %d\n", i, numaNode);
                coresFound++;
            }
        }
    }

    printf("\nFound %d cores\n\n", coresFound);
    return true;
}

int main(){
    if(printCPUInfo()){
        return 0;
    }

    printf("Error getting cpu information.\n");

    return 1;
}
