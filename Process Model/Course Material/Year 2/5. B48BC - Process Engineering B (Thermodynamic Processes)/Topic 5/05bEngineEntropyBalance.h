//
//  05bEngineEntropyBalance.h
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

#ifndef EngineEntropyBalanceVariable_h
#define EngineEntropyBalanceVariable_h

typedef struct T5Reservoir{
    double q[32];
    double T[32];
    double s[32];
} T5Reservoir;

/// This subroutine is used to collect the work inputted/produced from the thermodynamic cycle.
/// @param mode Integer variable to control whether work description belongs to a heat engine (1) or a heat pump (2).
/// @param work Net work (kJ/kg).
void CycleVariable(int mode, double *work);

/// This subroutine is used to collect the variables related to the hot reservoir.
/// @param qHot Heat supplied to cycle (kJ/kg).
/// @param THot Temperature of the hot reservoir (deg C).
void HotResVariable(int mode, double *qHot, double *THot);

/// This subroutine is used to collect the variables related to the cold reservoir.
/// @param qCold Heat supplied to cycle (kJ/kg).
/// @param TCold Cold reservoir temperature (deg C).
void ColdResVariable(int mode, double *qCold, double *TCold);

/// This subroutine is used to collect the temperature of the system's surroundings.
/// @param TSurr Temperature of the system's surroundings (deg C).
void SurrVariable(double *TSurr);

#endif /* EngineEntropyBalanceVariable_h */

#ifndef EngineEntropyBalanceCalculation_h
#define EngineEntropyBalanceCalculation_h

/// This subroutine is used to perform the entropy balance for a heat engine. After calculation, it then returns the value of the entropy balance.
/// @param HotCount Number of hot reservoirs.
/// @param hot Struct used to store entropy data for the hot reservoir.
/// @param work Net work of the cycle (kJ/kg).
/// @param TSurr Temperature of surroundings (K).
/// @param dSHot Entropy change of the hot reservoir (kJ/kg.K).
/// @param dSCold Entropy change of the cold reservoir (kJ/kg.K).
double HeatEngineEntropyBalance(int HotCount, T5Reservoir hot, double work, double TSurr, double *dSHot, double *dSCold);

/// This subroutine is used to perform the entropy balance for a heat pump/refrigerator. After calculation, it returns the value of the entropy balance.
/// @param ColdCount Number of cold reservoirs.
/// @param cold Struct used to store entropy data for the cold reservoir.
/// @param work Net work of the cycle (kJ/kg).
/// @param TSurr Temperature of surroundings (K).
/// @param dSHot Entropy change of the hot reservoir (kJ/kg.K).
/// @param dSCold Entropy change of the cold reservoir (kJ/kg.K).
double HeatPumpEntropyBalance(int ColdCount, T5Reservoir cold, double work, double TSurr, double *dSHot, double *dSCold);

#endif /* EngineEntropyBalanceCalculation_h */

#ifndef EngineEntropyBalanceDisplay_h
#define EngineEntropyBalanceDisplay_h

/// This subroutine is used to display the inputted and calculated parameters.
/// @param mode Integer variable to control whether variable descriptions belongs to a heat engine (1) or a heat pump (2).
/// @param work net work (kJ/kg)
/// @param TSurr Temperature of surroundings (K)
/// @param hot Struct used to store entropy data for the hot reservoir(s).
/// @param cold Struct used to store entropy data for the cold reservoir(s).
/// @param HotCount Number of hot reservoirs.
/// @param ColdCount Number of cold reservoirs.
/// @param dSHot Entropy change of hot reservoir(s) (kJ/kg.K).
/// @param dSCold Entropy change of cold reservoir(s) (kJ/kg.K).
/// @param dSTotal Total entropy change for system (kJ/kg.K).
void EngineEntropyDisplay(int mode, double work, double TSurr, T5Reservoir hot, T5Reservoir cold, int HotCount, int ColdCount, double dSHot, double dSCold, double dSTotal);

#endif /* EngineEntropyBalanceDisplay_h */

#ifndef EngineEntropyBalanceWrite_h
#define EngineEntropyBalanceWrite_h

/// This subroutine is used to write the inputted and calculated parameters to a tab-delineated .txt file.
/// @param mode Integer variable to control whether variable descriptions belongs to a heat engine (1) or a heat pump (2).
/// @param work net work (kJ/kg)
/// @param TSurr Temperature of surroundings (K)
/// @param hot Struct used to store entropy data for the hot reservoir(s).
/// @param cold Struct used to store entropy data for the cold reservoir(s).
/// @param HotCount Number of hot reservoirs.
/// @param ColdCount Number of cold reservoirs.
/// @param dSHot Entropy change of hot reservoir(s) (kJ/kg.K).
/// @param dSCold Entropy change of cold reservoir(s) (kJ/kg.K).
/// @param dSTotal Total entropy change for system (kJ/kg.K).
void EngineEntropyWrite(int mode, double work, double TSurr, T5Reservoir hot, T5Reservoir cold, int HotCount, int ColdCount, double dSHot, double dSCold, double dSTotal);

/// This subroutine is used to ask the user whether they want to write the inputted and calculated parameters to disk.
/// @param mode Integer variable to control whether variable descriptions belongs to a heat engine (1) or a heat pump (2).
/// @param work net work (kJ/kg)
/// @param TSurr Temperature of surroundings (K)
/// @param hot Struct used to store entropy data for the hot reservoir(s).
/// @param cold Struct used to store entropy data for the cold reservoir(s).
/// @param HotCount Number of hot reservoirs.
/// @param ColdCount Number of cold reservoirs.
/// @param dSHot Entropy change of hot reservoir(s) (kJ/kg.K).
/// @param dSCold Entropy change of cold reservoir(s) (kJ/kg.K).
/// @param dSTotal Total entropy change for system (kJ/kg.K).
void EngineEntropyWriteSwitch(int mode, double work, double TSurr, T5Reservoir hot, T5Reservoir cold, int HotCount, int ColdCount, double dSHot, double dSCold, double dSTotal);

#endif /* EngineEntropyBalanceWrite_h */
