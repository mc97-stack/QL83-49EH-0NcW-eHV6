//
//  03aFrictFactor.h
//  Process Model
//
//  Created by Matthew Cheung on 09/10/2020.
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

#ifndef Laminar_h
#define Laminar_h

/// This subroutine is used to calculate the friction factor associated with a fluid flowing with laminar flow properties. This subroutine requires "ReyNoCalc(...)" from "02dReyNo.h" to function properly.
/// @param rho Fluid density (kg/ m3)
/// @param u Fluid velocity (m/ s)
/// @param d Pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
double Laminar(double rho, double u, double d, double mu);

#endif /* Laminar_h */

#ifndef Turbulent1_h
#define Turbulent1_h

/// This subroutine is used to calculate the friction factor associated with the pressure loss of a fluid with a turbulent flow profile. This equation is valid between 2500 < Re < 100,000. This subroutine requires "ReyNoCalc(...)" from "02dReyNo.h" to function properly.
/// @param rho Fluid density (kg/ m3)
/// @param u Fluid velocity (m/ s)
/// @param d Pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
double Turbulent1(double rho, double u, double d, double mu);

#endif /* Turbulent1_h */

#ifndef Turbulent2_h
#define Turbulent2_h

/// This subroutine is used to calculate the friction factor associated with the pressure loss of a fluid with a turbulent flow profile through a brute force iteration scheme. This equation is valid when 2500 < Re < 10,000,000. This subroutine requires "ReyNoCalc(...)" from "02dReyNo.h" to function properly.
/// @param rho Fluid density (kg/ m3)
/// @param u Fluid velocity (m/ s)
/// @param d Pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
double Turbulent2(double rho, double u, double d, double mu);

#endif /* Turbulent2_h */

#ifndef Turbulent3_h
#define Turbulent3_h

/// This subroutine is used to calculate the friction factor associated with the pressure loss of a fluid with a turbulent flow profile through a brute force iteration scheme. This equation is valid when Re > 3000 and the friction factor is dependent on relative roughness. This subroutine requires "ReyNoCalc(...)" from "02dReyNo.h" to function properly.
/// @param rho Fluid density (kg/ m3)
/// @param u Fluid velocity (m/ s)
/// @param d Pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
/// @param vareps Absolute roughness (m)
double Turbulent3(double rho, double u, double d, double mu, double vareps);

#endif /* Turbulent3_h */

#ifndef Turbulent4_h
#define Turbulent4_h

/// This subroutine is used to calculate the friction factor associated with the pressure loss of a fluid with a turbulent flow profile. This equation is valid when Re > 3000 and the Friction Factor is independent of surface roughness.
/// @param d Pipe diameter (m)
/// @param vareps Absolute roughness (m)
double Turbulent4(double d, double vareps);

#endif /* Turbulent4_h */
