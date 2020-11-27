//
//  06cEquilibriumConstant.h
//  Process Model
//
//  Created by Matthew Cheung on 26/11/2020.
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

#ifndef _6cEquilibriumConstantVariable_h
#define _6cEquilibriumConstantVariable_h

/// This subroutine is used to collect the variables used to adjust the equilibrium constant for temperature and pressure.
/// @param mode This integer variable is used to control whether variables for temperature adjustment (1) are collected or for temperature and pressure adjustment (2).
/// @param h_rxn Enthalpy change of reaction (J/mol).
/// @param K1 Reference equilibrium constant ([ ]).
/// @param T1 Reference equilibrium constant temperature (deg C).
/// @param T2 System temperature (deg C).
/// @param P1 Reference system pressure (bar).
/// @param stoich Overall stoichiometric coefficient.
void EquiConstVariable(int mode, double *h_rxn, double *K1, double *T1, double *T2, double *P1, double *stoich);

#endif /* _6cEquilibriumConstantVariable_h */

#ifndef _6cEquilibriumConstantCalculation_h
#define _6cEquilibriumConstantCalculation_h

/// This subroutine is used to calculate the temperature adjusted equilibrium constant using the Van't Hoff equation.
/// @param h_rxn Enthalpy change of reaction (J/mol).
/// @param K1 Reference equilibrium constant ([ ]).
/// @param T1 Reference equilibrium constant temperature (K).
/// @param T2 System temperature (K).
double VantHoffCalculation(double h_rxn, double K1, double T1, double T2);

/// This subroutine is used to calculate the temperature adjusted equilibrium constant through a series of 100 quasi-static temperature changes.
/// @param h_rxn Enthalpy change of reaction (J/mol).
/// @param K1 Reference equilibrium constant ([ ]).
/// @param T1 Reference equilibrium constant temperature (K).
/// @param T2 System temperature (K).
double VantHoffCalc(double h_rxn, double K1, double T1, double T2);

/// This subroutine is used to calculate the pressure adjusted equilibrium constant.
/// @param Pref Reference equilibrium constant pressure (bar).
/// @param stoich Overall stoichiometric coefficient.
/// @param K2 Temperature adjusted equilibrium constant ([ ]).
double KPCalculation(double Pref, double stoich, double K2);

#endif /* _6cEquilibriumConstantCalculation_h */

#ifndef _6cEquilibriumConstantDisplay_h
#define _6cEquilibriumConstantDisplay_h

/// This subroutine is used to display the inputted and calculated parameters on the user console.
/// @param mode This integer variable is used to control whether variables for temperature adjustment (1) are collected or for temperature and pressure adjustment (2).
/// @param h_rxn Enthalpy change of reaction (J/mol).
/// @param K1 Reference equilibrium constant ([ ]).
/// @param K2 Temperature adjusted equilibrium constant.
/// @param KP Pressure adjusted equilibrium constant ([ ]).
/// @param T1 Reference equilibrium constant temperature (K).
/// @param T2 System temperature (K).
/// @param P1 Reference equilibrium constant pressure (bar).
/// @param stoich Overall stoichiometric coefficient.
void EquiConstDisplay(int mode, double h_rxn, double K1, double K2, double KP, double T1, double T2, double P1, double stoich);

#endif /* _6cEquilibriumConstantDisplay_h */

#ifndef _6cEquilibriumConstantWrite_h
#define _6cEquilibriumConstantWrite_h

/// This subroutine is used to write the inputted and calculated parameters to a .txt file.
/// @param mode This integer variable is used to control whether variables for temperature adjustment (1) are collected or for temperature and pressure adjustment (2).
/// @param h_rxn Enthalpy change of reaction (J/mol).
/// @param K1 Reference equilibrium constant ([ ]).
/// @param K2 Temperature adjusted equilibrium constant.
/// @param KP Pressure adjusted equilibrium constant ([ ]).
/// @param T1 Reference equilibrium constant temperature (K).
/// @param T2 System temperature (K).
/// @param P1 Reference equilibrium constant pressure (bar).
/// @param stoich Overall stoichiometric coefficient.
void EquiConstWrite(int mode, double h_rxn, double K1, double K2, double KP, double T1, double T2, double P1, double stoich);

/// This subroutine is used to ask the user whether or not they would like to write the inputted and calculated parameters to disk.
/// @param mode This integer variable is used to control whether variables for temperature adjustment (1) are collected or for temperature and pressure adjustment (2).
/// @param h_rxn Enthalpy change of reaction (J/mol).
/// @param K1 Reference equilibrium constant ([ ]).
/// @param K2 Temperature adjusted equilibrium constant.
/// @param KP Pressure adjusted equilibrium constant ([ ]).
/// @param T1 Reference equilibrium constant temperature (K).
/// @param T2 System temperature (K).
/// @param P1 Reference equilibrium constant pressure (bar).
/// @param stoich Overall stoichiometric coefficient.
void EquiConstWriteSwitch(int mode, double h_rxn, double K1, double K2, double KP, double T1, double T2, double P1, double stoich);

#endif /* _6cEquilibriumConstantWrite_h */
