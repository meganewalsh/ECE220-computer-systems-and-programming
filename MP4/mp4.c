// This program takes an input (the coefficients of a polynomial and an interval) from the user. Through the application
// of Budan's Theorem and Halley's Method, the program finds the roots of the polynomial (if they exist) and returns them
// back to the user. It will also acknowledge if no roots exist or if none exist in the given interval.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double abs_double(double y)
{
    //Change this to return the absolute value of y i.e |y|
    if (y < 0)											// only changes sign if reads a negative #
	y = y * -1;										// if positive, just returns same value.
    return y;
}

double fx_val(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the polynomial at the value x
    	double f_val;
	f_val =  a*pow(x,4) + b*pow(x,3) + c*pow(x,2) + d*x + e;				// ax^4 + bx^3 + cx^2 + dx + e
    return f_val;
}

double fx_dval(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the derivative of the polynomial at the value x
     	double f_derivf;
     	f_derivf = 4*a*pow(x,3) + 3*b*pow(x,2) + 2*c*x + d;					// 4ax^3 + 3bx^2 + 2cx + d
     return f_derivf;
}

double fx_ddval(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the double derivative of the polynomial at the value x
    	double s_derivf;
    	s_derivf = 12*a*pow(x,2) + 6*b*x + 2*c;							// 12ax^2 + 6bx +2c 
    return s_derivf;
}

double newrfind_halley(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the root found starting from the initial point x using Halley's method
	double old_x = x;
	double ret_val = 0;	
	int counter;
	
	for (counter = 0 ; counter < 10000 ; counter++)
	{ 
		x = old_x - (((2*fx_val(a,b,c,d,e,x)*fx_dval(a,b,c,d,e,x))) /
		(2*pow(abs_double(fx_dval(a,b,c,d,e,x)),2) - (fx_val(a,b,c,d,e,x)*fx_ddval(a,b,c,d,e,x)))); 	
		
    		if (abs_double(x - old_x) <= 0.000001) 
		   break;

		old_x = x;
	}
	if (counter < 10000)									// don't allow more than 10000 iterations
	   ret_val = x;
	else
	   ret_val = -99999;									// more than 10000 iterations done (no roots)
    return ret_val;
}

int rootbound(double a, double b, double c, double d, double e, double r, double l)
{
    //Change this to return the upper bound on the number of roots of the polynomial in the interval (l, r)
	double coeff1;
	double coeff2;
	double coeff3;
	double coeff4;
	double coeff5;
	int upper_bound = 0;
	int vl = 0;
	int vr = 0;

	coeff1 = a;										// calculate all coefficients in Budan's theorem
	coeff2 = 4*a*l + b;									// for addition of lower bound
	coeff3 = 6*a*pow(l,2) + 3*b*l + c;
	coeff4 = 4*a*pow(l,3) + 3*b*pow(l,2) + 2*c*l +d;
	coeff5 = a*pow(l,4) + b*pow(l,3) + c*pow(l,2) + d*l + e;

	   if((coeff1 > 0 && coeff2 < 0) || (coeff1 < 0 && coeff2 > 0))				// checks alternating signs of lower bounds
	     vl++;
	   if((coeff2 > 0 && coeff3 < 0) || (coeff2 < 0 && coeff3 > 0))
	     vl++;
	   if((coeff3 > 0 && coeff4 < 0) || (coeff3 < 0 && coeff4 > 0))
	     vl++;
	   if((coeff4 > 0 && coeff5 < 0) || (coeff4 < 0 && coeff5 > 0))
	     vl++;
    
	coeff1 = a;										// calculates all coefficients in Budan's theorem
	coeff2 = 4*a*r + b;									// for addition of upper bound
	coeff3 = 6*a*pow(r,2) + 3*b*r + c;
	coeff4 = 4*a*pow(r,3) + 3*b*pow(r,2) + 2*c*r +d;
	coeff5 = a*pow(r,4) + b*pow(r,3) + c*pow(r,2) + d*r + e;

	   if((coeff1 > 0 && coeff2 < 0) || (coeff1 < 0 && coeff2 > 0))				// checks alternating signs of upper bound coeffs
	     vr++;
	   if((coeff2 > 0 && coeff3 < 0) || (coeff2 < 0 && coeff3 > 0))
	     vr++;
	   if((coeff3 > 0 && coeff4 < 0) || (coeff3 < 0 && coeff4 > 0))
	     vr++;
	   if((coeff4 > 0 && coeff5 < 0) || (coeff4 < 0 && coeff5 > 0))
	     vr++;
	
	upper_bound = abs_double(vl-vr);
//	printf(" low is %d  upper is %d \n", vl, vr);
     return upper_bound;
}

int main(int argc, char **argv)
{
	double a, b, c, d, e, l, r;
	FILE *in;
	double z;
	double x;
	double root_val;

	if (argv[1] == NULL) {
		printf("You need an input file.\n");
		return -1;
	}
	in = fopen(argv[1], "r");
	if (in == NULL)
		return -1;
	fscanf(in, "%lf", &a);
	fscanf(in, "%lf", &b);
	fscanf(in, "%lf", &c);
	fscanf(in, "%lf", &d);
	fscanf(in, "%lf", &e);
	fscanf(in, "%lf", &l);
	fscanf(in, "%lf", &r);
        fclose(in);
    
    //The values are read into the variable a, b, c, d, e, l and r.
    //You have to find the bound on the number of roots using rootbound function.
    //If it is > 0 try to find the roots using newrfind function.
    //You may use the fval, fdval and fddval funtions accordingly in implementing the halleys's method.
	z = rootbound(a,b,c,d,e,r,l);	    
	if ( z == 0 )
	{  
	   printf("The polynomial has no roots in the given interval.\n");
	}
	else
	{ 
	   for ( x = l; x <= r; x = x + 0.5)							// checks between lower and upper bound and 
	   {											// increments point value by 0.5
	       root_val = newrfind_halley(a,b,c,d,e,x);
	       if (root_val == -99999)	  
 	       {
	          printf("No roots found.\n");
	       }
    	       else 
	       {
		  printf("Root found: %lf\n", root_val);					// prints the value of the root found 
	       }
	   }
	}
    return 0;
}
