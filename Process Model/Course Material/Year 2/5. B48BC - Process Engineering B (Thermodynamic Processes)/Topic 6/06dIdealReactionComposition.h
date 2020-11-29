//
//  06dIdealReactionComposition.h
//  Process Model
//
//  Created by Matthew Cheung on 27/11/2020.
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

#ifndef _6dIdealReactionCompositionData_h
#define _6dIdealReactionCompositionData_h

typedef struct species{
    double initial[12]; // Initial moles of species present.
    double stoich[12];  // Stoichiometric coefficient.
    double gibbs[12];   // Species gibbs free energy.
} species;

typedef struct GibbsRxn{
    double EoR[1001];        // Extent of reaction.
    double reags[12][1001];  // Reagents composition.
    double reagsmu[12][1001];// Chemical potential of reagents.
    double prods[12][1001];  // Products composition.
    double prodsmu[12][1001];// Chemical potential of products.
    double Gmix[1001];       // Total Gibbs free energy
    double Cond[1001];       // Equilibrium condition.
} GibbsRxn;

#endif /* _6dIdealReactionCompositionData_h */

#ifndef _6dIdealReactionCompositionVariable_h
#define _6dIdealReactionCompositionVariable_h

/// This subroutine is used to collect the variables for the system conditions and reference pressure.
/// @param P System pressure (kPa).
/// @param Pref Reference pressure (atm).
/// @param T System temperature (deg C).
void ReactionVariable(double *P, double *Pref, double *T);

/// This subroutine is used to collect the variables that relate to a chemical species participating in the chemical reaction under analysis.
/// @param type This integer is used to control whether reagent (1) or product (2) is displayed.
/// @param initial Initial moles of reagent or product present.
/// @param stoich Stoichiometric coefficient.
/// @param gibbs Gibbs free energy of formation (J/mol).
void SpeciesVariable(int type, double *initial, double *stoich, double *gibbs);

#endif /* _6dIdealReactionCompositionVariable_h */

#ifndef _6dIdealReactionCompositionCalculation_h
#define _6dIdealReactionCompositionCalculation_h

/// This subroutine is used to determine a species composition from the extent of reaction.
/// @param species Initial amount of species present (mol).
/// @param total Total moles of all species present (mol).
/// @param stoich Species-specific stoichiometric coefficient.
/// @param stoichtotal Overall stoichiometric coefficient.
/// @param EoR Extent of Reaction.
double CompositionCalculation(double species, double total, double stoich, double stoichtotal, double EoR);

/// This subroutine is used to adjust the gibbs energy of formation to a species within an ideal gas mixture.
/// @param molestotal Total moles in reacting mixture.
/// @param gibbs Gibbs free energy of formation (J/mol).
/// @param T System temperature (K).
/// @param P System pressure (atm).
/// @param Pref Reference pressure (atm).
/// @param comp Molar composition of species i.
double SpeciesGibbsEgyCalc(double molestotal, double gibbs, double T, double P, double Pref, double comp);

/// This subroutine is used to calculate the equilibrium constant for a reacting ideal gas mixture.
/// @param products This struct contains the information required for any product species within the reacting mixture.
/// @param reagents This struct contains the information required for any reagent species within the reacting mixture.
/// @param numprods Number of products present in the multicomponent mixture.
/// @param numreags Number of reagents present in the multicomponent mixture.
/// @param T System temperature.
double EquilibriumConstantCalc(species products, species reagents, int numprods, int numreags, double T);

/// This subroutine is used to calculate the Gibbs free energy of mixing for a reacting ideal gas mixture.
/// @param reagents This struct contains the information required for any reagent species within the reacting mixture.
/// @param products This struct contains the information required for any product species within the reacting mixture.
/// @param numreags Number of reagents present.
/// @param numprods Number of products present.
/// @param totalmoles Total moles in the reacting mixture (mol).
/// @param totalstoich Overall stoichiometric coefficient.
/// @param T System temperature (K).
/// @param P System pressure (atm).
/// @param Pref Reference pressure (atm).
GibbsRxn GibbsMixing(species reagents, species products, int numreags, int numprods, double totalmoles, double totalstoich, double T, double P, double Pref);

#endif /* _6dIdealReactionCompositionCalculation_h */

#ifndef _6dIdealReactionCompositionDisplay_h
#define _6dIdealReactionCompositionDisplay_h

/// This subroutine is used to display the inputted and calculated parameters on the user console.
/// @param reagents This struct contains the information required for any reagent species within the reacting mixture.
/// @param products This struct contains the information required for any product species within the reacting mixture.
/// @param numreags Number of reagents present.
/// @param numprods Number of products present.
/// @param totalmoles Total moles in the reacting mixture (mol).
/// @param T System temperature (K).
/// @param P System pressure (atm).
/// @param Pref Reference pressure (atm).
/// @param results This struct contains the calculation table for the Gibbs free energy of mixing.
/// @param K Temperature adjusted equilibrium constant.
/// @param KP Temperature adjusted equilibrium constant.
/// @param totalstoich Overall stoichiometric coefficient.
void IdealRxnCompDisplay(species reagents, species products, int numreags, int numprods, double totalmoles, double T, double P, double Pref, GibbsRxn results, double K, double KP, double totalstoich);

#endif /* _6dIdealReactionCompositionDisplay_h */

#ifndef _6dIdealReactionCompositionWrite_h
#define _6dIdealReactionCompositionWrite_h

/// This subroutine is used to write the inputted and calculated parameters to a .txt file.
/// @param reagents This struct contains the information required for any reagent species within the reacting mixture.
/// @param products This struct contains the information required for any product species within the reacting mixture.
/// @param numreags Number of reagents present.
/// @param numprods Number of products present.
/// @param totalmoles Total moles in the reacting mixture (mol).
/// @param T System temperature (K).
/// @param P System pressure (atm).
/// @param Pref Reference pressure (atm).
/// @param results This struct contains the calculation table for the Gibbs free energy of mixing.
/// @param K Temperature adjusted equilibrium constant.
/// @param KP Temperature adjusted equilibrium constant.
/// @param totalstoich Overall stoichiometric coefficient.
void IdealRxnCompWrite(species reagents, species products, int numreags, int numprods, double totalmoles, double T, double P, double Pref, GibbsRxn results, double K, double KP, double totalstoich);

/// This subroutine is used to ask the user whether or not they would like to display/write the gathered data to the user console/disk.
/// @param mode This integer variable is used to control whether the inputted and calculated parameters are either displayed on the user console (1) or written to disk (2).
/// @param reagents This struct contains the information required for any reagent species within the reacting mixture.
/// @param products This struct contains the information required for any product species within the reacting mixture.
/// @param numreags Number of reagents present.
/// @param numprods Number of products present.
/// @param totalmoles Total moles in the reacting mixture (mol).
/// @param T System temperature (K).
/// @param P System pressure (atm).
/// @param Pref Reference pressure (atm).
/// @param results This struct contains the calculation table for the Gibbs free energy of mixing.
/// @param K Temperature adjusted equilibrium constant.
/// @param KP Temperature adjusted equilibrium constant.
/// @param totalstoich Overall stoichiometric coefficient.
void IdealRxnCompSwitch(int mode, species reagents, species products, int numreags, int numprods, double totalmoles, double T, double P, double Pref, GibbsRxn results, double K, double KP, double totalstoich);

#endif /* _6dIdealReactionCompositionWrite_h */
