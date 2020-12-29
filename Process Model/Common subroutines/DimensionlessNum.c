//
//  DimensionlessNum.c
//  Process Model
//
//  Created by Matthew Cheung on 19/12/2020.
//

//  Standard header files
#include <math.h>
#include <stdio.h>

// Custom header files
#include "DimensionlessNum.h"

//  Subroutine definitions
#define g 9.80665   // m/s2

double GrashofNum(double beta, double T1, double T2, double d, double rho, double mu)
{
    double result = 0.0;
    double sto = 0.0;
    
    sto = beta*g;
    result = sto;
    sto = T1 - T2;
    result *= sto;
    sto = pow(d, 3);
    result *= sto;
    sto = pow(rho, 2);
    result *= sto;      // Numerator calculated
    
    sto = pow(mu, 2);
    result /= sto;      // Grashof number calculated.
    
    return result;
}

double NusseltNum(double h, double d, double k)
{
    double result = 0.0;
    
    result = h*d;
    result = (result)/k;
    
    return result;
}

double PrandtlNum(double cp, double mu, double k)
{
    double result = 0.0;
    
    result = cp*mu;
    result = (result)/k;
    
    return result;
}

double ReynoldsNum(double rho, double u, double d, double mu)
{
    double result = 0.0;
    
    result = rho * u;
    result = (result)*d;
    result = (result)/mu;
    
    return result;
}

double StantonNum(double h, double cp, double rho, double mu, double u)
{
    double result = 0.0;
    
    result = cp*mu;
    result *= u;
    result = h/(result);
    
    return result;
}
