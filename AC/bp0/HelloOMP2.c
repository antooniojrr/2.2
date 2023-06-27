/* Compilar con:
gcc -O2 -fopenmp -o HelloOMP2 HelloOMP2.c
*/
#include <stdio.h>
#include <omp.h>
int main(void) {
#pragma omp parallel
printf("(%d:!!!Hello; ",
omp_get_thread_num());
printf("%d:world!!!)",
omp_get_thread_num());
return(0);
}
