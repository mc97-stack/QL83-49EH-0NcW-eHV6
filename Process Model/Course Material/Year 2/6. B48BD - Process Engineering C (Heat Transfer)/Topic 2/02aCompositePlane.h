//
//  02aCompositePlane.h
//  Process Model
//
//  Created by Matthew Cheung on 02/12/2020.
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

#ifndef _2aCompositePlaneVariable_h
#define _2aCompositePlaneVariable_h

typedef struct CondMedium {
    double k[20];   // Thermal conductivity.
    double x[20];   // Plane thickness.
    double R[20];   // Layer resistance to heat transfer.
} CondMedium;

/// This subroutine is used to collect the variables regarding the general system being analysed.
/// @param T1 Hot surface temperature (deg C).
/// @param T2 Cold surface temperature (deg C).
/// @param A Heat transfer area (m2).
void CompPlaneExtVariable(double *T1, double *T2, double *A);

/// This subroutine is used to collect the variables about the thermal properties of a layer.
/// @param k Thermal conductivity (W/m.K).
/// @param x Layer thickness (m).
void CompPlaneIntVariable(double *k, double *x);

#endif /* _2aCompositePlaneVariable_h */

#ifndef _2aCompositePlaneCalculation_h
#define _2aCompositePlaneCalculation_h

/// This subroutine is used to calculate the resistance to heat transfer within a layer of the composite wall.
/// @param k Thermal conductivity (W/m.K)
/// @param A Heat transfer area (m2).
/// @param x Layer thickness (m).
double ResistanceCalculation(double k, double A, double x);

/// This subroutine is used to calculate the rate of heat transfer through the entire system under analysis.
/// @param R Resistance to heat transfer (K/W).
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
double HeatCalculation(double R, double T1, double T2);

/// This subroutine is used to calculate the interface temperature for a composite wall.
/// @param T1 Temperature on the hot side of the composite (K).
/// @param x Layer thickness (m).
/// @param k Thermal conductivity of composite material (W/m.K).
/// @param A Heat transfer area (m2).
/// @param Q Rate of heat transfer (W).
double TempCalculation(double T1, double x, double k, double A, double Q);

/// This subroutine is used to find the location of the interfaces within the temperature profile being generated.
/// @param medium_ID The integer identifier of composite layer - 1.
int InterfaceLocater(int medium_ID);

/// This subroutine is used to generate the temperature profile for a composite plane wall where heat transfer by conduction is occurring.
/// @param numMediums Number of composite layers present.
/// @param data Struct used to store the thermal properties of the composite layer.
/// @param Q Rate of heat transfer through the composite wall (W).
/// @param A Area of the heat transfer surface (m2).
/// @param T1 Temperature of the hot surface (K).
/// @param rowsused Number of rows generated within the profile.
B48BDTemps CompPlaneCalculation(int numMediums, heatmedium data, double Q, double A, double T1, int *rowsused);

#endif /* _2aCompositePlaneCalculation_h */

#ifndef _2aCompositePlaneDisplay_h
#define _2aCompositePlaneDisplay_h

/// This subroutine is used to display the inputted and calculated parameters on the user console.
/// @param numMediums Number of composite layers present.
/// @param data Struct used to store the thermal properties of the composite layer.
/// @param Q Rate of heat transfer through the composite wall (W).
/// @param A Area of the heat transfer surface (m2).
/// @param T1 Temperature of the hot surface (K).
/// @param T2 Temperature of the cold surface (K).
/// @param rowsused Number of rows generated within the profile.
/// @param profile Struct used to store the generated temperature profile.
void CompPlaneDisplay(int numMediums, heatmedium data, double Q, double A, double T1, double T2, double rowsused, B48BDTemps profile);

#endif /* _2aCompositePlaneDisplay_h */

#ifndef _2aCompositePlaneWrite_h
#define _2aCompositePlaneWrite_h

/// This subroutine is used to write the inputted and calculated parameters to a .txt file.
/// @param numMediums Number of composite layers present.
/// @param data Struct used to store the thermal properties of the composite layer.
/// @param Q Rate of heat transfer through the composite wall (W).
/// @param A Area of the heat transfer surface (m2).
/// @param T1 Temperature of the hot surface (K).
/// @param T2 Temperature of the cold surface (K).
/// @param rowsused Number of rows generated within the profile.
/// @param profile Struct used to store the generated temperature profile.
void CompPlaneWrite(int numMediums, heatmedium data, double Q, double A, double T1, double T2, double rowsused, B48BDTemps profile);

/// This subroutine is used to ask the user whether or not they would like to display/ write the inputted and calculated parameters on the user console/to disk.
/// @param mode Integer value used to control whether data is displayed on the console (1) or written to disk (2).
/// @param numMediums Number of composite layers present.
/// @param data Struct used to store the thermal properties of the composite layer.
/// @param Q Rate of heat transfer through the composite wall (W).
/// @param A Area of the heat transfer surface (m2).
/// @param T1 Temperature of the hot surface (K).
/// @param T2 Temperature of the cold surface (K).
/// @param rowsused Number of rows generated within the profile.
/// @param profile Struct used to store the generated temperature profile.
void CompPlaneSwitch(int mode, int numMediums, heatmedium data, double Q, double A, double T1, double T2, double rowsused, B48BDTemps profile);

#endif /* _2aCompositePlaneWrite_h */
