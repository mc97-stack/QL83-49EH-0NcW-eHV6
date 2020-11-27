//
//  06aExtentOfReaction.h
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

#ifndef _6aExtentOfReactionVariable_h
#define _6aExtentOfReactionVariable_h

/// This subroutine is used to collect the variables required to calculate the extent of reaction.
/// @param reacted Moles of species i reacted (mol).
/// @param stoich Stoichiometric coefficient.
void EoRVariable(double *reacted, double *stoich);

#endif /* _6aExtentOfReactionVariable_h */

#ifndef _6aExtentOfReactionCalculation_h
#define _6aExtentOfReactionCalculation_h

/// This subroutine is used to calculate and return the extent of reaction to the calling function. 
/// @param reacted Moles of species i reacted (mol).
/// @param stoich Stoichiometric coefficient.
double EoRCalculation(double reacted, double stoich);

#endif /* _6aExtentOfReactionCalculation_h */

#ifndef _6aExtentOfReactionDisplay_h
#define _6aExtentOfReactionDisplay_h

/// This subroutine is used to display the inputted and calculated parameters on the user console.
/// @param reacted Moles of species i reacted (mol).
/// @param stoich Stoichiometric coefficient.
/// @param EoR Extent of reaction (mol).
void EoRDisplay(double reacted, double stoich, double EoR);

#endif /* _6aExtentOfReactionDisplay_h */

#ifndef _6aExtentOfReactionWrite_h
#define _6aExtentOfReactionWrite_h

/// This subroutine is used to ask the user whether they would like to write the inputted and calculated parameters to disk.
/// @param reacted Moles of species i reacted (mol).
/// @param stoich Stoichiometric coefficient.
/// @param EoR Extent of reaction (mol).
void EoRWrite(double reacted, double stoich, double EoR);

#endif /* _6aExtentOfReactionWrite_h */
