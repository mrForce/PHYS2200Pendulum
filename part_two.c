

#include <stdio.h>
#include <math.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_const_mksa.h>

int func (double t, const double y[], double f[], void *params);

struct pendulum_params{
	double x;
	double w;
};
int main (int argc, char *argv[]) 
{
  double w;
  if(argc > 1){
  	w = atof(argv[1]);
  }else{
	printf("please include Omega\n");
	return(-1);
  }
  size_t neqs = 2;          /* number of equations. There are two, since I decoupled the system earlier (see attached).  */
  double eps_abs = 1.e-8, 
    eps_rel = 0.;           /* desired precision */
  double stepsize = 1e-7;   /* initial integration step */
  double t = 0.0, t1 = 200.; /* time interval */
  struct pendulum_params params = {0.01, w};

  int status;
  /* 
   * Initial conditions, first is phi, second is lambda
   */
  double y[2] = {.99*M_PI, 0};   /* for res1 */


  /*
   * Explicit embedded Runge-Kutta-Fehlberg (4,5) method. 
   * This method is a good general-purpose integrator.
   */
  gsl_odeiv2_step    *s = gsl_odeiv2_step_alloc 
                            (gsl_odeiv2_step_rkf45, neqs);
  gsl_odeiv2_control *c = gsl_odeiv2_control_y_new (eps_abs, 
						    eps_rel);
  gsl_odeiv2_evolve  *e = gsl_odeiv2_evolve_alloc (neqs);
    
  gsl_odeiv2_system sys = {func, NULL, neqs, &params};
    
  /*
   * This is where t gets increased, until t1.
   */
  while ((t < t1))
  {
    status = gsl_odeiv2_evolve_apply (e, c, s, &sys, &t,
                                      t1, &stepsize, y);

    if (status != GSL_SUCCESS) {
      printf ("Troubles: % .5e  % .5e\n", 
              t, y[0]);
      break;
    }
    printf ("%.5e \t %.5e  \n", 	      
            t, y[0]);
  }

  gsl_odeiv2_evolve_free (e);
  gsl_odeiv2_control_free (c);
  gsl_odeiv2_step_free (s);

  return 0;
}
