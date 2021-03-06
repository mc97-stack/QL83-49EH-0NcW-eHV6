//
//  B48BD_T1.h
//  Process Model
//
//  Created by Matthew Cheung on 29/11/2020.
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

#ifndef B48BD_T1_h
#define B48BD_T1_h

/// This subroutine is used to guide the user through converting temperature measurements to different scales.
void TemperatureConversion(void);

/// This subroutine is used to guide the user through calculating the heat transfer by conduction using Fourier's law.
void Conduction(void);

/// This subroutine is used to guide the user through calculating the heat transfer by convection using the steady-state heat convection law.
void Convection(void);

/// This subroutine is used to guide the user through calculating the heat transfer by radiation using the Stefan-Boltzmann law.
void Radiation(void);

#endif /* B48BC_T1_h */
