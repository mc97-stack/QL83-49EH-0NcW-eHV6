//
//  01bIsothermal.h
//  Process Model
//
//  Created by Matthew Cheung on 08/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
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

#ifndef IsotVariable_h
#define IsotVariable_h

/// This subroutine is used to collect the data to required to calculate the volume work for an isothermal process.
/// @param method Integer variable used to determine what equation should be used. (1) = Volume equation. (2) = Pressure equation.
/// @param P1 Initial system pressure (kPa).
/// @param P2 Final system pressure (kPa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T System temperature (deg C).
/// @param n Moles of component in system (kmol/ s).
void IsotVariable(int method, double *P1, double *P2, double *V1, double *V2, double *T, double *n);

#endif /* IsotVariable_h */

#ifndef IsotVolume_h
#define IsotVolume_h

/// This subroutine used to calculate the volume work associated with an isothermal process from a volume change. This subroutine then returns the volume work associated with the volume change.
/// @param n Moles of component in system (mol/ s).
/// @param T System temperature (K).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
double IsotVolume(double n, double T, double V1, double V2);

#endif /* IsotVolume_h */

#ifndef IsotPressure_h
#define IsotPressure_h

/// This subroutine used to calculate the volume work associated with an isothermal process from a pressure change. This subroutine then returns the volume work associated with the pressure change.
/// @param n Moles of component in system (mol/ s).
/// @param T System temperature (K).
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
double IsotPressure(double n, double T, double P1, double P2);

#endif /* IsotPressure_h */

#ifndef IsotFinalPressure_h
#define IsotFinalPressure_h

/// This subroutine is used to calculate the final pressure of a process undergoing an isothermal process.
/// @param P1 Initial system pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
double IsotFinalPressure(double P1, double V1, double V2);

#endif /* IsotFinalPressure_h */

#ifndef IsotFinalVolume_h
#define IsotFinalVolume_h

/// This subroutine is used to calculate the final volume of a process undergoing an isothermal process.
/// @param V1 initial system volume (m3).
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
double IsotFinalVolume(double V1, double P1, double P2);

#endif /* IsotFinalVolume_h */

#ifndef IsotProfile_h
#define IsotProfile_h

#include "B48BC_T1.h"

/// This subroutine is used to estimate the process profile for an isothermal process. This subroutine requires "IdealPressure(...)" and "IdealVolume(...)" from "IdealGasLaw.h" to function as intended.
/// @param n Moles of component in system (mol/ s).
/// @param T System temperature (K).
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
T1ThermoProf IsotProfile(int method, double n, double T, double P1, double P2, double V1, double V2);
/*  Pressure|Volume|Temperature|Work|Work_cum.|
 */

#endif /* IsotProfile_h */

#ifndef IsocProcDisp_h
#define IsocProcDisp_h

/// This subroutine is used to output the collected data and generated profile to the user console.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T System temperature (K).
/// @param n Moles of component in system (mol/ s).
/// @param profile Isothermal process profile.
void IsotProcDisplay(double P1, double P2, double V1, double V2, double T, double n, T1ThermoProf profile);

#endif /* IsocProcDisp_h */

#ifndef IsocProcWrite_h
#define IsocProcWrite_h

/// This subroutine is used to write the collected data and generated profile to a .txt file.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T System temperature (K).
/// @param n Moles of component in system (mol/ s).
/// @param profile Isothermal process profile.
void IsotProcWrite(double P1, double P2, double V1, double V2, double T, double n, T1ThermoProf profile);

/// This subroutine is used to ask the user if they would like to either display the results on the console or save the results of this program to a file.
/// @param mode Integer used to control whether this function will access the display (1) or write (2) function.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T System temperature (K).
/// @param n Moles of component in system (mol/ s).
/// @param profile Isothermal process profile.
void IsotProcSwitch(int mode, double P1, double P2, double V1, double V2, double T, double n, T1ThermoProf profile);

#endif /* IsocProcWrite_h */
