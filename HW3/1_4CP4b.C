///////////////////////////////////////////////////////////////////////////////
// NEWTON'S METHOD
//
// state newton(double& x, double tolerance, int maxIteration)
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
#include <math.h> 
using namespace std;

enum state {SUCCESS=0, WONT_STOP, BAD_DATA, BAD_ITERATE};

double f(double x) { return log(3-x)+x-2; }
double df(double x) { return -1/(3-x)+1; }

state newton(double& x, double tolerance, int maxIteration, int debug) {
  if(debug) {
    cout << "Guess: x = " << x << endl;
  }

  for(int iteration = 1; iteration <= maxIteration; iteration++) {
    double dfx = df(x);
    if(dfx == 0.0) return BAD_ITERATE;

    double dx = -2*f(x)/dfx; //    double dx = -f(x)/dfx;
    x += dx;

    if(debug) {
      cout << "Iter " << iteration << ": x = " << x << ", dx = " << dx << endl;
    }

    if(fabs(dx) < tolerance) return SUCCESS;
  }

  return WONT_STOP;
}

int main() {
  double root,tol;
  int maxIter,debug;

  // Input

  cout << "Enter guess at root: ";
  cin >> root;
  cout << "Enter tolerance,  max iteration, and debug flag: ";
  cin >> tol >> maxIter >> debug;

  // Solve

  state s = newton(root, tol, maxIter, debug);

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
  case BAD_ITERATE:
    cout << "ERROR: Obtained a vanishing derivative!" << endl;
    break;
  default:
    cout << "ERROR: Coding error!" << endl;
  }

  return 1;
}
