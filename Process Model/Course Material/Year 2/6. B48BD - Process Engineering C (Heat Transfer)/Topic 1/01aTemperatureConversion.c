//
//  01aTemperatureConversion.c
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

/// MARK: HEADER DECLARATIONS
//Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Custom Header Files
#include "System.h"
#include "B48BD_T1.h"
#include "01aTemperatureConversion.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void TempConvVariable(int mode, double *temp)
{
    if(mode == 1)
    {
        *temp = inputDouble(1, 1, "the temperature reading", "deg C");
    }
    if(mode == 2)
    {
        *temp = inputDouble(1, 1, "the temperature reading", "deg F");
    }
    if(mode == 3)
    {
        *temp = inputDouble(1, 1, "the temperature reading", "K");
    }
    if(mode == 4)
    {
        *temp = inputDouble(1, 1, "the temperature reading", "R");
    }
}

/// MARK: GENERAL CALCULATIONS
double CelsiusFahrenheitConv(double temp)
{
    temp *= 1.8;
    temp += 32;
    return temp;
}

double FahrenheitCelsiusConv(double temp)
{
    temp -= 32;
    temp /= (1.8);
    return temp;
}

double CelsiusKelvin(double temp)
{
    return temp + 273.15;
}

double KelvinCelsius(double temp)
{
    return temp - 273.15;
}

double FahrenheitRankine(double temp)
{
    return temp + 459.67;
}

double RankineFahrenheit(double temp)
{
    return temp - 459.67;
}

void TempConverter(int initialUnits, int outputUnits, double measurement, double *celsius, double *fahrenheit, double *kelvin, double *rankine)
{
    double sto = 0.0;
    if(initialUnits == outputUnits)
    {
        // No conversion required.
        printf("No conversion performed.\n");
    }else{
        if(initialUnits == 1)
        {
            if(outputUnits == 2 || outputUnits == 5)
            {
                // Celsius to Fahrenheit.
                *fahrenheit = CelsiusFahrenheitConv(measurement);
            }
            if(outputUnits == 3 || outputUnits == 5)
            {
                // Celsius to Kelvin.
                *kelvin = CelsiusKelvin(measurement);
            }
            if(outputUnits == 4 || outputUnits == 5)
            {
                // Celsius to Rankine
                sto = CelsiusFahrenheitConv(measurement);
                *rankine = FahrenheitRankine(sto);
            }
        }
        if(initialUnits == 2)
        {
            if(outputUnits == 1 || outputUnits == 5)
            {
                // Fahrenheit to Celsius.
                *celsius = FahrenheitCelsiusConv(measurement);
            }
            if(outputUnits == 3 || outputUnits == 5)
            {
                // Fahrenheit to Kelvin.
                sto = FahrenheitCelsiusConv(measurement);
                *kelvin = CelsiusKelvin(sto);
            }
            if(outputUnits == 4 || outputUnits == 5)
            {
                // Fahrenheit to Rankine.
                *rankine = FahrenheitRankine(measurement);
            }
        }
        if(initialUnits == 3)
        {
            if(outputUnits == 1 || outputUnits == 5)
            {
                // Kelvin to Celsius.
                *celsius = KelvinCelsius(measurement);
            }
            if(outputUnits == 2 || outputUnits == 5)
            {
                // Kelvin to Fahrenheit.
                sto = KelvinCelsius(measurement);
                *fahrenheit = CelsiusFahrenheitConv(sto);
            }
            if(outputUnits == 4 || outputUnits == 5)
            {
                // Kelvin to Rankine.
                sto = KelvinCelsius(measurement);
                sto = CelsiusFahrenheitConv(sto);
                *rankine = FahrenheitRankine(sto);
            }
        }
        if(initialUnits == 4)
        {
            if(outputUnits == 1 || outputUnits == 5)
            {
                // Rankine to Celsius.
                sto = RankineFahrenheit(measurement);
                *celsius = FahrenheitCelsiusConv(sto);
            }
            if(outputUnits == 2 || outputUnits == 5)
            {
                // Rankine to Fahrenheit.
                *fahrenheit = RankineFahrenheit(measurement);
            }
            if(outputUnits == 3 || outputUnits == 5)
            {
                // Rankine to Kelvin.
                sto = RankineFahrenheit(measurement);
                sto = FahrenheitCelsiusConv(sto);
                *kelvin = CelsiusKelvin(sto);
            }
        }
    }
}

/// MARK: DISPLAY AND WRITE
void TempConvDisplay(int initialUnits, int outputUnits, double measurement, double celsius, double fahrenheit, double kelvin, double rankine)
{
    printf("_Temperature_Conversion_Results_\n");
    if(initialUnits == outputUnits)
    {
        // No conversion required.
        printf("No conversion required.\n");
    }else{
        printf("\tInput parameters:\n");
        printf("Temperature Measurement:\n");
        if(initialUnits == 1)
        {
            // Input in Celsius.
            printf("T =\t%.3f\tdeg C\n", measurement);
            
            printf("\n\tOutput parameters:\n");
            printf("Converted temperature:\n");
            if(outputUnits == 2 || outputUnits == 5)
            {
                // Output in Fahrenheit.
                printf("T =\t%.3f\tdeg F\n", fahrenheit);
            }
            if(outputUnits == 3 || outputUnits == 5)
            {
                // Output in Kelvin.
                printf("T =\t%.3f\tK\n", kelvin);
            }
            if(outputUnits == 4 || outputUnits == 5)
            {
                // Output in Rankine.
                printf("T =\t%.3f\tR\n", rankine);
            }
        }
        if(initialUnits == 2)
        {
            // Input in Fahrenheit.
            printf("T =\t%.3f\tdeg F\n", measurement);
            
            printf("\n\tOutput parameters:\n");
            printf("Converted temperature:\n");
            if(outputUnits == 1 || outputUnits == 5)
            {
                // Output in Celsius.
                printf("T =\t%.3f\tdeg C\n", celsius);
            }
            if(outputUnits == 3 || outputUnits == 5)
            {
                // Output in Kelvin.
                printf("T =\t%.3f\tK\n", kelvin);
            }
            if(outputUnits == 4 || outputUnits == 5)
            {
                // Output in Rankine.
                printf("T =\t%.3f\tR\n", rankine);
            }
            
        }
        if(initialUnits == 3)
        {
            // Input in Kelvin.
            printf("T =\t%.3f\tK\n", measurement);
            
            printf("\n\tOutput parameters:\n");
            printf("Converted temperature:\n");
            if(outputUnits == 1 || outputUnits == 5)
            {
                // Output in Celsius.
                printf("T =\t%.3f\tdeg C\n", celsius);
            }
            if(outputUnits == 2 || outputUnits == 5)
            {
                // Output in Fahrenheit.
                printf("T =\t%.3f\tdeg F\n", fahrenheit);
            }
            if(outputUnits == 4 || outputUnits == 5)
            {
                // Output in Rankine.
                printf("T =\t%.3f\tR\n", rankine);
            }
        }
        if(initialUnits == 4)
        {
            // Input in Rankine.
            printf("T =\t%.3f\tR\n", measurement);
            
            printf("\n\tOutput parameters:\n");
            printf("Converted temperature:\n");
            if(outputUnits == 1 || outputUnits == 5)
            {
                // Output in Celsius.
                printf("T =\t%.3f\tdeg C\n", celsius);
            }
            if(outputUnits == 2 || outputUnits == 5)
            {
                // Output in Fahrenheit.
                printf("T =\t%.3f\tdeg F\n", fahrenheit);
            }
            if(outputUnits == 3 || outputUnits == 5)
            {
                // Output in Kelvin.
                printf("T =\t%.3f\tK\n", kelvin);
            }
        }
    }
}

void TempConvWrite(int initialUnits, int outputUnits, double measurement, double celsius, double fahrenheit, double kelvin, double rankine)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Temperature Conversion Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Temperature Conversion Results");
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    /*
    //driveloc is not suitable when determining the file path for mac
    *filepath = (char)malloc(sizeof *filepath);
    
    //printf("Save file to: /Users/user/Documents/ ");
    strcpy(filepath, "/Users/user/Documents/ModelFiles/");
    printf("File path: \"%s\"\n", filepath);
    
    strcat(filepath, filename);
    void free(void *filename); // Removing 'filename' from the heap
    
    printf("File name: \"%s\"\n", filename);
    printf("Full file path: \"%s\"\n\n", filepath);
    
    //Testing if directory is not present
    if(fopen(filepath, "r") == NULL){
        printf("Directory does not exist, writing data to \"Documents\" folder instead.\n");
        strcpy(filepath, "/Users/user/Documents/");
        printf("File is now being outputted to: %s\n", filepath);
    }
    */
    printf("Note that write sequence may be disabled by zsh\n");
    
    printf("Beginning file write...\n");
    
    //Open file
    fp = fopen(filename, "w+");
    
    //Write to file
    fprintf(fp, "_Temperature_Conversion_Results_\n");
    if(initialUnits == outputUnits)
    {
        // No conversion required.
        fprintf(fp, "No conversion required.\n");
    }else{
        fprintf(fp, "\tInput parameters:\n");
        fprintf(fp, "Temperature Measurement:\n");
        if(initialUnits == 1)
        {
            // Input in Celsius.
            fprintf(fp, "T =\t%.3f\tdeg C\n", measurement);
            
            fprintf(fp, "\n\tOutput parameters:\n");
            fprintf(fp, "Converted temperature:\n");
            if(outputUnits == 2 || outputUnits == 5)
            {
                // Output in Fahrenheit.
                fprintf(fp, "T =\t%.3f\tdeg F\n", fahrenheit);
            }
            if(outputUnits == 3 || outputUnits == 5)
            {
                // Output in Kelvin.
                fprintf(fp, "T =\t%.3f\tK\n", kelvin);
            }
            if(outputUnits == 4 || outputUnits == 5)
            {
                // Output in Rankine.
                fprintf(fp, "T =\t%.3f\tR\n", rankine);
            }
        }
        if(initialUnits == 2)
        {
            // Input in Fahrenheit.
            fprintf(fp, "T =\t%.3f\tdeg F\n", measurement);
            
            fprintf(fp, "\n\tOutput parameters:\n");
            fprintf(fp, "Converted temperature:\n");
            if(outputUnits == 1 || outputUnits == 5)
            {
                // Output in Celsius.
                fprintf(fp, "T =\t%.3f\tdeg C\n", celsius);
            }
            if(outputUnits == 3 || outputUnits == 5)
            {
                // Output in Kelvin.
                fprintf(fp, "T =\t%.3f\tK\n", kelvin);
            }
            if(outputUnits == 4 || outputUnits == 5)
            {
                // Output in Rankine.
                fprintf(fp, "T =\t%.3f\tR\n", rankine);
            }
            
        }
        if(initialUnits == 3)
        {
            // Input in Kelvin.
            fprintf(fp, "T =\t%.3f\tK\n", measurement);
            
            fprintf(fp, "\n\tOutput parameters:\n");
            fprintf(fp, "Converted temperature:\n");
            if(outputUnits == 1 || outputUnits == 5)
            {
                // Output in Celsius.
                fprintf(fp, "T =\t%.3f\tdeg C\n", celsius);
            }
            if(outputUnits == 2 || outputUnits == 5)
            {
                // Output in Fahrenheit.
                fprintf(fp, "T =\t%.3f\tdeg F\n", fahrenheit);
            }
            if(outputUnits == 4 || outputUnits == 5)
            {
                // Output in Rankine.
                fprintf(fp, "T =\t%.3f\tR\n", rankine);
            }
        }
        if(initialUnits == 4)
        {
            // Input in Rankine.
            fprintf(fp, "T =\t%.3f\tR\n", measurement);
            
            fprintf(fp, "\n\tOutput parameters:\n");
            fprintf(fp, "Converted temperature:\n");
            if(outputUnits == 1 || outputUnits == 5)
            {
                // Output in Celsius.
                fprintf(fp, "T =\t%.3f\tdeg C\n", celsius);
            }
            if(outputUnits == 2 || outputUnits == 5)
            {
                // Output in Fahrenheit.
                fprintf(fp, "T =\t%.3f\tdeg F\n", fahrenheit);
            }
            if(outputUnits == 3 || outputUnits == 5)
            {
                // Output in Kelvin.
                fprintf(fp, "T =\t%.3f\tK\n", kelvin);
            }
        }
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void TempConvWriteSwitch(int initialUnits, int outputUnits, double measurement, double celsius, double fahrenheit, double kelvin, double rankine)
{
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        char input[maxstrlen];
        
        printf("Do you want to save results to file? ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                TempConvWrite(initialUnits, outputUnits, measurement, celsius, fahrenheit, kelvin, rankine);
                control = 0;
                break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                control = 0;
                break;
            default:
                printf("Input not recognised\n");
                break;
        }
    }
}

/// MARK: PSEUDO-MAIN FUNCTION
void TemperatureConversion(void)
{
    int whilmain = 0;
    printf("Temperature Conversion\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        char input[maxstrlen];
        int control = 0;
        int inUnits = 0;
        int outUnits = 0;
        
        double celsius = 0.0;
        double fahrenheit = 0.0;
        double kelvin = 0.0;
        double rankine = 0.0;
        
        double initial = 0.0;
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        control = 1;
        while(control == 1)
        {
            printf("What units is the measurement you want to convert in?\n");
            printf("1. Celsius.\n");
            printf("2. Fahrenheit.\n");
            printf("3. Kelvin.\n");
            printf("4. Rankine.\n");
            printf("Selection [1 - 4]: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                    inUnits = 1;
                    control = 0;
                    break;
                case '2':
                    inUnits = 2;
                    control = 0;
                    break;
                case '3':
                    inUnits = 3;
                    control = 0;
                    break;
                case '4':
                    inUnits = 4;
                    control = 0;
                    break;
                case '0':
                case 'Q':
                case 'q':
                    whilmain = 0;
                    goto end;
                    break;
                default:
                    printf("Input not recognised. Please enter an integer between 1 and 4.\n");
                    break;
            }
        }
        TempConvVariable(inUnits, &initial);
        
        control = 1;
        while(control == 1)
        {
            printf("What units do you want to convert to?\n");
            printf("1. Celsius.\n");
            printf("2. Fahrenheit.\n");
            printf("3. Kelvin.\n");
            printf("4. Rankine.\n");
            printf("5. All possible temperature conversions.\n");
            printf("Selection [1 - 5]: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                    outUnits = 1;
                    control = 0;
                    break;
                case '2':
                    outUnits = 2;
                    control = 0;
                    break;
                case '3':
                    outUnits = 3;
                    control = 0;
                    break;
                case '4':
                    outUnits = 4;
                    control = 0;
                    break;
                case '5':
                    outUnits = 5;
                    control = 0;
                    break;
                case '0':
                case 'Q':
                case 'q':
                    whilmain = 0;
                    goto end;
                    break;
                default:
                    printf("Input not recognised. Please enter an integer between 1 and 4.\n");
                    break;
            }
        }
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        // Calculation function(s)
        TempConverter(inUnits, outUnits, initial, &celsius, &fahrenheit, &kelvin, &rankine);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        TempConvDisplay(inUnits, outUnits, initial, celsius, fahrenheit, kelvin, rankine);
        
        //  Writing to File
        TempConvWriteSwitch(inUnits, outUnits, initial, celsius, fahrenheit, kelvin, rankine);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
end:
    fflush(stdout);
}
