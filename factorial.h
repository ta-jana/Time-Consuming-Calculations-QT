#ifndef FACTORIAL_H
#define FACTORIAL_H

#include <QProgressBar>

class Factorial
{
public:
    Factorial(QProgressBar &bar);

    long double computeFactorial(int number);
    bool destroy;
    bool pause;
    int progressBarFact;

private:
    long double _computeFactorial(int start, int end);

    QProgressBar &progressBar;


};

#endif // FACTORIAL_H
