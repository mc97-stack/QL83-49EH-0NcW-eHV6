//
//  02cCompositeSphere.h
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

#ifndef _2cCompositeSphereVariable_h
#define _2cCompositeSphereVariable_h

typedef struct CondSphMedium {
    double k[21];   // Thermal conductivity.
    double r[21];   // Outer radius of layer.
    double R[21];   // Layer resistance to heat transfer.
} CondSphMedium;

/// This subroutine is used to collect the variables regarding the general system being analysed.
/// @param T1 Hot surface temperature (deg C).
/// @param T2 Cold surface temperature (deg C).
/// @param r1 Inner sphere radius (mm).
void CompSphExtVariable(double *T1, double *T2, double *r1);

/// This subroutine is used to collect the variables about the thermal properties of the layer.
/// @param data Struct where the thermal data is being stored. This variable is used to verify that a valid radius has been entered.
/// @param i Integer to tell the subroutine the current location of where data is being written to.
/// @param k Thermal conductivity (W/m.K).
/// @param r Radius of composite layer (mm).
void CompSphIntVariable(CondSphMedium data, int i, double *k, double *r);

#endif /* _2cCompositeSphereVariable_h */

#ifndef _2cCompositeSphereCalculation_h
#define _2cCompositeSphereCalculation_h

/// This subroutine is used to calculate the resistance to heat transfer in a spherical composite layer.
/// @param k Thermal conductivity (W/m.K).
/// @param r1 Inner radius of layer (m).
/// @param r2 Outer radius of layer (m).
double SphResistanceCalculation(double k, double r1, double r2);

/// This subroutine is used to calculate the rate of heat transfer through a spherical system.
/// @param R Resistance to heat transfer (K/W).
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
double SphHeatCalculation(double R, double T1, double T2);

/// This subroutine is used to calculate the interfacial temperatures within a spherical system.
/// @param T1 Starting temperature (K).
/// @param R Resistance to heat transfer (K/W).
/// @param Q Rate of heat transfer (W).
double SphTempCalculation(double T1, double R, double Q);

/// This subroutine is used to locate different sections within the generated temperature profile.
/// @param medium_ID Composite layer identifier - 1.
int SphInterfaceLocater(int medium_ID);

/// This subroutine is used to generate the temperature profile to show the rate of heat transfer within a spherical system.
/// @param numMediums Number of composite layers.
/// @param data Struct where the thermal properties of the composite layers is stored.
/// @param Q Rate of heat transfer within the spherical system (W).
/// @param T1 Hot surface temperature (K).
/// @param rowsused Number of rows used within the generated profile.
B48BDTemps CompSphCalculation(int numMediums, CondSphMedium data, double Q, double T1, int *rowsused);

#endif /* _2cCompositeSphereCalculation_h */

#ifndef _2cCompositeSphereDisplay_h
#define _2cCompositeSphereDisplay_h

/// This subroutine is used to display the inputted and calculated parameters on the user console.
/// @param numMediums Number of composite layers.
/// @param data Struct where the thermal properties of the composite layers is stored.
/// @param Q Rate of heat transfer within the spherical system (W).
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
/// @param rowsused Number of rows used within the generate profile.
/// @param profile Struct used to store the generated temperature profile.
void CompSphDisplay(int numMediums, CondSphMedium data, double Q, double T1, double T2, int rowsused, B48BDTemps profile);

#endif /* _2cCompositeSphereDisplay_h */

#ifndef _2cCompositeSphereWrite_h
#define _2cCompositeSphereWrite_h

/// This subroutine is used to write the inputted and calculated parameters to a .txt file.
/// @param numMediums Number of composite layers.
/// @param data Struct where the thermal properties of the composite layers is stored.
/// @param Q Rate of heat transfer within the spherical system (W).
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
/// @param rowsused Number of rows used within the generate profile.
/// @param profile Struct used to store the generated temperature profile.
void CompSphWrite(int numMediums, CondSphMedium data, double Q, double T1, double T2, int rowsused, B48BDTemps profile);

/// This subroutine is used to ask the user whether or not they would like to display/ write the inputted and calculated parameters on the user console/to disk.
/// @param mode Integer value used to control whether data is displayed on the console (1) or written to disk (2).
/// @param numMediums Number of composite layers.
/// @param data Struct where the thermal properties of the composite layers is stored.
/// @param Q Rate of heat transfer within the spherical system (W).
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
/// @param rowsused Number of rows used within the generate profile.
/// @param profile Struct used to store the generated temperature profile.
void CompSphSwitch(int mode, int numMediums, CondSphMedium data, double Q, double T1, double T2, int rowsused, B48BDTemps profile);

#endif /* _2cCompositeSphereWrite_h */
