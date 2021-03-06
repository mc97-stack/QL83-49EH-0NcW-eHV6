//
//  B48BB_T1.h
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

#ifndef B48BB_T1_h
#define B48BB_T1_h

/// This subroutine guides the user through gathering the data and calculation of the fluid coefficient of compressibility derived from the ideal gas law.
void CoefficientofCompressibility(void);

/// This subroutine guides the user through gathering the data and calculation of the hydrostatic pressure gradient for a stationary fluid.
void FluidVerticalHydrostaticPressure(void);

/// This subroutine guides the user through gathering the data and calculation of the pressure that a fluid exerts of a system wall through either a vertical or inclined manometer.
void Manometer(void);

/// This subroutine guides the user through gathering the data and calculation of  the force required to break a fluid's surface through the du Nouy ring method.
void SurfaceTension(void);

/// This subroutine guides the user through gathering the data and calculation of bubble pressure using the fluid surface tension.
void BubblePressure(void);

/// This subroutine guides the user through gathering the data and calculation of capillarity effects from surface tension data.
void Cappilarity(void);

#endif /* B48BB_T1_h */
