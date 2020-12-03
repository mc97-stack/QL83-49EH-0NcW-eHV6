//
//  02bCompositeCylinder.h
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

#ifndef _2bCompositeCylinderVariable_h
#define _2bCompositeCylinderVariable_h

typedef struct CondCylMedium {
    double k[21];   // Thermal conductivity.
    double r[21];   // Outer radius of layer.
    double R[21];   // Layer resistance to heat transfer.
} CondCylMedium;

/// This subroutine is used to collect the variables regarding the general system being analysed.
/// @param T1 Hot surface temperature (deg C).
/// @param T2 Cold surface temperature (deg C).
/// @param L Length of cylinder (m).
/// @param r1 Inner cylinder radius (m).
void CompCylExtVariable(double *T1, double *T2, double *L, double *r1);

/// This subroutine is used to collect the variables about the thermal properties of a layer.
/// @param data Struct where the thermal data is being stored. This variable is used to verify a valid radius has been entered.
/// @param i Integer telling the subroutine the location of where the subroutine is writing into.
/// @param k Thermal conductivity (W/m.K).
/// @param r Radius of composite layer (mm).
void CompCylIntVariable(CondCylMedium data, int i, double *k, double *r);

#endif /* _2bCompositeCylinderVariable_h */

#ifndef _2bCompositeCylinderCalculation_h
#define _2bCompositeCylinderCalculation_h

/// This subroutine is used to calculate the resistance to heat transfer in a cylindrical composite layer.
/// @param k Thermal conductivity (W/m.K).
/// @param L Length of cylinder (m).
/// @param r1 Inner radius of composite layer (m).
/// @param r2 Outer radius of composite layer (m).
double CylResistanceCalculation(double k, double L, double r1, double r2);

/// This subroutine is used to calculate the rate of heat transfer through a cylindrical system.
/// @param R Resistance to heat transfer (K/W).
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
double CylHeatCalculation(double R, double T1, double T2);

/// This subroutine is used to calculate the interfacial temperatures within a cylindrical system.
/// @param T1 Starting temperature (K).
/// @param R Resistance to heat transfer (K/W).
/// @param Q Rate of heat transfer (W).
double CylTempCalculation(double T1, double R, double Q);

/// This subroutine is used to locate different sections within the generated temperature profile.
/// @param medium_ID Composite layer identifier - 1.
int CylInterfaceLocater(int medium_ID);

/// This subroutine is used to generate the temperature profile to show the rate of heat transfer within a cylindrical system.
/// @param numMediums Number of composite layers.
/// @param data Struct where the thermal properties of the composite layers is stored.
/// @param Q Rate of heat transfer within the cylindrical system (W).
/// @param L Length of cylinder (m).
/// @param T1 Hot surface temperature (K).
/// @param rowsused Number of rows used within the generated profile.
B48BDTemps CompCylCalculation(int numMediums, CondCylMedium data, double Q, double L, double T1, int *rowsused);

#endif /* _2bCompositeCylinderCalculation_h */

#ifndef _2bCompositeCylinderDisplay_h
#define _2bCompositeCylinderDisplay_h

/// This subroutine is used to display the inputted and calculated parameters on the user console.
/// @param numMediums Number of composite layers.
/// @param data Struct where the thermal properties of the composite layers is stored.
/// @param Q Rate of heat transfer within the cylindrical system (W).
/// @param L Length of cylinder (m).
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
/// @param rowsused Number of rows used within the generated profile.
/// @param profile Struct where the generated temperature profile is stored.
void CompCylDisplay(int numMediums, CondCylMedium data, double Q, double L, double T1, double T2, int rowsused, B48BDTemps profile);

#endif /* _2bCompositeCylinderDisplay_h */

#ifndef _2bCompositeCylinderWrite_h
#define _2bCompositeCylinderWrite_h

/// This subroutine is used to write the inputted and calculated parameters to a .txt file.
/// @param numMediums Number of composite layers.
/// @param data Struct where the thermal properties of the composite layers is stored.
/// @param Q Rate of heat transfer within the cylindrical system (W).
/// @param L Length of cylinder (m).
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
/// @param rowsused Number of rows used within the generated profile.
/// @param profile Struct where the generated temperature profile is stored.
void CompCylWrite(int numMediums, CondCylMedium data, double Q, double L, double T1, double T2, int rowsused, B48BDTemps profile);

/// This subroutine is used to ask the user whether or not they would like to display/ write the inputted and calculated parameters on the user console/to disk.
/// @param mode Integer value used to control whether data is displayed on the console (1) or written to disk (2).
/// @param numMediums Number of composite layers.
/// @param data Struct where the thermal properties of the composite layers is stored.
/// @param Q Rate of heat transfer within the cylindrical system (W).
/// @param L Length of cylinder (m).
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
/// @param rowsused Number of rows used within the generated profile.
/// @param profile Struct where the generated temperature profile is stored.
void CompCylSwitch(int mode, int numMediums, CondCylMedium data, double Q, double L, double T1, double T2, int rowsused, B48BDTemps profile);

#endif /* _2bCompositeCylinderWrite_h */
