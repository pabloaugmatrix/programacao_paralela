//
// Created by pabloaugmat on 05/04/25.
//

#include <stdio.h>
#include <omp.h>

int main(){
  #pragma omp parallel
  {
    int ID = omp_get_thread_num();
    printf("hello(%d) \n", ID);
    printf("world(%d) \n", ID);
  }
  return 0;
}
