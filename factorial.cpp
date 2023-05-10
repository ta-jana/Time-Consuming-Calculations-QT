#include "factorial.h"
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

Factorial::Factorial(int number):destroy(false),pause(false)
{

    int num = number;
    int numThreads = omp_get_num_procs()/2;

    int sectionSize = std::floor(num / numThreads);

    int sectionStart[numThreads];
    int sectionEnd[numThreads];

    for (int i = 0; i < numThreads; i++) {
        sectionStart[i] = i * sectionSize + 1;
        sectionEnd[i] = (i + 1) * sectionSize;
    }

    //pro zbytek
    sectionEnd[numThreads - 1] = num;

    int sections[numThreads];

#pragma omp parallel shared(destroy,pause)
{
    #pragma omp parallel num_threads(numThreads)
    {

        int threadId = omp_get_thread_num();
        sections[threadId] = computeFactorial(sectionStart[threadId], sectionEnd[threadId]);
    }
}

    int result = 0;
    for(int i = 0; i < numThreads; i++){
        result *= sections[i];
    }

    printf("Factorial is : %d",result);


}

int Factorial::computeFactorial(int start, int end)
{
    int result = 1;
    for (int i = start; i <= end; i++) {
        result *= i;
        while(pause){
            //sleep
        }
        if(destroy){
            return result;
        }
    }
    return result;
}

