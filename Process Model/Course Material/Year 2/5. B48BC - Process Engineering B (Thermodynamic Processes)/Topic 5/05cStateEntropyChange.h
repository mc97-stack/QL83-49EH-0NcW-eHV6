//
//  05cStateEntropyChange.h
//  Process Model
//
//  Created by Matthew Cheung on 24/11/2020.
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

#ifndef StateEntropyChangeVariable_h
#define StateEntropyChangeVariable_h

/// This subroutine is used to collect the variables required to calculate the entropy change for an ideal gas dependent on which method is initially selected within the pseudo-main function.
/// @param method Integer variable used to control which variables are selected. (1) = Pressure-Temperature. (2) = Pressure-molar volume. (3) = Temperature-molar volume.
/// @param cp Heat capacity at constant pressure (kJ/kmol.K).
/// @param P1 Initial system pressure (kPa)
/// @param P2 Final system pressure (kPa).
/// @param v1 Initial molar volume (m3/kmol).
/// @param v2 Final molar volume (m3/kmol).
/// @param T1 Initial system temperature (deg C).
/// @param T2 Final system temperature (deg C).
void IdealChangeVariable(int method, double *cp, double *P1, double *P2, double *v1, double *v2, double *T1, double *T2);

#endif /* StateEntropyChangeVariable_h */

#ifndef StateEntropyChangeCalculation_h
#define StateEntropyChangeCalculation_h

/// This subroutine is used to calculate the entropy change from the system pressure and temperature ratios.
/// @param cp Heat capacity at constant pressure (kJ/kmol.K).
/// @param P1 Initial system pressure (kPa)
/// @param P2 Final system pressure (kPa).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
double PTIdealCalculation(double cp, double P1, double P2, double T1, double T2);

/// This subroutine is used to calculate the entropy change from the system pressure and molar volume ratios.
/// @param cp Heat capacity at constant pressure (kJ/kmol.K).
/// @param P1 Initial system pressure (kPa)
/// @param P2 Final system pressure (kPa).
/// @param v1 Initial molar volume (m3/kmol).
/// @param v2 Final molar volume (m3/kmol).
double PvIdealCalculation(double cp, double P1, double P2, double v1, double v2);

/// This subroutine is used to calculate the entropy change from the system temperature and molar volume ratios.
/// @param cp Heat capacity at constant pressure (kJ/kmol.K).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param v1 Initial molar volume (m3/kmol).
/// @param v2 Final molar volume (m3/kmol).
double TvIdealCalculation(double cp, double T1, double T2, double v1, double v2);

#endif /* StateEntropyChangeCalculation_h */

#ifndef StateEntropyChangeDisplay_h
#define StateEntropyChangeDisplay_h

/// This subroutine is used to display the inputted and calculated parameters on the user console.
/// @param cp Heat capacity at constant pressure (kJ/kmol.K).
/// @param P1 Initial system pressure (kPa)
/// @param P2 Final system pressure (kPa).
/// @param v1 Initial molar volume (m3/kmol).
/// @param v2 Final molar volume (m3/kmol).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param ds Entropy change (kJ/kmol.K).
void EntropyChangeDisplay(double cp, double P1, double P2, double v1, double v2, double T1, double T2, double ds);

#endif /* StateEntropyChangeDisplay_h */

#ifndef StateEntropyChangeWrite_h
#define StateEntropyChangeWrite_h

/// This subroutine is used to write the inputted and calculated parameters to a .txt file. 
/// @param cp Heat capacity at constant pressure (kJ/kmol.K).
/// @param P1 Initial system pressure (kPa)
/// @param P2 Final system pressure (kPa).
/// @param v1 Initial molar volume (m3/kmol).
/// @param v2 Final molar volume (m3/kmol).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param ds Entropy change (kJ/kmol.K).
void EntropyChangeWrite(double cp, double P1, double P2, double v1, double v2, double T1, double T2, double ds);

/// This subroutine is used to ask the user if they would like to write the inputted and calculated parameters to disk. 
/// @param cp Heat capacity at constant pressure (kJ/kmol.K).
/// @param P1 Initial system pressure (kPa)
/// @param P2 Final system pressure (kPa).
/// @param v1 Initial molar volume (m3/kmol).
/// @param v2 Final molar volume (m3/kmol).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param ds Entropy change (kJ/kmol.K).
void EntropyChangeWriteSwitch(double cp, double P1, double P2, double v1, double v2, double T1, double T2, double ds);

#endif /* StateEntropyChangeWrite_h */
