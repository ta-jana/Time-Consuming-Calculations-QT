#include "factorial.h"
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <QDebug>

Factorial::Factorial():destroy(false),pause(false)
{   }

long double Factorial::computeFactorial(int number)
{
    int num = number;
    //int numThreads = omp_get_num_procs()/2;
    int numThreads = 2;
    int sectionSize = std::floor(num / numThreads);

    int sectionStart[numThreads];
    int sectionEnd[numThreads];

    for (int i = 0; i < numThreads; i++) {
        sectionStart[i] = i * sectionSize + 1;
        sectionEnd[i] = (i + 1) * sectionSize;
    }

    //pro zbytek
    sectionEnd[numThreads - 1] = num;

    long double sections[numThreads];

    #pragma omp parallel num_threads(numThreads)
    {

        int threadId = omp_get_thread_num();
         qDebug() << "Parallel code thread   is: " << threadId << "..." ;
        sections[threadId] = _computeFactorial(sectionStart[threadId], sectionEnd[threadId]);
    }
    #pragma omp barrier


    long double result = 1;
    for(int i = 0; i < numThreads; i++){
        result *= sections[i];

    }

    return result;
}



long double Factorial::_computeFactorial(int start, int end)
{
    long double result = 1;
    for (int i = start; i <= end; i++) {
        result *= i;
/*        while(pause){
            //sleep
        }
        if(destroy){
            return result;
        }
        */
    }
    return result;
}



