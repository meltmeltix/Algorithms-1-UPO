/* Esercizio:
    lavora con puntatori a funzioni per implementare una funzione num_apply
    per manipolare ogni elemento di un array di double 
*/

#include <stdio.h>
#include <math.h>
#include <stddef.h>

void num_apply(int size, double *ary, double (*fun)(double)) {
    for(unsigned short int i = 0; i < size; i++) {
        ary[i] = fun(ary[i]);
    }
}

double sqr(double x) { return x * x; }
double mult2(double x) { return 2 * x; }

int main() {
    double dary[] = {4, 16, 36};
    size_t n = sizeof dary / sizeof dary[0];

    double (*sqrPtr)(double) = &sqr;
    double (*mult2Ptr)(double) = &mult2;
    double (*sqrtPtr)(double) = &sqrt;

    num_apply(n, dary, sqrtPtr); // -> {2, 4, 6}
    printf("Modified Array after sqrt: {%lf, %lf, %lf}\n", dary[0], dary[1], dary[2]);

    num_apply(n, dary, mult2Ptr); // -> {4, 8, 12}
    printf("Modified Array after mult2: {%lf, %lf, %lf}\n", dary[0], dary[1], dary[2]);

    num_apply(n, dary, sqrPtr); // -> {16, 64, 144}
    printf("Modified Array after sqr: {%lf, %lf, %lf}\n", dary[0], dary[1], dary[2]);

    return 0;
}
