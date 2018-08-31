#include "time.h"

int main() {

  clock_t start, finish;  //  declare start and final time
  start = clock();
  // your code is here, do something and then get final time
  finish = clock();
  ( (finish - start)/CLOCKS_PER_SEC );
}
