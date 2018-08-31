#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <armadillo>
#include "time.h"

using namespace std;
using namespace arma;

#define TYPE double

void general_algorithm            (int n, TYPE *a, TYPE *b, TYPE *c, TYPE *v, TYPE *f);
void allocating                   (int n);
void initiate_abc                 (int n, TYPE *a, TYPE *b, TYPE *c, TYPE *f);

TYPE u (TYPE x){
  return 1.0 - ( 1 - exp(-10.0)) * x - exp(-10.0 * x);
}




void initiate_abc(int n, TYPE *a, TYPE *b, TYPE *c, TYPE *f) {

  TYPE h = 1.0 / (n + 1.0);
  for(int i = 0; i < n; i ++) {
    if(i > 0 && i < n) {
      a[i] = -1.0;
      c[i] = -1.0;
    }
    b[i] = 2.0;
    f[i] = pow(h, 2.0) * 100.0 * exp(-10.0 * i * h);
  }
}


void general_algorithm(int n, TYPE *a, TYPE *b, TYPE *c, TYPE *v, TYPE *f) {

  TYPE btemp;
  TYPE *temp = new TYPE[n+2];
  int i;
  btemp = b[1];
  v[1] = f[1]/btemp;

  for(i = 2; i <= n; i ++) {
    temp[i] = c[i - 1] / btemp;
    btemp = b[i] - a[i] * temp[i];
    v[i] = (f[i] - a[i] * v[i - 1]) / btemp;
  }

  for(i = n - 1; i >= 1; i --) {
    v[i] -= temp[i - 1] * v[i + 1];
  }
}


void allocating(int n) {

  TYPE *a         = new TYPE[n - 1];
  TYPE *b         = new TYPE[n];
  TYPE *c         = new TYPE[n - 1];
  TYPE *v         = new TYPE[n];
  TYPE *f         = new TYPE[n];
  TYPE *f_LU      = new TYPE[n];

  TYPE h = 1.0 / (n + 1.0);

  initiate_abc(n, a, b, c, f);
  general_algorithm(n, a, b, c, v, f);
  for (int i = 1; i <= n; i++){
		cout << a[i] << " " << b[i] << " " << c[i] << " " << v[i]  -  u(i * h)<< " " << f[i] << endl;
	}
  // Freeing the memory
  delete [] a;
  delete [] b;
  delete [] c;
  delete [] v;
  delete [] f;
  delete [] f_LU;
}







int main() {

  allocating(10);
  // for(n = 10; n <= 1000; n =* 10) {}

}
