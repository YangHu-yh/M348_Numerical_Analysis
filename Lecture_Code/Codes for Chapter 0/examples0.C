#include <iostream>
#include <cmath>
using namespace std;

void f(double w, double& z) {
  w = 88.88;
  z = 77.77;
}

int main() {
  double x = 12.0;
  double &y = x;

  cout << "x= " << x << endl;
  cout << "y= " << y << endl;

  y = -1;

  cout << "x= " << x << endl;
  cout << "y= " << y << endl;

  double xx = -34;
  f(xx,x);

  cout << "xx= " << xx << endl;
  cout << "x= " << x << endl;
  cout << "y= " << y << endl;

  return 0;
}
