/****************************************************************
Solve ax^2 + bx + c = 0 for real roots

return 0 in no error, 1 otherwise
****************************************************************/
#include <iostream>
#include <cmath>
using namespace std;

int quadraticFormula(double a, double b, double c, double& r1, double& r2) {
  double discriminant = b*b - 4*a*c;

  if(discriminant < 0 || a == 0) return 1;

  if(b < 0) {
    // multiply through by -1, so now b>=0
    a = -a; b = -b; c = -c;
  }

  r1 = -(b + sqrt(discriminant)) / (2*a);
  r2 = -2*c / (b + sqrt(discriminant));

  return 0;
}

int main() {
  double a,b,c,r1,r2;

  cout << "Solve ax^2 + bx + c = 0 for real roots.\n" << "Enter a,b,c: ";
  cin >> a >> b >> c;

  int error = quadraticFormula(a,b,c,r1,r2);

  if(error) {
    cout << "ERROR: a=0 or roots not real" << endl;
    return 1;
  }

  cout << "Roots are " << r1 << " and " << r2 << endl;

  return 0;
}
