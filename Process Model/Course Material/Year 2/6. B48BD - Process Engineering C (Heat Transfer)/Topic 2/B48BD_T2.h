//
//  B48BD_T2.h
//  Process Model
//
//  Created by Matthew Cheung on 01/12/2020.
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

#ifndef B48BD_T2_DATA_h
#define B48BD_T2_DATA_h

typedef struct B48BDTemps {     // Allows for 20 composite layers with 250 elements.
    double k[5000];     // Thermal conductivity present.
    double x[5000];     // Linear/Radial thickness into composite.
    double T[5000];     // Temperature (K).
} B48BDTemps;

#endif /* B48BD_T2_DATA_h */

#ifndef B48BD_T2_h
#define B48BD_T2_h

/// This subroutine is used to guide the user through calculating the interface temperatures through a composite plane.
void CompositePlane(void);

/// This subroutine is used to guide the user through calculating the interface temperatures through a composite cylinder.
void CompositeCylinder(void);

/// This subroutine is used to guide the user through calculating the interface temperatures through a composite sphere.
void CompositeSphere(void);

/// This subroutine is used to guide the user through calculating the interface temperature through a composite cylinder applied to fluid flow.
void CompositePipe(void);

/// This subroutine is used to guide the user through finding the optimal lagging thickness using the composite cylinder calculations.
void Lagging(void);

#endif /* B48BD_T2_h */
