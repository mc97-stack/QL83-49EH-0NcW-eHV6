//
//  01aTemperatureConversion.h
//  Process Model
//
//  Created by Matthew Cheung on 30/11/2020.
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

#ifndef _1aTemperatureConversionVariable_h
#define _1aTemperatureConversionVariable_h

/// This subroutine is used to collect the temperature measurement that needs converting.
/// @param mode This integer controls what units are displayed. (1) Celsius. (2) Fahrenheit. (3) Kelvin. (4) Rankine.
/// @param temp Temperature measurement.
void TempConvVariable(int mode, double *temp);

#endif /* _1aTemperatureConversionVariable_h */

#ifndef _1aTemperatureConversionCalculation_h
#define _1aTemperatureConversionCalculation_h

/// This subroutine is used to convert degrees Celsius to degrees Fahrenheit.
/// @param temp Temperature (deg C).
double CelsiusFahrenheitConv(double temp);

/// This subroutine is used to convert degrees Fahrenheit to degrees celsius.
/// @param temp Temperature (deg F).
double FahrenheitCelsiusConv(double temp);

/// This subroutine is used to convert degrees Celsius to Kelvin.
/// @param temp Temperature (deg C).
double CelsiusKelvin(double temp);

/// This subroutine is used to convert Kelvin to degrees to Celsius.
/// @param temp Temperature (K).
double KelvinCelsius(double temp);

/// This subroutine is used to convert degrees Fahrenheit to Rankine.
/// @param temp Temperature (deg F).
double FahrenheitRankine(double temp);

/// This subroutine is used to convert Rankine to degrees Fahrenheit.
/// @param temp Temperature (R).
double RankineFahrenheit(double temp);

/// This subroutine is used to control what a temperature measurement gets converted into.
/// @param initialUnits Units that the temperature measurement was made in. (1) Celsius. (2) Fahrenheit. (3) Kelvin. (4) Rankine.
/// @param outputUnits Units that the user wishes to convert the temperature measurement into. (1) Celsius. (2) Fahrenheit. (3) Kelvin. (4) Rankine.
/// @param measurement Temperature measurement.
/// @param celsius Converted temperature (deg C).
/// @param fahrenheit Converted temperature (deg F).
/// @param kelvin Converted temperature (K).
/// @param rankine Converted temperature (R).
void TempConverter(int initialUnits, int outputUnits, double measurement, double *celsius, double *fahrenheit, double *kelvin, double *rankine);

#endif /* _1aTemperatureConversionCalculation_h */

#ifndef _1aTemperatureConversionDisplay_h
#define _1aTemperatureConversionDisplay_h

/// This subroutine is used to display the inputted and calculated parameters on the user console.
/// @param initialUnits Units that the temperature measurement was made in. (1) Celsius. (2) Fahrenheit. (3) Kelvin. (4) Rankine.
/// @param outputUnits Units that the user wishes to convert the temperature measurement into. (1) Celsius. (2) Fahrenheit. (3) Kelvin. (4) Rankine.
/// @param measurement Temperature measurement.
/// @param celsius Converted temperature (deg C).
/// @param fahrenheit Converted temperature (deg F).
/// @param kelvin Converted temperature (K).
/// @param rankine Converted temperature (R).
void TempConvDisplay(int initialUnits, int outputUnits, double measurement, double celsius, double fahrenheit, double kelvin, double rankine);

#endif /* _1aTemperatureConversionDisplay_h */

#ifndef _1aTemperatureConversionWrite_h
#define _1aTemperatureConversionWrite_h

/// This subroutine is used to write the inputted and calculated parameters to a .txt file.
/// @param initialUnits Units that the temperature measurement was made in. (1) Celsius. (2) Fahrenheit. (3) Kelvin. (4) Rankine.
/// @param outputUnits Units that the user wishes to convert the temperature measurement into. (1) Celsius. (2) Fahrenheit. (3) Kelvin. (4) Rankine.
/// @param measurement Temperature measurement.
/// @param celsius Converted temperature (deg C).
/// @param fahrenheit Converted temperature (deg F).
/// @param kelvin Converted temperature (K).
/// @param rankine Converted temperature (R).
void TempConvWrite(int initialUnits, int outputUnits, double measurement, double celsius, double fahrenheit, double kelvin, double rankine);

/// This subroutine is used to ask the user whether or not they would like to write the inputted and calculated parameters to disk.
/// @param initialUnits Units that the temperature measurement was made in. (1) Celsius. (2) Fahrenheit. (3) Kelvin. (4) Rankine.
/// @param outputUnits Units that the user wishes to convert the temperature measurement into. (1) Celsius. (2) Fahrenheit. (3) Kelvin. (4) Rankine.
/// @param measurement Temperature measurement.
/// @param celsius Converted temperature (deg C).
/// @param fahrenheit Converted temperature (deg F).
/// @param kelvin Converted temperature (K).
/// @param rankine Converted temperature (R).
void TempConvWriteSwitch(int initialUnits, int outputUnits, double measurement, double celsius, double fahrenheit, double kelvin, double rankine);

#endif /* _1aTemperatureConversionWrite_h */
