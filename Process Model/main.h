//
//  main.h
//  Process Model
//  
//  Created by Matthew Cheung on 17/08/2020.
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

#ifndef main_h
#define main_h

/// This subroutine contains the menu for the pipeline designer and subroutines for sizing minor unit operations.
void MinorUnitOps(void);

/// This subroutine contains the menu for the sizing of major unit operations.
void MajorUnitOps(void);

/// This subroutine contains a series of switch statements allowing the user to select from the subroutines made for the courses.
void CourseSelection(void);

/// This subroutine contains the menu for any subroutines made from reading literature.
void Reading(void);

/// This subroutine contains subroutines related to running a dynamic process simulation.
void DynProcessSim(void);

/// This subroutine contains any additional content.
void NiceThings(void);

/// This subroutine is used to display the GNU General Public License on the user console.
void License(void);

/// This subroutine is the system entry point for the entire program.
int main(void);

#endif /* main_h */
