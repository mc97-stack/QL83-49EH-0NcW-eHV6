//
//  06bEquilibriumConversion.h
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

#ifndef _6bEquilibriumConversionVariable_h
#define _6bEquilibriumConversionVariable_h

/// This subroutine is used to collect the variables required to calculate the equilibrium conversion.
/// @param mode This integer value is used to control whether the moles reacted is collected or the stoichiometric coefficient and extent of reaction.
/// @param reacted Moles of species i reacted (mol).
/// @param stoich Stoichiometric coefficient.
/// @param EoR Extent of reaction (mol).
/// @param initial Moles of species i initially present (mol).
void EquiConvVariable(int mode, double *reacted, double *stoich, double *EoR, double *initial);

#endif /* _6bEquilibriumConversionVariable_h */

#ifndef _6bEquilibriumConversionCalculation_h
#define _6bEquilibriumConversionCalculation_h

/// This subroutine is used to calculate and return the equilibrium conversion through the moles of species i reacted compared to its initial value.
/// @param reacted Moles of species i reaction (mol).
/// @param initial Moles of species i initially present (mol).
double EquiConvCalc1(double reacted, double initial);

/// This subroutine is used to calculate and return the equilibrium conversion through the extent of reaction, stoichiometric coefficient and the amount of species i initially present.
/// @param stoich Stoichiometric coefficient.
/// @param EoR Extent of reaction (mol).
/// @param initial Moles of species i initially present (mol).
double EquiConvCalc2(double stoich, double EoR, double initial);

#endif /* _6bEquilibriumConversionCalculation_h */

#ifndef _6bEquilibriumConversionDisplay_h
#define _6bEquilibriumConversionDisplay_h

/// This subroutine is used to display the inputted and calculated parameters on the user console.
/// @param mode This integer value is used to control whether the moles reacted is collected or the stoichiometric coefficient and extent of reaction.
/// @param reacted Moles of species i reacted (mol).
/// @param stoich Stoichiometric coefficient.
/// @param EoR Extent of reaction (mol).
/// @param initial Moles of species i initially present (mol).
/// @param Conv Equilibrium conversion (%).
void EquiConvDisplay(int mode, double reacted, double stoich, double EoR, double initial, double Conv);

#endif /* _6bEquilibriumConversionDisplay_h */

#ifndef _6bEquilibriumConversionWrite_h
#define _6bEquilibriumConversionWrite_h

/// This subroutine is used to write the inputted and calculated parameters to a .txt file.
/// @param mode This integer value is used to control whether the moles reacted is collected or the stoichiometric coefficient and extent of reaction.
/// @param reacted Moles of species i reacted (mol).
/// @param stoich Stoichiometric coefficient.
/// @param EoR Extent of reaction (mol).
/// @param initial Moles of species i initially present (mol).
/// @param Conv Equilibrium conversion (%).
void EquiConvWrite(int mode, double reacted, double stoich, double EoR, double initial, double Conv);

/// This subroutine is used to ask the user whether or not they would like to write the inputted and calculated parameters to disk.
/// @param mode This integer value is used to control whether the moles reacted is collected or the stoichiometric coefficient and extent of reaction.
/// @param reacted Moles of species i reacted (mol).
/// @param stoich Stoichiometric coefficient.
/// @param EoR Extent of reaction (mol).
/// @param initial Moles of species i initially present (mol).
/// @param Conv Equilibrium conversion (%).
void EquiConvWriteSwitch(int mode, double reacted, double stoich, double EoR, double initial, double Conv);

#endif /* _6bEquilibriumConversionWrite_h */
