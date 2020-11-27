//
//  05aEntropyBalance.h
//  Process Model
//
//  Created by Matthew Cheung on 24/11/2020.
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

#ifndef EntropyBalanceVariable_h
#define EntropyBalanceVariable_h

/// This subroutine collects the parameters required for an entropy balance on an isobaric system undergoing a change in temperature.
/// @param m Mass present in system (kg/s).
/// @param cp Heat capacity at constant pressure (kJ/kg.K).
/// @param T1 Initial system temperature (deg C).
/// @param T2 Final system temperature (deg C).
/// @param TSurr Temperature of surroundings (deg C).
void EntropyBalanceVariable(double *m, double *cp, double *T1, double *T2, double *TSurr);

#endif /* EntropyBalanceVariable_h */

#ifndef EntropyBalanceCalculation_h
#define EntropyBalanceCalculation_h

/// This subroutine is used to calculate the entropy change in the system undergoing an isobaric proces. The entropy change for the system is returned in units (kW/K).
/// @param m Mass present in system (kg/s).
/// @param cp Heat capacity at constant pressure (kJ/kg.K).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
double EntropyBalanceSysCalc(double m, double cp, double T1, double T2);

/// This subroutine is used to calculate the entropy change in the surroundings of a system undergoing an isobaric process. The entropy change for the surroundings is returned in units (kW/K).
/// @param m Mass present in system (kg/s).
/// @param cp Heat capacity at constant pressure (kJ/kg.K).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param TSurr Temperature of surroundings (K).
double EntropyBalanceSurrCalc(double m, double cp, double T1, double T2, double TSurr);

/// This subroutine is used to perform the entropy balance.
/// @param System Entropy change in system (kW/K)
/// @param Surroundings Entropy change in surroundings (kW/K).
double EntropyBalance(double System, double Surroundings);

#endif /* EntropyBalanceCalculation_h */

#ifndef EntropyBalanceDisplay_h
#define EntropyBalanceDisplay_h

/// This subroutine is used to display the collected and calculated parameters on the user console.
/// @param m Mass present in system (kg/s).
/// @param cp Heat capacity at constant pressure (kJ/kg.K).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param TSurr Temperature of surroundings (K).
/// @param SysEntropy Entropy change in system (kW/K).
/// @param SurrEntropy Entropy change in surroundings (kW/K).
/// @param TotalEntropy Total entropy change (kW/K).
void EntropyBalanceDisplay(double m, double cp, double T1, double T2, double TSurr, double SysEntropy, double SurrEntropy, double TotalEntropy);

#endif /* EntropyBalanceDisplay_h */

#ifndef EntropyBalanceWrite_h
#define EntropyBalanceWrite_h

/// This subroutine is used to write the collected and calculated parameters to a tab-delineated .txt file.
/// @param m Mass present in system (kg/s).
/// @param cp Heat capacity at constant pressure (kJ/kg.K).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param TSurr Temperature of surroundings (K).
/// @param SysEntropy Entropy change in system (kW/K).
/// @param SurrEntropy Entropy change in surroundings (kW/K).
/// @param TotalEntropy Total entropy change (kW/K).
void EntropyBalanceWrite(double m, double cp, double T1, double T2, double TSurr, double SysEntropy, double SurrEntropy, double TotalEntropy);

/// This subroutine is used to ask the user if they would like to write the results of this subroutine to disk.
/// @param m Mass present in system (kg/s).
/// @param cp Heat capacity at constant pressure (kJ/kg.K).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param TSurr Temperature of surroundings (K).
/// @param SysEntropy Entropy change in system (kW/K).
/// @param SurrEntropy Entropy change in surroundings (kW/K).
/// @param TotalEntropy Total entropy change (kW/K).
void EntropyBalanceWriteSwitch(double m, double cp, double T1, double T2, double TSurr, double SysEntropy, double SurrEntropy, double TotalEntropy);

#endif /* EntropyBalanceWrite_h */
