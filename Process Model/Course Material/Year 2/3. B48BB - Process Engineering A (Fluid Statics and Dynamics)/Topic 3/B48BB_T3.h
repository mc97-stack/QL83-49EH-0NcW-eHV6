//
//  B48BB_T3.h
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

#ifndef B48BB_T3_h
#define B48BB_T3_h

/// This subroutine guides the user through gathering the data and calculation of pressure losses for a moving fluid between Reynold's number of 0 < Re <= 10,000,000.
void GeneralPressureLoss(void);

/// This subroutine guides the user through gathering the data and calculation of hydraulic diameter for a non-circular pipe.
void HydraulicDiameter(void);

/// This subroutine guides the user through gathering the data and calculation of pressure losses through pipe fittings with the 1K, 2K, 3K and equivalent length methods.
void Fittings(void);

/// This subroutine guides the user through gathering the data and calculation of pressure of a flowing fluid using a pitot static tube.
void PitotStaticTube(void);

/// This subroutine guides the user through gathering the data and calculation of the mass flowrate of a flowing fluid through an orifice plate meter.
void OrificePlateMeter(void);

/// This subroutine guides the user through gathering the data and calculation of the mass flowrate of a flowing fluid through a rotameter.
void Rotameter(void);

#endif /* B48BB_T3_h */
