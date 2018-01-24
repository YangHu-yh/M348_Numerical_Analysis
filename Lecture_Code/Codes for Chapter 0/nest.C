////////////////////////////////////////////////////////////////////////////////////////
//  NESTED MULTIPLICATION (HORNER"S METHOD)
//
//  Evaluation by nested multiplication of the polynomial
//    p(x) = c[n] x^n + c[n-1] x^{n-1} + ... + c[0]
////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

double nest(int n, double c[], double x) {
  double p = c[n];
  for(int i=n-1; i>=0; i--) {
    p = p*x + c[i];
  }
  return p;
}

int main() {
  const int n=4;
  double c[n+1] = {-1,5,-3,3,2};
  double x = 0.5;

  cout << "p(x) = " << c[0];
  for(int i = 1; i <= n; i++) {
    cout << " + " << c[i] << "*x^" << i;
  }
  cout << endl;

  double p = nest(n,c,x);

  cout << "p(1/2) = " << p << "\n";
}
