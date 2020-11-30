//
//  01dRadiation.h
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

#ifndef _1dRadiationVariable_h
#define _1dRadiationVariable_h

/// This subroutine is used to collect the variables required to calculate the rate of heat transfer through the Stefan-Boltzmann law.
/// @param A Heat transfer area (m2).
/// @param Ts Temperature of heat transfer surface (deg C).
/// @param Tf Temperature of surrounding fluid (deg C).
void ThermRadiationVariable(double *A, double *Ts, double *Tf);

/// This subroutine returns the Stefan-Boltzmann constant in W/(m2.K4).
double StefanBoltzmannConstant(void);

#endif /* _1dRadiationVariable_h */

#ifndef _1dRadiationCalculation_h
#define _1dRadiationCalculation_h

/// This subroutine is used to calculate the rate of heat transfer by radiation from an ideal black-body.
/// @param A Heat transfer area (m2).
/// @param Ts Temperature of heat transfer surface (K).
/// @param Tf Temperature of surrounding fluid (K).
double ThermRadiationCalculation(double A, double Ts, double Tf);

#endif /* _1dRadiationCalculation_h */

#ifndef _1dRadiationDisplay_h
#define _1dRadiationDisplay_h

/// This subroutine is used to display the inputted and calculated parameters on the user console.
/// @param A Heat transfer area (m2).
/// @param Ts Temperature of heat transfer surface (K).
/// @param Tf Temperature of surrounding fluid (K).
/// @param Q Rate of heat transfer (W).
void ThermRadiationDisplay(double A, double Ts, double Tf, double Q);

#endif /* _1dRadiationDisplay_h */

#ifndef _1dRadiationWrite_h
#define _1dRadiationWrite_h

/// This subroutine is used to write the inputted and calculated parameters to a .txt file.
/// @param A Heat transfer area (m2).
/// @param Ts Temperature of heat transfer surface (K).
/// @param Tf Temperature of surrounding fluid (K).
/// @param Q Rate of heat transfer (W).
void ThermRadiationWrite(double A, double Ts, double Tf, double Q);

/// This subroutine is used to ask the user whether or not they would like to write the inputted and calculated parameters to disk.
/// @param A Heat transfer area (m2).
/// @param Ts Temperature of heat transfer surface (K).
/// @param Tf Temperature of surrounding fluid (K).
/// @param Q Rate of heat transfer (W).
void ThermRadiationWriteSwitch(double A, double Ts, double Tf, double Q);

#endif /* _1dRadiationWrite_h */
