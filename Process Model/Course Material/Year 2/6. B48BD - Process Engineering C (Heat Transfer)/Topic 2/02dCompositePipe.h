//
//  02dCompositePipe.h
//  Process Model
//
//  Created by Matthew Cheung on 05/12/2020.
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

#ifndef _2dCompositePipeVariable_h
#define _2dCompositePipeVariable_h

typedef struct PipeMedium{
    double k[21];       // Thermal conductivity (W/m.K).
    double h[21];       // Fluid heat transfer coefficient (W/m2.K).
    double r[21];       // Cylinder radius (m).
    double R[21];       // Resistance to heat transfer (K/W).
} PipeMedium;

/// This subroutine is used to collect the variables regarding the general system being analysed.
/// @param T1 Hot surface temperature (deg C).
/// @param T2 Cold surface temperature (deg C).
/// @param L Length of cylinder (m).
/// @param r1 Inner cylinder radius (mm).
void CompPipeExtVariable(double *T1, double *T2, double *L, double *r1);

/// This subroutine is used to collect the variables relating to thermal conduction through a solid layer.
/// @param data Struct where thermal data is stored. This variable is used to verify that a valid radius has been entered into the system.
/// @param i Integer telling the subroutine the location of where the subroutine is writing into.
/// @param k Thermal conductivity (W/m.K).
/// @param r Radius of composite layer (mm).
void CondIntVariable(PipeMedium data, int i, double *k, double *r);

/// This subroutine is used to collect the variables relating to convection within a fluid.
/// @param h Fluid heat transfer coefficient (W/m2.K).
void ConvIntVariable(double *h);

#endif /* _2dCompositePipeVariable_h */

#ifndef _2dCompositePipeCalculation_h
#define _2dCompositePipeCalculation_h

typedef struct TempProfile{
    double k[5000];     // Thermal conductivity (W/m.K).
    double h[5000];     // Fluid heat transfer coefficient (W/m2.K).
    double r[5000];     // Cylinder radius (m).
    double T[5000];     // Temperature at cylinder radius (K).
} TempProfile;

/// This subroutine is used to calculatethe resistance to heat transfer in a system where convection is the main mode of heat transfer. This is calculated by assuming that the thermal boundary layer is negligibly thin.
/// @param h Fluid heat transfer coefficient (W/m2.K).
/// @param r Radius of convective layer (m).
double ConvResistanceCalculation(double h, double r);

/// This subroutine is used to calculate the rate of heat transfer through the composite.
/// @param R Total resistance to heat transfer (K/W).
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
double PipeHeatCalculation(double R, double T1, double T2);

/// This subroutine is used to estimate the final temperature through a composite layer.
/// @param R Element resistance to heat transfer (K/W).
/// @param Q Rate of heat transfer (W).
/// @param T1 Initial element temperature (K).
double ConvTempCalculation(double R, double Q, double T1);

/// This subroutine is used to generate the temperature profile for a system where either convection or conduction can occur.
/// @param numMediums Total number of fluid/solid mediums present within the system.
/// @param data Struct where the thermal property data is stored.
/// @param T1 Hot surface temperature (K).
/// @param r1 Inner cylinder radius (m).
/// @param L Pipe length (m).
/// @param Q Rate of heat transfer (W).
/// @param rowsused Total number of rows used.
TempProfile CompPipeCalculation(int numMediums, PipeMedium data, double T1, double r1, double L, double Q, int *rowsused);

#endif /* _2dCompositePipeCalculation_h */

#ifndef _2dCompositePipeDisplay_h
#define _2dCompositePipeDisplay_h

/// This subroutine is used to display the inputted and calculated parameters on the user console.
/// @param numMediums Total number of fluid/solid mediums present within the system.
/// @param data Struct where the thermal property data is stored.
/// @param Q Rate of heat transfer (W).
/// @param L Pipe length (m).
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
/// @param rowsused Total number of rows used within the temperature profile.
/// @param profile Struct used to store the temperature profile data.
void CompPipeDisplay(int numMediums, PipeMedium data, double Q, double L, double T1, double T2, int rowsused, TempProfile profile);

#endif /* _2dCompositePipeDisplay_h */

#ifndef _2dCompositePipeWrite_h
#define _2dCompositePipeWrite_h

/// This subroutine is used to write the inputted and calculated parameters to disk.
/// @param numMediums Total number of fluid/solid mediums present within the system.
/// @param data Struct where the thermal property data is stored.
/// @param Q Rate of heat transfer (W).
/// @param L Pipe length (m).
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
/// @param rowsused Total number of rows used within the temperature profile.
/// @param profile Struct used to store the temperature profile data.
void CompPipeWrite(int numMediums, PipeMedium data, double Q, double L, double T1, double T2, int rowsused, TempProfile profile);

/// This subroutine is used to ask the user whether or not they would either like to display the inputted and calculated parameters on screen, or write the parameters to disk.
/// @param mode Integer variable used to control whether the inputted and calculated parameters are displayed (1) or written to disk (2).
/// @param numMediums Total number of fluid/solid mediums present within the system.
/// @param data Struct where the thermal property data is stored.
/// @param Q Rate of heat transfer (W).
/// @param L Pipe length (m).
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
/// @param rowsused Total number of rows used within the temperature profile.
/// @param profile Struct used to store the temperature profile data.
void CompPipeSwitch(int mode, int numMediums, PipeMedium data, double Q, double L, double T1, double T2, int rowsused, TempProfile profile);

#endif /* _2dCompositePipeWrite_h */
