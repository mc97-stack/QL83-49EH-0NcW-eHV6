//
//  03dTwoK.h
//  Process Model
//
//  Created by Matthew Cheung on 22/10/2020.
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

#ifndef TwoKStruct
#define TwoKStruct

typedef struct TwoKFittings{
    int k1[32];
    double kinf[32];
    int count[32];
    double headloss[32];
    double dP_f[32];
} TwoKFittings;

#endif /* TwoKStruct */

#ifndef TwoKData_h
#define TwoKData_h

/// This subroutine is used to write the 2K database into the struct where data is to be entered.
/// @param input Table where 2K database constants should be written to.
TwoKFittings TwoKData(TwoKFittings input);

/// This subroutine is used to collect the required data to run calculate the head and pressure losses through the 2K method.
/// @param table Table where collected variables should be stored.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Internal pipe diameter (mm)
/// @param mu Fluid viscosity (cP)
/// @param Impd Internal pipe diameter (inches)
TwoKFittings TwoKVariable(TwoKFittings table, double *rho, double *u, double *d, double *mu, double *Impd);

#endif /* TwoKData_h */

#ifndef TwoKCalc_h
#define TwoKCalc_h

/// This subroutine is used to calculate the resistance coefficient with the 2K method.
/// @param Re Reynolds number ([ ])
/// @param d Internal pipe diameter (inches)
/// @param k1 Resistance Coefficient at Re = 1.
/// @param kinf Resistance Coefficeint at Re = \infty.
double TwoKCalculateK(double Re, double d, double k1, double kinf);

/// This subroutine is used to calculate the head loss associated with a specific fitting.
/// @param count Number of fittings
/// @param K Resistance coefficeint calculated with "TwoKCalcK(...)".
/// @param u Fluid velocity (m/s)
double TwoKCalculateHead(int count, double K, double u);

/// This subroutine is used to calculate the pressure loss associated with a specific fitting.
/// @param h Head loss (m)
/// @param rho Fluid density (kg/m3)
double TwoKCalculatePLoss(double h, double rho);

/// This subroutine is used to perform the calculations for the head and pressure losses through the 2K method. 
/// @param data Table containing collected data.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Internal pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
/// @param Impd Internal pipe diameter (inches)
/// @param Re Reynold's number
TwoKFittings TwoKFinalTable(TwoKFittings data, double rho, double u, double d, double mu, double Impd, double *Re);

#endif /* TwoKCalc_h */

#ifndef TwoKDisp_h
#define TwoKDisp_h

/// This subroutine is used to display the collected data and generated data table on the user console.
/// @param data Table containing collected data and calculated parameters.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Internal pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
/// @param Re Reynold's number
/// @param TotalP Total pressure loss (Pa)
/// @param TotalH Total head loss (m)
void TwoKDisplay(TwoKFittings data, double rho, double u, double d, double mu, double Re, double TotalP, double TotalH);

#endif /* TwoKDisp_h */

#ifndef TwoKWrite_h
#define TwoKWrite_h

/// This subroutine is used to write the collect data and calculated parameters to a .txt file.
/// @param data Table containing collected data and calculated parameters.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Internal pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
/// @param Re Reynold's number
/// @param TotalP Total pressure loss (Pa)
/// @param TotalH Total head loss (m)
void TwoKWrite(TwoKFittings data, double rho, double u, double d, double mu, double Re, double TotalP, double TotalH);

/// This subroutine is used to ask the user if they would like to write the generated dataset and calculated parameters to a file.
/// @param data Table containing collected data and calculated parameters.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Internal pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
/// @param Re Reynold's number
/// @param TotalP Total pressure loss (Pa)
/// @param TotalH Total head loss (m)
void TwoKWriteSwitch(TwoKFittings data, double rho, double u, double d, double mu, double Re, double TotalP, double TotalH);

#endif /* TwoKWrite_h */

#ifndef TwoK_h
#define TwoK_h

/// This subroutine us used to guide the computer through gathering the required data and performing calculations for the 2K head loss method.
void TwoK(void);

#endif /* TwoK_h */
