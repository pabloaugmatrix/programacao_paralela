//
// Created by pabloaugmat on 05/04/25.
//
#include <stdio.h>
#include <omp.h>

int main()
{
  int ID = 0;
  #pragma omp parallel
  {
    printf(" hello(%d) \n", ID);
    printf(" world(%d) \n", ID);
  }
  return 0;
}
