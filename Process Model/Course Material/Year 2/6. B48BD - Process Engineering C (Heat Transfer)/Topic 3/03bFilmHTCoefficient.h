//
//  03bFilmHTCoefficient.h
//  Process Model
//
//  Created by Matthew Cheung on 19/12/2020.
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//  

#ifndef _3bFilmHTCoefficientCases_h
#define _3bFilmHTCoefficientCases_h

/// This subroutine is used to guide the user through calculating the fluid heat transfer coefficient for natural convection.
void NaturalConvection(void);

/// This subroutine is used to guide the user through calculating the fluid heat transfer coefficient for forced convection over a flat plate.
void ForcedFlatPlate(void);

/// This subroutine is used to guide the user through calculating the fluid heat transfer coefficient inside a cylindrical tube.
void InsideCylinder(void);

/// This subroutine is used to guide the user through calculating the fluid heat transfer coefficeint outside either a single or bank of cylindrical tube(s).
void OutsideCylinder(void);

#endif /* _3bFilmHTCoefficientCases_h */

#ifndef _3bFilmHTCoefficientVariable_h
#define _3bFilmHTCoefficientVariable_h

/// This subroutine is used to collect the variables required to calculate the film heat transfer coefficient for a system with natural convective currents.
/// @param rho Fluid density (kg/m3).
/// @param mu Fluid viscosity (cP).
/// @param cp Heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param u Fluid velocity (m/s).
/// @param d Internal pipe diameter (mm).
/// @param T1 Fluid film hot side temperature (deg C).
/// @param T2 Fluid film cold side temperature (deg C).
/// @param beta Coefficient of cubic expansion (m/K).
/// @param constant Correlation constant ([ ]).
/// @param n Grashof number exponent ([ ]).
/// @param m Prandtl number exponent ([ ]).
void FluidHTNaturalVariable(double *rho, double *mu, double *cp, double *k, double *u, double *d, double *T1, double *T2, double *beta, double *constant, double *n, double *m);

/// This subroutine is used to collect the variables to calculate the film heat transfer coefficient over a heated flate plate (Forced convection).
/// @param rho Fluid density (kg/m3).
/// @param mu Fluid viscosity (cP).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param u Fluid velocity (m/s).
/// @param d Internal pipe diameter
void ForcedPlateVariable(double *rho, double *mu, double *cp, double *k, double *u, double *d);

/// This subroutine is used to collect the variables required to calculate the film heat transfer coefficient inside a cylinder.
/// @param eqn This variable is used to control which variables are collected. (1) Dittus-Boelter, (2) Colburn, (3) Stanton number and (4) Sieder-Tate.
/// @param rho Fluid density (kg/m3).
/// @param mu Fluid viscosity (cP).
/// @param mu_s Fluid viscosity at wall (cP).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param u Fluid velocity (m/s).
/// @param d Inner pipe diameter (mm).
void InCylVariable(int eqn, double *rho, double *mu, double *mu_s, double *cp, double *k, double *u, double *d);

/// This subroutine is used to collect the variables required to calculate the film heat transfer coefficient outer a bank of cylindrical tubes.
/// @param eqn This variable is used to control which variables are collected. (1) Hilpert's correlations for air, (2) Churchill_Bernstien correlation, (3) Generalised Nusselt correlation, (4) Nusselt correlation for a square/staggered tube layout.
/// @param rho Fluid density (kg/m3).
/// @param mu Bulk fluid viscosity (cP).
/// @param mu_s Fluid viscosity at wall (cP).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param u Fluid velocity (m/s).
/// @param d Equivalent pipe diameter (mm).
/// @param a Correlation constant.
/// @param m Correlation constant.
/// @param F1 Correlation constant.
/// @param F2 Correlation constant.
void OutCylVariable(int eqn, double *rho, double *mu, double *mu_s, double *cp, double *k, double *u, double *d, double *a, double *m, double *F1, double *F2);

#endif /* _3bFilmHTCoefficientVariable_h */

#ifndef _3bFilmHTCoefficientCalculation_h
#define _3bFilmHTCoefficientCalculation_h

/// This subroutine is used to calculate the fluid heat transfer coefficient using the Grashof and Prandtl numbers.
/// @param constant Correlation constant ([ ]).
/// @param n Grashof number exponent ([ ]).
/// @param m Prandtl number exponent ([ ]).
/// @param beta Coefficient of cubic expansion (m/K).
/// @param T1 Fluid film hot side temperature (K).
/// @param T2 Fluid film cold side temperature (K).
/// @param d Internal pipe diameter (m).
/// @param rho Fluid density (kg/m3).
/// @param mu Fluid viscosity (Pa.s).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Fluid thermal conductivity (W/m.K).
/// @param Nusselt Nusselt number ([ ]).
/// @param Grashof Grashof number ([ ]).
/// @param Prandtl Prandtl number ([ ]).
double NaturalHTCoefficient(double constant, double n, double m, double beta, double T1, double T2, double d, double rho, double mu, double cp, double k, double *Nusselt, double *Grashof, double *Prandtl);

/// This subroutine is used to calculate the film heat transfer coefficient for a fluid travelling under laminar flow conditions. 
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param k Thermal conductivity (W/m.K).
/// @param d Internal pipe diameter (m).
/// @param Nusselt Nusselt number ([ ]).
double ForcedHTCoefficientPlateLam(double Re, double Pr, double k, double d, double *Nusselt);

/// This subroutine is used to calculate the film heat transfer coefficient for a fluid at the transition point.
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param k Thermal conductivity (W/m.K).
/// @param d Internal pipe diameter (m).
/// @param Nusselt Nusselt number ([ ]).
double ForcedHTCoefficientPlateTrans(double Re, double Pr, double k, double d, double *Nusselt);

/// This subroutine is used to calculate the film heat transfer coefficient for a fluid travelling under turbulent flow conditions.
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param k Thermal conductivity (W/m.K).
/// @param d Internal pipe diameter (m).
/// @param Nusselt Nusselt number ([ ]).
double ForcedHTCoefficientPlateTur(double Re, double Pr, double k, double d, double *Nusselt);

/// This subroutine is used to calculate the film heat transfer coefficient through the Dittus-Boelter equation.
/// @param mode This is used to control whether the heating (1) or cooling (2) correlation is used.
/// @param Re Reynolds number([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param k Thermal conductivity (W/m.K).
/// @param d Inner pipe diameter (m).
/// @param Nusselt Nusselt number ([ ]).
double DittusBoelter(int mode, double Re, double Pr, double k, double d, double *Nusselt);

/// This subroutine is used to calculate the film heat transfer coefficient through the Colburn equation.
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param k Thermal conductivity (W/m.K).
/// @param d Inner pipe diameter (m).
/// @param Nusselt Nusselt number ([ ]).
double Colburn(double Re, double Pr, double k, double d, double *Nusselt);

/// This subroutine is used to calculate the film heat transfer coefficient through the Stanton number.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param d Inner pipe diameter (m).
/// @param mu Bulk fluid viscosity (Pa.s).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param Stanton Stanton number ([ ]).
double Stanton(double rho, double u, double d, double mu, double cp, double k, double *Stanton);

/// This subroutine is used to calculate the film heat transfer coefficient through the Sieder and Tate correlation.
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param mu Bulk fluid viscosity (Pa.s).
/// @param mu_wall Fluid viscosity at wall (Pa.s).
/// @param k Thermal conductivity (W/m.K).
/// @param d Inner pipe diameter (m).
/// @param Nusselt Nusselt number ([ ]).
double SiederTate(double Re, double Pr, double mu, double mu_wall, double k, double d, double *Nusselt);

/// This subroutine is used to calculate the film heat transfer coefficient using Hilpert's correlations.
/// @param Re Reynolds number ([ ]).
/// @param k Thermal conductivity (W/m.K).
/// @param d Equivalent pipe diameter (m)
/// @param Nusselt Nusselt number ([ ]).
double OutCylHTCoeffAir(double Re, double k, double d, double *Nusselt);

/// This subroutine is used to calculate the film heat transfer coefficient using the Churchill-Bernstien correlation.
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param d Equivalent pipe diameter ([ ]).
/// @param k Thermal conductivity (W/m.K).
/// @param Nusselt Nusselt number ([ ]).
double OutCylHTCoeffChurchillBernstein(double Re, double Pr, double d, double k, double *Nusselt);

/// This subroutine is used to calculate the film heat transfer coefficient using the generalised Nusselt correlation.
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param a Correlation constant ([ ]).
/// @param m Correlation constant ([ ]).
/// @param F1 Correlation constant ([ ]).
/// @param F2 Correlation constant ([ ]).
/// @param k Thermal conductivity (W/m.K).
/// @param d Equivalent pipe diameter (m).
/// @param Nusselt Nusselt number ([ ]).
double OutCylHTCoeffGeneral(double Re, double Pr, double a, double m, double F1, double F2, double k, double d, double *Nusselt);

/// This subroutine is used to calculate the film heat transfer coefficient using the Nusselt correlation applied to a square/staggered tube layout.
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param m Correlation constant ([ ]).
/// @param k Thermal conductivity (W/m.K).
/// @param d Equivalent pipe diameter (m).
/// @param Nusselt Nusselt number ([ ]).
double OutCylHTCoeffSquare(double Re, double Pr, double m, double k, double d, double *Nusselt);

#endif /* _3bFilmHTCoefficientCalculation_h */

#ifndef _3bFilmHTCoefficientDisplay_h
#define _3bFilmHTCoefficientDisplay_h

/// This subroutine is used to display the inputted and calculated parameters to the user console.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param mu Fluid viscosity (Pa.s).
/// @param beta Fluid coefficient of cubic expansion (m/K).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param d Internal pipe diameter (m).
/// @param T1 Fluid film hot side temperature (K).
/// @param T2 Fluid film cold side temperature (K).
/// @param constant Correlation constant ([ ]).
/// @param n Grashof number exponent ([ ]).
/// @param m Prandtl number exponent ([ ]).
/// @param Gr Grashof number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param Nu Nusselt number ([ ]).
/// @param h Film heat transfer coefficient (W/m2.K).
void NaturalHTCoeffDisplay(double rho, double u, double mu, double beta, double cp, double k, double d, double T1, double T2, double constant, double n, double m, double Gr, double Pr, double Nu, double h);

/// This subroutine is used to display the inputted and calculated parameters on the user console.
/// @param eqnset This variable is used to display which equation was used to calculate the film heat transfer coefficient.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param mu Fluid viscosity (Pa.s).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param d Pipe inner diameter (m).
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param Nu Nusselt number ([ ]).
/// @param h Film heat transfer coefficient (W/m2.K).
void PlateHTCoeffDisplay(int eqnset, double rho, double u, double mu, double cp, double k, double d, double Re, double Pr, double Nu, double h);

/// This subroutine is used to display the inputted and calculated parameters on the user console.
/// @param eqn This variable is used to control which parameters are displayed on the user console.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param mu Bulk fluid viscosity (Pa.s).
/// @param mu_wall Fluid viscosity at wall (Pa.s).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param d Inner pipe diameter (m).
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param St Stanton number ([ ]).
/// @param Nu Nusselt number ([ ]).
/// @param h Film heat transfer coefficient (W/m2.K).
void InCylHTCoeffDisplay(int eqn, double rho, double u, double mu, double mu_wall, double cp, double k, double d, double Re, double Pr, double St, double Nu, double h);

/// This subroutine is used to write the inputted and calculated parameters to the user console.
/// @param eqn Variable used to control which input variables are displayed on the console.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param mu Bulk fluid viscosity (Pa.s).
/// @param mu_s Fluid viscosity at wall (Pa.s).
/// @param d Equivalent pipe diameter (m).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param a Correlation constant ([ ]).
/// @param m Correlation constant ([ ]).
/// @param F1 Correlation constant ([ ]).
/// @param F2 Correlation constant ([ ]).
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param Nu Nusselt number ([ ]).
/// @param h Film heat transfer coefficient (W/m2.K).
void OutCylHTCoeffDisplay(int eqn, double rho, double u, double mu, double mu_s, double d, double cp, double k, double a, double m, double F1, double F2, double Re, double Pr, double Nu, double h);

#endif /* _3bFilmHTCoefficientDisplay_h */

#ifndef _3bFilmHTCoefficientWrite_h
#define _3bFilmHTCoefficientWrite_h

/// This subroutine is used to write the inputted and calculate parameters to a .txt file.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param mu Fluid viscosity (Pa.s).
/// @param beta Fluid coefficient of cubic expansion (m/K).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param d Internal pipe diameter (m).
/// @param T1 Fluid film hot side temperature (K).
/// @param T2 Fluid film cold side temperature (K).
/// @param constant Correlation constant ([ ]).
/// @param n Grashof number exponent ([ ]).
/// @param m Prandtl number exponent ([ ]).
/// @param Gr Grashof number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param Nu Nusselt number ([ ]).
/// @param h Film heat transfer coefficient (W/m2.K).
void NaturalHTCoeffWrite(double rho, double u, double mu, double beta, double cp, double k, double d, double T1, double T2, double constant, double n, double m, double Gr, double Pr, double Nu, double h);

/// This subroutine is used to ask the user whether they would like to either display or write the inputted and calculated parameters.
/// @param mode This variable is used to control whether this subroutine displays (1) or writes (2) the inputted and calculated parameters to the user console or disk.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param mu Fluid viscosity (Pa.s).
/// @param beta Fluid coefficient of cubic expansion (m/K).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param d Internal pipe diameter (m).
/// @param T1 Fluid film hot side temperature (K).
/// @param T2 Fluid film cold side temperature (K).
/// @param constant Correlation constant ([ ]).
/// @param n Grashof number exponent ([ ]).
/// @param m Prandtl number exponent ([ ]).
/// @param Gr Grashof number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param Nu Nusselt number ([ ]).
/// @param h Film heat transfer coefficient (W/m2.K).
void NaturalHTCoeffSwitch(int mode, double rho, double u, double mu, double beta, double cp, double k, double d, double T1, double T2, double constant, double n, double m, double Gr, double Pr, double Nu, double h);

/// This subroutine is used to write the inputted and calculated parameters to a .txt file.
/// @param eqnset This variable is used to display which equation was used to calculate the film heat transfer coefficient.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param mu Fluid viscosity (Pa.s).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param d Pipe inner diameter (m).
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param Nu Nusselt number ([ ]).
/// @param h Film heat transfer coefficient (W/m2.K).
void PlateHTCoeffWrite(int eqnset, double rho, double u, double mu, double cp, double k, double d, double Re, double Pr, double Nu, double h);

/// This subroutine is used to ask the user whether or not they would like to write the inputted and calculated parameters to disk.
/// @param eqnset This variable is used to display which equation was used to calculate the film heat transfer coefficient.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param mu Fluid viscosity (Pa.s).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param d Pipe inner diameter (m).
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param Nu Nusselt number ([ ]).
/// @param h Film heat transfer coefficient (W/m2.K).
void PlateHTCoeffWriteSwitch(int eqnset, double rho, double u, double mu, double cp, double k, double d, double Re, double Pr, double Nu, double h);

/// This subroutine is used to write the inputted and calculated parameters to a .txt file.
/// @param eqn This variable is used to control which parameters are displayed on the user console.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param mu Bulk fluid viscosity (Pa.s).
/// @param mu_wall Fluid viscosity at wall (Pa.s).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param d Inner pipe diameter (m).
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param St Stanton number ([ ]).
/// @param Nu Nusselt number ([ ]).
/// @param h Film heat transfer coefficient (W/m2.K).
void InCylHTCoeffWrite(int eqn, double rho, double u, double mu, double mu_wall, double cp, double k, double d, double Re, double Pr, double St, double Nu, double h);

/// This subroutine is used to ask the user whether or not they would like to write the inputted and calculated parameters to disk.
/// @param eqn This variable is used to control which parameters are displayed on the user console.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param mu Bulk fluid viscosity (Pa.s).
/// @param mu_wall Fluid viscosity at wall (Pa.s).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param d Inner pipe diameter (m).
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param St Stanton number ([ ]).
/// @param Nu Nusselt number ([ ]).
/// @param h Film heat transfer coefficient (W/m2.K).
void InCylHTCoeffWriteSwitch(int eqn, double rho, double u, double mu, double mu_wall, double cp, double k, double d, double Re, double Pr, double St, double Nu, double h);

/// This subroutine is used to write the inputted and calculated parameters to a .txt file.
/// @param eqn Variable used to control which input variables are written to disk..
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param mu Bulk fluid viscosity (Pa.s).
/// @param mu_s Fluid viscosity at wall (Pa.s).
/// @param d Equivalent pipe diameter (m).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param a Correlation constant ([ ]).
/// @param m Correlation constant ([ ]).
/// @param F1 Correlation constant ([ ]).
/// @param F2 Correlation constant ([ ]).
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param Nu Nusselt number ([ ]).
/// @param h Film heat transfer coefficient (W/m2.K).
void OutCylHTCoeffWrite(int eqn, double rho, double u, double mu, double mu_s, double d, double cp, double k, double a, double m, double F1, double F2, double Re, double Pr, double Nu, double h);

/// This subroutine is used to ask the user whether or not they would like to write the inputted and calculated parameters to disk.
/// @param eqn Variable used to control which input variables are written to disk..
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param mu Bulk fluid viscosity (Pa.s).
/// @param mu_s Fluid viscosity at wall (Pa.s).
/// @param d Equivalent pipe diameter (m).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param k Thermal conductivity (W/m.K).
/// @param a Correlation constant ([ ]).
/// @param m Correlation constant ([ ]).
/// @param F1 Correlation constant ([ ]).
/// @param F2 Correlation constant ([ ]).
/// @param Re Reynolds number ([ ]).
/// @param Pr Prandtl number ([ ]).
/// @param Nu Nusselt number ([ ]).
/// @param h Film heat transfer coefficient (W/m2.K).
void OutCylHTCoeffWriteSwitch(int eqn, double rho, double u, double mu, double mu_s, double d, double cp, double k, double a, double m, double F1, double F2, double Re, double Pr, double Nu, double h);

#endif /* _3bFilmHTCoefficientWrite_h */
