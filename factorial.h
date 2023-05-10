#ifndef FACTORIAL_H
#define FACTORIAL_H


class Factorial
{
public:
    Factorial();

    long double computeFactorial(int number);
    bool destroy;
    bool pause;

private:
    long double _computeFactorial(int start, int end);

};

#endif // FACTORIAL_H
