//
//  B48BB_T2.h
//  Process Model
//
//  Created by Matthew Cheung on 19/08/2020.
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

#ifndef B48BB_T2_h
#define B48BB_T2_h

/// This subroutine guides the user through gathering the data and calculation of volumetric and mass flow rates at a process endstate.
void MassConservation(void);

/// This subroutine guides the user through gathering the data and determining whether the system is at steady-state or not.
void EnergyConservation(void);

/// This subroutine guides the user through gathering the data and calculation of the fluid pressure at a process endstate through Bernoulli's equation.
void BernoulliEquation(void);

/// This subroutine guides the user through gathering the data and calculation of Reynold's number for a fluid
void ReynoldsNumber(void);

/// This subroutine guides the user through gathering the data and calculation of dynamic and kinematic viscosity.
void ViscosityCorrelation(void);

/// This subroutine guides the user through gathering the data and estimation of the velocity profile for a flowing fluid with either fully developed laminar or turbulent properties.
void VelocityProfileMenu(void);

/// This subroutine guides the user through gathering the data and calculation of the pressure losses incurred by a fluid flowing with fully developed laminar flow properties.
void HagenPoiseuille(void);

#endif /* B48BB_T2_h */
