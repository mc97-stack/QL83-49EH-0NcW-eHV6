//
//  B48BC_T4.h
//  Process Model
//
//  Created by Matthew Cheung on 30/10/2020.
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

#ifndef B48BC_T4_h
#define B48BC_T4_h

/// This subroutine is used to calculate the thermal efficiency of a heat engine extracting heat from a hot thermal reservoir and dumping heat into a cold thermal reservoir. It also contains the calculations comparing the given process to its equivalent carnot cycle to determine whether or not the proposed is in violation of the quality argument of the second law of thermodynamics.
void ThermalEfficiency(void);

/// This subroutine is used to calculate the coefficient of performance for a refrigerator or a heat pump. This, like with "ThermalEfficiency(void)" calculates the equivalent reversible process and checks whether or not the proposed process is in violation of the quality argument of the second law of thermodynamics.
void CoefficientofPerformance(void);

/// This subroutine is used to run a simulation of a carnot cycle and evaluates and quantifies the irreversibility of the process by using the functions given with "ThermalEfficiency(void)" and evaluating the Clausius inequality.
void CarnotCycle(void);

/// This subroutine is used to guide the user through evaluating the thermodynamic feasibility of a process through analysis of the conserved heat-temperature property (entropic contributions) throughout a process. After all heat contributions have been inputted into the subroutine, it then notifies the user of whether the given process is in violation of the second law of thermodynamics.
void ClausiusInequality(void);

#endif /* B48BC_T4_h */
