//
//  System.h
//  Process Model
//
//  Created by Matthew Cheung on 24/10/2020.
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

#ifndef Input_h
#define Input_h

/// This subroutine is used to collect character input and convert the inputted array to a double value. 
/// @param allowZero Integer value used to control whether a zero value is permitted in the data entry. A value of 0 will force a non-zero value to be entered.
/// @param allowNeg Integer value used to control whether a negative value is permitted in the data entry. A value of 0 will force a positive value to be entered.
/// @param VariableName Variable descriptor.
/// @param Units Units of the variable.
double inputDouble(int allowZero, int allowNeg, char VariableName[], char Units[]);

#endif /* Input_h */

#ifndef Timer_h
#define Timer_h

/// This subroutine takes and returns the difference between two time states of the internal CPU.
/// @param start Starting time state of process.
/// @param end Ending time state of process.
double timer(struct timespec start, struct timespec end);

#endif /* Timer_h */

#ifndef pcterr_h
#define pcterr_h

/// This subroutine is used calculate the percentage error in a calculated value 
/// @param input Calculated value.
/// @param data Empirical value.
double pcterror(double input, double data);

#endif /* pcterr_h */

#ifndef Continue_h
#define Continue_h

/// This subroutine is used to control whether the user would like to continue with another round of calculations or go to the above menu.
/// @param ControlVariable Variable controlling the main loop in the subroutine it is called from.
int Continue(int ControlVariable);

#endif /* System_h */
