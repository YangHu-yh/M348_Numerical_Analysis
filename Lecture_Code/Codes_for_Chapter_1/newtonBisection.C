///////////////////////////////////////////////////////////////////////////////
// NEWTON-BISECTION METHOD
//
// state newtonBisection(double& x, double tolerance, int maxIteration)
//
// Inputs:
//   x              The initial guess at the solution.
//   tolerance      The convergence tolerance (must be > 0).
//   maxIteration   The maximum number of iterations that can be taken.
//   debug          Boolean to set debugging output.
// Outputs:
//   x              The solution.
// Return:
//   state          An error status code.
//     SUCCESS      Sucessful termination.
//     WONT_STOP    Error: Exceeded maximum number of iterations.
//     BAD_ITERATE  Error: The function had a vanishing derivative.
//
//  Remark: We assume we are given the two functions
//   f              The name of the function for which a root is sought.
//   df             The name of the derivative of the function.  The derivative
//                  of f must be computed by hand and coded correctly as df,
//                  or newton will not work!
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
using namespace std;

enum state {SUCCESS=0, WONT_STOP, BAD_DATA, BAD_ITERATE};

double f(double x) { return (x+4)*x*x-10; }
double df(double x) { return (3*x+8)*x; }

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

state newtonBisection(double a, double b, double& x, double tolerance, int maxIteration, int debug) {
  // Swap a and b if necessary so a < b
  if(a > b) {
    double c = a;
    a = b;
    b = c;
  }
  double sfa = sgn(f(a)), sfb = sgn(f(b));

  // Make sure there is a root between a and b
  if(sfa*sfb >= 0.0) return BAD_DATA;

  if(debug) {
    cout << "Interval a,b = " << a << ", " << b << endl;
  }

  x = a + (b-a)/2;
  double xNew, fx = f(x);
  if(sfa*sgn(fx) > 0.0) {
    a = x;
  } else {
    b = x;
  }

  for(int iteration = 1; iteration <= maxIteration; iteration++) {
    double dfx = df(x);
    bool usedNewton = true;
    if(dfx != 0.0) {
      xNew = x - fx/dfx; // Newton
      if(xNew < a || b < xNew) {
	xNew = a + (b-a)/2; // Revert to Bisection
	usedNewton = false;
      }
    } else {
      xNew = a + (b-a)/2; // Bisection
      usedNewton = false; 
    }

    fx = f(xNew);

    if(sfa*sgn(fx) > 0.0) {
      a = xNew;
    } else {
      b = xNew;
    }

    double dx = xNew - x;
    x = xNew;
    if(debug) {
      cout << "Iter " << iteration << ": x = " << x << ", dx = " << dx
	   << ", a,b = " << a << ", " << b << ", Newton? " << usedNewton << endl;
    }
    if(fabs(dx) < tolerance) return SUCCESS;
  }

  return WONT_STOP;
}

int main() {
  double a,b,root,tol;
  int maxIter,debug;

  // Input

  cout << "Enter a and b: " << flush;
  cin >> a >> b;
  cout << "Enter tolerance,  max iteration, and debug flag: ";
  cin >> tol >> maxIter >> debug;

  // Solve

  state s = newtonBisection(a, b, root, tol, maxIter, debug);

  // Report results

  switch(s) {
  case SUCCESS: {
    int prec = (int) (log10(1.0/tol) + log10(fabs(root))) + 1;
    cout.precision(prec);
    cout << "The root is " << root << endl;
    return 0;
  }
  case WONT_STOP:
    cout << "ERROR: Failed to converge in " << maxIter << " iterations!"
         << endl;
    break;
  case BAD_DATA:
    cout << "ERROR: Unsuitable interval!" << endl;
    break;
  default:
    cout << "ERROR: Coding error!" << endl;
  }

  return 1;
}
