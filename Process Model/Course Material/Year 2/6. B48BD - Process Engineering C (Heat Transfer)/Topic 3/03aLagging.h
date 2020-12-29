//
//  03aLagging.h
//  Process Model
//
//  Created by Matthew Cheung on 19/12/2020.
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

#ifndef _3aLaggingData_h
#define _3aLaggingData_h

typedef struct LaggingData{
    double k[4];    // Thermal conductivity (W/m.K).
    double h[4];    // Fluid heat transfer coefficient (W/m2.K).
    double r[4];    // Outer layer radius (m).
} LaggingData;

typedef struct LaggingTable{
    double x[32];       // Lagging thickness (m).
    double R_lag[32];   // Lagging resistance (K.m/W).
    double R_out[32];   // Air resistance (K.m/W).
    double R_tot[32];   // Total resistance to heat transfer (K.m/W).
    double Q[32];       // Heat transferred (W/m).
    double pctLag[32];  // Percentage resistance in lagging.
} LaggingTable;

#endif /* _3aLaggingData_h */

#ifndef _3aLaggingVariable_h
#define _3aLaggingVariable_h

/// This subroutine is used to collect the variables regarding the general system being analysed.
/// @param T1 Hot surface temeprature (deg C).
/// @param T2 Cold surface temperature (deg C).
/// @param r1 Inner pipe radius (cm).
void LaggingExtVariable(double *T1, double *T2, double *r1);

/// This subroutine is used to collect the variables related to the heat transfer properties of a layer within the composite.
/// @param mode1 This variable controls whether k (1) or h (2) is collected.
/// @param mode2 This variable control whether (1) or not (0) the radius is collected.
/// @param i Element identifier within the data struct.
/// @param data Struct used to store the thermal property data of each composite layer.
LaggingData LaggingIntVariable(int mode1, int mode2, int i, LaggingData data);

#endif /* _3aLaggingVariable_h */

#ifndef _3aLaggingCalculation_h
#define _3aLaggingCalculation_h

/// This subroutine is used to calculate the resistance to heat transfer arising from convection.
/// @param h Fluid heat transfer coefficeint (W/m2.K).
/// @param r Layer radius (m).
double LagConvResist(double h, double r);

/// This subroutine is used to calculate the resistance to heat transfer arising from conduction.
/// @param k Thermal conductivity (W/m.K).
/// @param r1 Inner layer radius (m).
/// @param r2 Outer layer radius (m).
double LagCondResist(double k, double r1, double r2);

/// This subroutine calculates the total resistance to heat transfer in the composite system.
/// @param data Struct used to store thermal property data.
double LagTotalResist(LaggingData data);

/// This subroutine is used to calculate the rate of heat transfer per metre pipe in the composite system.
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
/// @param R Resistance to heat transfer (K.m/W).
double LagHeat(double T1, double T2, double R);

/// This subroutine is used to generate the table to show how lagging thickness affects the rate of heat transfer.
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
/// @param data Struct used to store thermal property data.
LaggingTable LaggingCalculation(double T1, double T2, LaggingData *data);

#endif /* _3aLaggingCalculation_h */

#ifndef _3aLaggingDisplay_h
#define _3aLaggingDisplay_h

/// This subroutine is used to display the inputted parameters and calculated data table on the user console.
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
/// @param data Struct used to store thermal property data.
/// @param results Struct used to store the generated data table.
void LaggingDisplay(double T1, double T2, LaggingData data, LaggingTable results);

#endif /* _3aLaggingDisplay_h */

#ifndef _3aLaggingWrite_h
#define _3aLaggingWrite_h

/// This subroutine is used to write the inputted parameters and calculated data table to a .txt file.
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
/// @param data Struct used to store thermal property data.
/// @param results Struct used to store the generated data table.
void LaggingWrite(double T1, double T2, LaggingData data, LaggingTable results);

/// This subroutine is used to ask the user whether they would like to either display or write the inputted and calculated parameters.
/// @param mode This variable is used to control whether this subroutine displays (1) or writes (2) the inputted and calculated parameters to the user console or disk.
/// @param T1 Hot surface temperature (K).
/// @param T2 Cold surface temperature (K).
/// @param data Struct used to store thermal property data.
/// @param results Struct used to store the generated data table.
void LaggingSwitch(int mode, double T1, double T2, LaggingData data, LaggingTable results);

#endif /* _3aLaggingWrite_h */
