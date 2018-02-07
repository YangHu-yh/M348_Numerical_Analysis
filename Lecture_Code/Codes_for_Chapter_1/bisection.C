///////////////////////////////////////////////////////////////////////////////
// BISECTION METHOD
//
// Solves the problem
//   f(x) = 0
// using the bisection algorithm.
//
// state bisection(double a, double b, double& x, double tolerance, int maxIteration, int debug)
//
// Inputs:
//   a,b           The initial bounding interval, with a root between.
//   tolerance     The convergence tolerance (must be > 0).
//   maxIteration  The maximum number of iterations that can be taken.
//   debug         Boolean for printing out information on every iteration.
// Outputs:
//   x             The solution.
// Return:
//   state         An error status code.
//     SUCCESS     Sucessful termination.
//     WONT_STOP   Error: Exceeded maximum number of iterations.
//     BAD_DATA    Error: The interval may not bracket a root.
//
// We assume the function f is given:
//   double f(double);
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cmath>
using namespace std;

enum state {SUCCESS=0, WONT_STOP, BAD_DATA, BAD_ITERATE};

double f(double x) {
  return x - exp(-x);
}

double sgn(double x) {
  if(x>0) {
    return 1;
  } else if(x<0) {
    return -1;
  } else if(x==0) {
    return 0;
  } else {
    return x; // x is not a number
  }
} 

state bisection(double a, double b, double& x, double tolerance, int maxIteration, int debug) {
  // Swap a and b if necessary so a < b
  if(a > b) {
    double c = a;
    a = b;
    b = c;
  }
  double fa = f(a), fb = f(b);

  // Make sure there is a root between a and b
  if(sgn(fa)*sgn(fb) > 0.0) return BAD_DATA;

  // Bisection iteration loop
  double fx, dx = b-a;
  for(int iteration = 0; iteration < maxIteration; iteration++) {
    dx /= 2;
    x = a + dx;
    fx = f(x);

    if(debug) {
      cout << "Iter " << iteration << ": x = " << x << ", dx = " << dx 
	<< ", a = " << a << ", b = " << b << ", f(x) = " << fx << endl;
    }

    // Check error tolerance
    if(dx <= tolerance) return SUCCESS;

    if(sgn(fa)*sgn(fx) > 0.0) {
      a = x; fa = fx;
    } else {
      b = x; fb = fx;
    }
  }

  return WONT_STOP;
}

int main() {
  double a,b,root,tol;
  int maxIter;
  int debug;

  // Input

  cout << "Enter a and b: " << flush;
  cin >> a >> b;
  cout << "Enter tolerance and maxIteration: " << flush;
  cin >> tol >> maxIter;
  cout << "Monitor iterations? (1/0): " << flush;
  cin >> debug;

  // Solve for a root

  state s = bisection(a, b, root, tol, maxIter, debug);

  // Report results

  switch(s) {
  case SUCCESS: {
    int prec = (int) (log10(1.0/tol) + log10(fabs(root))) + 1;
    cout.precision(prec);
    cout << "The root is " << root << endl;
    cout << "  f(" << root << ") = " << f(root) << endl;
    return 0;
  }
  case WONT_STOP:
    cout << "ERROR: Failed to converge in " << maxIter << " iterations!" << endl;
    return 1;
  case BAD_DATA:
    cout << "ERROR: Unsuitable interval!" << endl;
    return 1;
  default:
    cout << "ERROR: Coding error!" << endl;
  }
  return 1;
}
