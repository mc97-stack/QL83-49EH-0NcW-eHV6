//
//  01dIsochoric Process.h
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

#ifndef IsocVariable_h
#define IsocVariable_h

/// This subroutine is used for collecting data for calculating the heat for a isochoric process.
/// @param method Integer variable used to determine what equation should be used. (1) = Pressure-Volume equation. (2) = Temperature equation.
/// @param P1 Initial system pressure (kPa).
/// @param P2 Final system pressure (kPa).
/// @param V System volume (m3).
/// @param T1 Initial system temperature (deg C).
/// @param T2 Final system temperature (deg C).
/// @param n Moles of component in system (kmol/s).
/// @param cv Heat capacity at constant volume (kJ/kmol.K).
void IsocVariable(int method, double *P1, double *P2, double *V, double *T1, double *T2, double *n, double *cv);

#endif /* IsocVariable_h */

#ifndef IsocPressure_h
#define IsocPressure_h

/// This subroutine is used to calculate the heat associated with a pressure change for an isochoric process.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V System volume (m3).
/// @param cv Heat capacity at constant volume (kJ/kmol.K).
double IsocPressure(double P1, double P2, double V, double cv);

#endif /* IsocPressure_h */

#ifndef IsocTemperature_h
#define IsocTemperature_h

/// This subroutine is used to calculate the heat associated with a temperature change for an isochoric process.
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param n Moles of component in system (mol/ s).
/// @param cv Heat capacity at constant volume (kJ/kmol.K).
double IsocTemperature(double T1, double T2, double n, double cv);

#endif /* IsocTemperature_h */

#ifndef IsocFinalTemperature_h
#define IsocFinalTemperature_h

/// This subroutine is used to calculate the final temperature for an isochoric process associated with a given pressure change and initial temperature..
/// @param T1 Initial system temperature.
/// @param P1 Initial system pressure.
/// @param P2 Final system pressure.
double IsocFinalTemperature(double T1, double P1, double P2);

#endif /* IsocTemperature_h */

#ifndef IsocProfile_h
#define IsocProfile_h

#include "B48BC_T1.h"

/// This subroutine is used for calculating the process profile for an isochoric process. This subroutine requires "IdealTemperature(...)" from "IdealGasLaw.h" to function as intended.
/// @param method Integer variable used to determine what equation should be used. (1) = Pressure-Volume equation. (2) = Temperature equation.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V System volume (m3).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param n Moles of component in system (mol/ s).
/// @param cv Heat capacity at constant volume (kJ/kmol.K).
T1ThermoProf IsocProfile(int method, double P1, double P2, double V, double T1, double T2, double n, double cv);
/*  Pressure|Volume|Temperature|Work|Q|Q_cum.|
 */

#endif /* IsocProfile_h */

#ifndef IsocProcDisp_h
#define IsocProcDisp_h

/// This subroutine is used to output the collected data and generated profile from "IsocProfile(...)" to the user console.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V System volume (m3).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param n Moles of component in system (mol/ s).
/// @param c_v Heat capacity at constant volume (J/mol.K).
/// @param profile Isochoric process profile.
void IsocProcDisplay(double P1, double P2, double V, double T1, double T2, double n, double c_v, T1ThermoProf profile);

#endif /* IsocProcDisp_h */

#ifndef IsocProcWrite_h
#define IsocProcWrite_h

/// This subroutine is used to output the collected data and generated profile from "IsocProfile(...)" to a .txt file.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V System volume (m3).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param n Moles of component in system (mol/ s).
/// @param c_v Heat capacity at constant volume (J/mol.K).
/// @param profile Isochoric process profile.
void IsocProcWrite(double P1, double P2, double V, double T1, double T2, double n, double c_v, T1ThermoProf profile);

/// This subroutine is used to ask the user if they would like to either display the results on the console or save the results of this program to a file.
/// @param mode Integer used to control whether this function will access the display (1) or write (2) function.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V System volume (m3).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param n Moles of component in system (mol/ s).
/// @param c_v Heat capacity at constant volume (J/mol.K).
/// @param profile Isochoric process profile.
void IsocProcSwitch(int mode, double P1, double P2, double V, double T1, double T2, double n, double c_v, T1ThermoProf profile);

#endif /* IsocProcWrite_h */
