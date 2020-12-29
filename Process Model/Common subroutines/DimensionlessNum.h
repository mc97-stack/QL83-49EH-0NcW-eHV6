//
//  DimensionlessNum.h
//  Process Model
//
//  Created by Matthew Cheung on 19/12/2020.
//

#ifndef DimensionlessNum_h
#define DimensionlessNum_h

/// This subroutine is used to calculate the Grashof number.
/// @param beta Coefficient of cubic expansion (m/K).
/// @param T1 Hot side temperature of fluid film (K).
/// @param T2 Cold side temperature of fluid film (K).
/// @param d Internal pipe diameter (m).
/// @param rho Fluid density (kg/m3).
/// @param mu Fluid viscosity (Pa.s)
double GrashofNum(double beta, double T1, double T2, double d, double rho, double mu);

/// This subroutine is used to calculate the Nusselt number.
/// @param h Fluid heat transfer coefficient (W/m2.K).
/// @param d Pipe internal diameter (m).
/// @param k Thermal conductivity (W/m.K).
double NusseltNum(double h, double d, double k);

/// This subroutine is used to calculate the Prandtl number.
/// @param cp Fluid heat capacity at constant pressure (J/mol.K).
/// @param mu Fluid viscosity (Pa.s).
/// @param k Thermal conductivity (W/m.K).
double PrandtlNum(double cp, double mu, double k);

/// This subroutine is used to calculate the Reynolds number.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param d Pipe diameter (m).
/// @param mu Fluid viscosity (Pa.s).
double ReynoldsNum(double rho, double u, double d, double mu);

/// This subroutine is used to calculate the Stanton number.
/// @param h Fluid heat transfer coefficient (W/m2.K).
/// @param cp Fluid heat capacity at constant pressure (J/kg.K).
/// @param rho Fluid density (kg/m3).
/// @param mu Fluid viscous (Pa.s).
/// @param u Fluid velocity (m/s).
double StantonNum(double h, double cp, double rho, double mu, double u);

#endif /* DimensionlessNum_h */
