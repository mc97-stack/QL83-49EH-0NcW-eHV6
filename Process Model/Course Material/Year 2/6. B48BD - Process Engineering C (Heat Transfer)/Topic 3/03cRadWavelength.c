//
//  03cRadWavelength.c
//  Process Model
//
//  Created by Matthew Cheung on 23/12/2020.
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
#include "B48BD_T3.h"
#include "01aTemperatureConversion.h"
#include "03cRadWavelength.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: GENERAL CALCULATIONS
double EmissivePowerCalculation(double wavelength, double T)
{
    double result = 0.0;
    double sto1 = 0.0;
    double sto2 = 0.0;
    
    sto1 = pow(10, -2);
    sto1 *= 1.439;
    sto2 = wavelength*T;
    sto1 /= sto2;
    sto1 = exp(sto1);
    sto1 -= 1;
    sto2 = pow(wavelength, 5);
    sto1 *= sto2;       // Denominator calculated and stored in sto1
    
    sto2 = pow(10, -16);
    sto2 *= 3.742;      // Numerator calculated and stored in sto2
    
    result = sto2/sto1;
    
    return result;
}

/// MARK: ARRAY FUNCTION
EmissivePower EmissivePwrArray(EmissivePower result, int numIsotherms)
{
    double interval = 0.0;
    double sto = 0.0;
    
    // Calculating interval between datapoints
    interval = pow(10, -7);
    interval *= 1;
    
    sto = pow(10, -5);
    sto *= 10;
    
    interval = sto - interval;
    interval /= 4999;
    
    // Initialising valid wavelengths
    for(int i = 0; i < 5000; ++i)
    {
        if(i == 0)
        {
            result.wavelength[i] = pow(10, -7);
        }else{
            result.wavelength[i] = result.wavelength[i-1]+interval;
        }
    }
    
    for(int i = 0; i < 5000; ++i)
    {
        for(int j = 0; j < numIsotherms; ++j)
        {
            result.EmPower[i][j] = EmissivePowerCalculation(result.wavelength[i], result.T[j]);
        }
    }
    
    return result;
}

/// MARK: DISPLAY AND WRITE
void EmissivePwrDisplay(EmissivePower data, int numIsotherms)
{
    printf("_Monochromatic_Emissive_Power_Results_\n");
    printf("T =\t");
    for(int i = 0; i < numIsotherms; ++i)
    {
        printf("%.3f\t", data.T[i]);
    }
    printf("\n");
    
    printf("\\lambda (m)\tE_{\\lambda} (W/m3)\n");
    for(int i = 0; i < 5000; ++i)
    {
        printf("%.5E\t", data.wavelength[i]);
        for(int j = 0; j < numIsotherms; ++j)
        {
            printf("%.5E\t", data.EmPower[i][j]);
        }
        printf("\n");
    }
}

void EmissivePwrWrite(EmissivePower data, int numIsotherms)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Monochromatic Emissive Power Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Monochromatic Emissive Power Results");
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
    fprintf(fp, "_Monochromatic_Emissive_Power_Results_\n");
    fprintf(fp, "T =\t");
    for(int i = 0; i < numIsotherms; ++i)
    {
        fprintf(fp, "%.3f\t", data.T[i]);
    }
    fprintf(fp, "\n");
    
    fprintf(fp, "\\lambda (m)\tE_{\\lambda} (W/m3)\n");
    for(int i = 0; i < 5000; ++i)
    {
        fprintf(fp, "%.5E\t", data.wavelength[i]);
        for(int j = 0; j < numIsotherms; ++j)
        {
            fprintf(fp, "%.5E\t", data.EmPower[i][j]);
        }
        fprintf(fp, "\n");
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void EmissivePwSwitch(int mode, EmissivePower results, int numIsotherms)
{
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        char input[maxstrlen];
        
        if(mode == 1)
        {
            printf("Do you want to view the results? ");
        }
        if(mode == 2)
        {
            printf("Do you want to save results to file? ");
        }
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                if(mode == 1)
                {
                    EmissivePwrDisplay(results, numIsotherms);
                }
                if(mode == 2)
                {
                    EmissivePwrWrite(results, numIsotherms);
                }
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
void RadWavelength(void)
{
    int whilmain = 0;
    printf("Monochromatic Emissive Power\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
            //  Subroutine behaviour (Delete me when done)
        char input[maxstrlen];
        int control = 0;
        int numIsotherms = 0;
            //  Subroutine output (Delete me when done)
        EmissivePower *results = calloc(1, sizeof(EmissivePower));
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        for(int i = 0; i < 25; ++i)
        {
            printf("Temperature of isotherm %i (deg C): ", i + 1);
            results->T[i] = CelsiusKelvin(atof(fgets(input, sizeof(input), stdin)));
            ++numIsotherms;
            control = 1;
            while(control == 1)
            {
                printf("Do you want to create another isotherm? [Y/N] ");
                fgets(input, sizeof(input), stdin);
                switch(input[0])
                {
                    case '1':
                    case 'T':
                    case 'Y':
                    case 't':
                    case 'y':
                        control = 0;
                        break;
                    case '0':
                    case 'F':
                    case 'N':
                    case 'f':
                    case 'n':
                        goto doneEntry;
                        break;
                    default:
                        printf("Input not recognised. Please try again.\n");
                        break;
                }
            }
        }
    doneEntry:
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        // Calculation function(s)
        *results = EmissivePwrArray(*results, numIsotherms);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        EmissivePwSwitch(1, *results, numIsotherms);
        
        //  Writing to File
        EmissivePwSwitch(2, *results, numIsotherms);
        
        //  Continue function
        whilmain = Continue(whilmain);
        free(results);
    }
    fflush(stdout);
}
