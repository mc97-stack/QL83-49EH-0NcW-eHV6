//
//  01bConduction.h
//  Process Model
//
//  Created by Matthew Cheung on 30/11/2020.
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

#ifndef _1bConductionVariable_h
#define _1bConductionVariable_h

/// This subroutine is used to collect the variables required to calculate the rate of heat transfer according to Fourier's law.
/// @param k Thermal conductivity (W/m.K).
/// @param A Heat transfer area (m2).
/// @param T1 Initial temperature (deg C).
/// @param T2 Final temperature (deg C).
/// @param x Surface thickness (mm).
void FouriersLawVariable(double *k, double *A, double *T1, double *T2, double *x);

#endif /* _1bConductionVariable_h */

#ifndef _1bConductionCalculation_h
#define _1bConductionCalculation_h

/// This subroutine is used to calculate the rate of heat transfer according to Fourier's law.
/// @param k Thermal conductivity (W/m.K).
/// @param A Heat transfer area (m2).
/// @param x Surface thickness (m).
/// @param T1 Initial temperature (deg C).
/// @param T2 Final temperature (deg C).
double FouriersLawCalculation(double k, double A, double x, double T1, double T2);

#endif /* _1bConductionCalculation_h */

#ifndef _1bConductionDisplay_h
#define _1bConductionDisplay_h

/// This subroutine is used to display the inputted and calculated parameters on the user console.
/// @param k Thermal conductivity (W/m.K).
/// @param A Heat transfer area (m2).
/// @param x Surface thickness (m).
/// @param T1 Initial temperature (deg C).
/// @param T2 Final temperature (deg C).
/// @param Q Rate of heat transfer (W).
void FouriersLawDisplay(double k, double A, double x, double T1, double T2, double Q);

#endif /* _1bConductionDisplay_h */

#ifndef _1bConductionWrite_h
#define _1bConductionWrite_h

/// This subroutine is used to write the inputted and calculated parameters to a .txt file.
/// @param k Thermal conductivity (W/m.K).
/// @param A Heat transfer area (m2).
/// @param x Surface thickness (m).
/// @param T1 Initial temperature (deg C).
/// @param T2 Final temperature (deg C).
/// @param Q Rate of heat transfer (W).
void FouriersLawWrite(double k, double A, double x, double T1, double T2, double Q);

/// This subroutine is used to ask the user whether or not they would like to write the inputted and calculated parameters to disk.
/// @param k Thermal conductivity (W/m.K).
/// @param A Heat transfer area (m2).
/// @param x Surface thickness (m).
/// @param T1 Initial temperature (deg C).
/// @param T2 Final temperature (deg C).
/// @param Q Rate of heat transfer (W).
void FouriersLawWriteSwitch(double k, double A, double x, double T1, double T2, double Q);

#endif /* _1bConductionWrite_h */
