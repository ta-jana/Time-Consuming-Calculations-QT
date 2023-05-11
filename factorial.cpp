#include "factorial.h"
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <QDebug>
#include <thread>



Factorial::Factorial(QProgressBar &bar)
    :destroy(false),
    pause(false),
    progressBarFact(0),
    progressBar(bar)
{

}

long double Factorial::computeFactorial(int number)
{
    int num = number;
    int numThreads = omp_get_num_procs()/2;
    //int numThreads = 2;
    int sectionSize = std::floor(num / numThreads);

    int sectionStart[numThreads];
    int sectionEnd[numThreads];

    for (int i = 0; i < numThreads; i++) {
        sectionStart[i] = i * sectionSize + 1;
        sectionEnd[i] = (i + 1) * sectionSize;
    }

    //for the last value
    sectionEnd[numThreads - 1] = num;

    long double sections[numThreads];

    #pragma omp parallel num_threads(numThreads) shared(progressBarFact)
    {

        int threadId = omp_get_thread_num();
        sections[threadId] = _computeFactorial(sectionStart[threadId], sectionEnd[threadId]);
    }
    #pragma omp barrier


    long double result = 1;
    for(int i = 0; i < numThreads; i++){
        result *= sections[i];

    }
progressBarFact = 0;
    return result;
}



long double Factorial::_computeFactorial(int start, int end)
{
    long double result = 1;
#pragma omp parallel for shared(progressBarFact)
    for (int i = start; i <= end; i++) {

        result *= i;

    #pragma omp atomic
    progressBarFact++;

    int value = progressBarFact;
    int clampedValue = std::clamp(value, 0, value*2-1);
    qDebug() << "progressBarFact++;   is: " << clampedValue << "..." ;

    progressBar.setValue(clampedValue);

        while(pause)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        if(destroy)
        {
            #pragma omp cancel for
         //   return result;
        }

    }
    return result;
}



