//
//  01dRadiation.c
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
#include "01dRadiation.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void ThermRadiationVariable(double *A, double *Ts, double *Tf)
{
    *A = inputDouble(0, 0, "heat transfer area", "m2");
    
    *Ts = inputDouble(1, 1, "temperature of heat transfer surface", "deg C");
    *Ts = CelsiusKelvin(*Ts);
    
    *Tf = inputDouble(1, 1, "temperature of surrounding fluid", "deg C");
    *Tf = CelsiusKelvin(*Tf);
}

double StefanBoltzmannConstant()
{
    double sto = 0.0;
    
    sto = pow(10, -8);
    sto = 5.6703*(sto);
    
    return sto;
}

/// MARK: GENERAL CALCULATIONS
double ThermRadiationCalculation(double A, double Ts, double Tf)
{
    double Q = 0.0;
    double sto = 0.0;
    
    sto = pow(Ts, 4);
    Q = pow(Tf, 4);
    Q = (sto) - (Q);
    
    sto = StefanBoltzmannConstant();
    Q *= A;
    Q *= (sto);
    
    return Q;
}

/// MARK: DISPLAY AND WRITE
void ThermRadiationDisplay(double A, double Ts, double Tf, double Q)
{
    printf("_Thermal_Radiation_Results_\n");
    printf("\tInput parameters:\n");
    printf("Heat transfer area:\n");
    printf("A =\t%.3f\tm2\n\n", A);
    
    printf("Temperature of the heat transfer surface:\n");
    printf("Ts =\t%.3f\tdeg C\n", Ts - 273.15);
    printf("Temperature of the surrounding fluid:\n");
    printf("Tf =\t%.3f\tdeg C\n\n", Tf - 273.15);
    
    printf("\tIntermediate parameters:\n");
    printf("Stefan-Boltzmann constant:\n");
    printf("\\sigma =\t5.6703 x 10^{-8}\tW/m2.K4\n\n");
    
    printf("\tOutput parameters:\n");
    printf("Rate of heat transfer:\n");
    printf("Q =\t%.3f\tW\n", Q);
}

void ThermRadiationWrite(double A, double Ts, double Tf, double Q)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Thermal Radiation Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Thermal Radiation Results");
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
    fprintf(fp, "_Thermal_Radiation_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Heat transfer area:\n");
    fprintf(fp, "A =\t%.3f\tm2\n\n", A);
    
    fprintf(fp, "Temperature of the heat transfer surface:\n");
    fprintf(fp, "Ts =\t%.3f\tdeg C\n", Ts - 273.15);
    fprintf(fp, "Temperature of the surrounding fluid:\n");
    fprintf(fp, "Tf =\t%.3f\tdeg C\n\n", Tf - 273.15);
    
    fprintf(fp, "\tIntermediate parameters:\n");
    fprintf(fp, "Stefan-Boltzmann constant:\n");
    fprintf(fp, "\\sigma =\t5.6703 x 10^{-8}\tW/m2.K4\n\n");
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Rate of heat transfer:\n");
    fprintf(fp, "Q =\t%.3f\tW\n", Q);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void ThermRadiationWriteSwitch(double A, double Ts, double Tf, double Q)
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
                ThermRadiationWrite(A, Ts, Tf, Q);
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
void Radiation(void)
{
    int whilmain = 0;
    printf("Thermal Radiation\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        double Q = 0.0;     // Rate of heat transfer.
        
        double A = 0.0;     // Heat transfer area.
        double Ts = 0.0;    // Temperature of heat transfer surface.
        double Tf = 0.0;    // Temperature of surrounding fluid.
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        ThermRadiationVariable(&A, &Ts, &Tf);
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        // Calculation function(s)
        Q = ThermRadiationCalculation(A, Ts, Tf);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        ThermRadiationDisplay(A, Ts, Tf, Q);
        
        //  Writing to File
        ThermRadiationWriteSwitch(A, Ts, Tf, Q);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
