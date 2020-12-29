//
//  03cRadWavelength.h
//  Process Model
//
//  Created by Matthew Cheung on 23/12/2020.
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

#ifndef _3dRadWavelengthVariable_h
#define _3dRadWavelengthVariable_h

typedef struct EmissivePower{
    double T[25];
    double wavelength[5000];
    double EmPower[5000][25];
} EmissivePower;

#endif /* _3dRadWavelengthVariable_h */

#ifndef _3dRadWavelengthCalculation_h
#define _3dRadWavelengthCalculation_h

/// This subroutine is used to calculate the monochromatic emissive power at a set wavelength and temperature.
/// @param wavelength Electromagnetic wavelength (m).
/// @param T Absolute temperature (K).
double EmissivePowerCalculation(double wavelength, double T);

/// This subroutine is used to generate the dataset for the black-body spectral emittance in SI units.
/// @param result Struct used to store temperature data prior to calculation.
/// @param numIsotherms The total number of isotherms to be generated.
EmissivePower EmissivePwrArray(EmissivePower result, int numIsotherms);

#endif /* _3dRadWavelengthCalculation_h */

#ifndef _3dRadWavelengthDisplay_h
#define _3dRadWavelengthDisplay_h

/// This subroutine is used to display the generated dataset on the user console.
/// @param data Struct used to store the dataset and isotherm temperatures.
/// @param numIsotherms Number of isotherms generated.
void EmissivePwrDisplay(EmissivePower data, int numIsotherms);

#endif /* _3dRadWavelengthDisplay_h */

#ifndef _3dRadWavelengthWrite_h
#define _3dRadWavelengthWrite_h

/// This subroutine is used to write the generated dataset to a .txt file.
/// @param data Struct used to store the dataset and isotherm temperatures.
/// @param numIsotherms Number of isotherms generated.
void EmissivePwrWrite(EmissivePower data, int numIsotherms);

/// This subroutine is used to ask the user whether or not they would like to either display the generated data on the user console OR write the generated dataset to file.
/// @param mode Variable used to control whether the data set is shown on the user console (1) or written to disk (2).
/// @param results Struct used to store the dataset and isotherm temperatures.
/// @param numIsotherms Number of isotherms generated.
void EmissivePwSwitch(int mode, EmissivePower results, int numIsotherms);

#endif /* _3dRadWavelengthWrite_h */
