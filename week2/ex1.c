#include <stdio.h>
#include <inttypes.h>
#include <float.h>

int main()
{
    // Create a program that declares integer, float and double variables
    int a;
    float b;
    double c;

    // Find out how to assign maximum values for each variable
    a = INT32_MAX;
    b = FLT_MAX;
    c = DBL_MAX;

    // Print sizes and values of each variable
    printf("Variable \"a\" of type int has value %i and uses %li bits in memory.\n", a, 8 * sizeof a);
    printf("Variable \"b\" of type float has value %f and uses %li bits in memory.\n", b, 8 * sizeof b);
    printf("Variable \"c\" of type double has value %f and uses %li bits in memory.\n", c, 8 * sizeof c);

    return 0;
}