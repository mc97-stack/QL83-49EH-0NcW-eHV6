//
//  01cConvection.h
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

#ifndef _1cConvectionVariable_h
#define _1cConvectionVariable_h

/// This subroutine is used to collect the variables used to calculate the rate of heat transfer through the steady-state convection law.
/// @param h Fluid heat transfer coefficient (W/m2.K).
/// @param A Heat transfer area (m2).
/// @param T1 Initial temperature (deg C).
/// @param T2 Final temperature (deg C).
void SSConvectionVariable(double *h, double *A, double *T1, double *T2);

#endif /* _1cConvectionVariable_h */

#ifndef _1cConvectionCalculation_h
#define _1cConvectionCalculation_h

/// This subroutine is used to calculate the rate of heat transfer through the steady-state convection law.
/// @param h Fluid heat transfer coefficient (W/m2.K).
/// @param A Heat transfer area (m2).
/// @param T1 Initial temperature (deg C).
/// @param T2 Final temperature (deg C).
double SSConvectionCalculation(double h, double A, double T1, double T2);

#endif /* _1cConvectionCalculation_h */

#ifndef _1cConvectionDisplay_h
#define _1cConvectionDisplay_h

/// This subroutine is used to display the inputted and calculated parameters to the user console.
/// @param h Fluid heat transfer coefficient (W/m2.K).
/// @param A Heat transfer area (m2).
/// @param T1 Initial temperature (deg C).
/// @param T2 Final temperature (deg C).
/// @param Q Rate of heat transfer (W).
void SSConvectionDisplay(double h, double A, double T1, double T2, double Q);

#endif /* _1cConvectionDisplay_h */

#ifndef _1cConvectionWrite_h
#define _1cConvectionWrite_h

/// This subroutine is used to write the inputted and calculated parameters to a .txt file.
/// @param h Fluid heat transfer coefficient (W/m2.K).
/// @param A Heat transfer area (m2).
/// @param T1 Initial temperature (deg C).
/// @param T2 Final temperature (deg C).
/// @param Q Rate of heat transfer (W).
void SSConvectionWrite(double h, double A, double T1, double T2, double Q);

/// This subroutine is used to ask the user whether or not they would like to write the inputted and calculated parameters to disk.
/// @param h Fluid heat transfer coefficient (W/m2.K).
/// @param A Heat transfer area (m2).
/// @param T1 Initial temperature (deg C).
/// @param T2 Final temperature (deg C).
/// @param Q Rate of heat transfer (W).
void SSConvectionWriteSwitch(double h, double A, double T1, double T2, double Q);

#endif /* _1cConvectionWrite_h */
