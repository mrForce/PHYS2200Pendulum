/*
 * The function provides the right hand sides of the two differential equations in the system.
 * dL/dt = -[1 - x*w*sin(t*w)]*sin(p)
   dp/dt = L
 */

#include <stdio.h>
#include <math.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
struct pendulum_params{
	double x;
	double w;
};

int func (double t, const double y[], double f[], 
	  void *params) 
{
  /*
   * y[0] - angle, phi
   * y[1] - derivative of angle, lambda
   */

 f[0] = y[1];
 struct pendulum_params * pen_params = (struct pendulum_params *)params;

//x is a/l
 double x = pen_params->x;
 
//w is Omega.
 double w = pen_params->w;
 f[1] = -1*(1 - x*pow(w, 2)*sin(w*t))*sin(y[0]);

  return GSL_SUCCESS;
}

