//
//  StateEntropyChange.c
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

/// MARK: HEADER DECLARATIONS
//Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Custom Header Files
#include "System.h"
#include "B48BC_T5.h"
#include "05cStateEntropyChange.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define R 8.3145

/// MARK: VARIABLE INPUT
void IdealChangeVariable(int method, double *cp, double *P1, double *P2, double *v1, double *v2, double *T1, double *T2)
{
    *cp = inputDouble(0, 0, "heat capacity at constant pressure", "kJ/kmol.K");
    
    if(method == 1 || method == 2)
    {
        *P1 = inputDouble(0, 0, "initial system pressure", "kPa");
        
        *P2 = inputDouble(0, 0, "final system pressure", "kPa");
    }
    if(method == 2 || method == 3)
    {
        *v1 = inputDouble(0, 0, "initial molar volume", "m3/kmol");
        
        *v2 = inputDouble(0, 0, "final molar volume", "m3/kmol");
    }
    if(method == 1 || method == 3)
    {
        *T1 = inputDouble(1, 1, "initial system temperature", "deg C");
        *T1 = (*T1) + 273.15;
        
        *T2 = inputDouble(1, 1, "final system temperature", "deg C");
        *T2 = (*T2) + 273.15;
    }
}

/// MARK: GENERAL CALCULATIONS
double PTIdealCalculation(double cp, double P1, double P2, double T1, double T2)
{
    double ds = 0.0;
    double sto = 0.0;
    
    sto = T2/T1;
    sto = log(sto);
    ds = cp*sto;        // Temperature term calculated
    
    sto = P2/P1;
    sto = log(sto);
    sto = R*sto;        // Pressure term calculated
    
    ds -= sto;
    
    return ds;
}

double PvIdealCalculation(double cp, double P1, double P2, double v1, double v2)
{
    double ds = 0.0;
    double sto = 0.0;
    double sto1 = 0.0;
    
    sto = v2/v1;
    sto = log(sto);
    ds = cp*(sto);      // molar volume term calculated
    
    sto1 = cp - R;      // Inferring cv value
    sto = P2/P1;
    sto = log(sto);
    sto = (sto1)*(sto); // Pressure term calculated
    
    ds += sto;
    
    return ds;
}

double TvIdealCalculation(double cp, double T1, double T2, double v1, double v2)
{
    double ds = 0.0;
    double sto = 0.0;
    double sto1 = 0.0;
    
    sto = v2/v1;
    sto = log(sto);
    ds = R*(sto);      // molar volume term calculated
    
    sto1 = cp - R;      // Inferring cv value
    sto = T2/T1;
    sto = log(sto);
    sto = (sto1)*(sto); // Pressure term calculated
    
    ds += sto;
    
    return ds;
}

/// MARK: DISPLAY AND WRITE
void EntropyChangeDisplay(double cp, double P1, double P2, double v1, double v2, double T1, double T2, double ds)
{
    printf("_Entropy_Change_Results_\n");
    printf("\tInput parameters:\n");
    printf("Initial system pressure:\n");
    printf("P1 =\t%.3f\tkPa\n", P1);
    printf("Final system pressure:\n");
    printf("P2 =\t%.3f\tkPa\n\n", P2);
    
    printf("Initial molar volume:\n");
    printf("v1 =\t%.3f\tm3/kmol\n", v1);
    printf("Final molar volume:\n");
    printf("v2 =\t%.3f\tm3/kmol\n\n", v2);
    
    printf("Initial system temperature:\n");
    printf("T1 =\t%.3f\tdeg C\n", T1 - 273.15);
    printf("Final system temperature:\n");
    printf("T2 =\t%.3f\tdeg C\n\n", T2 - 273.15);
    
    printf("Heat capacity at constant pressure:\n");
    printf("c_P =\t%.3f\tkJ/kmol.K\n\n", cp);
    
    printf("\tOutput parameters:\n");
    printf("ds =\t%.5f\tkJ/kmol.K\n", ds);
}

void EntropyChangeWrite(double cp, double P1, double P2, double v1, double v2, double T1, double T2, double ds)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Polytropic Process Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Entropy Change Estimation");
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
    fprintf(fp, "_Entropy_Change_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial system pressure:\n");
    fprintf(fp, "P1 =\t%.3f\tkPa\n", P1);
    fprintf(fp, "Final system pressure:\n");
    fprintf(fp, "P2 =\t%.3f\tkPa\n\n", P2);
    
    fprintf(fp, "Initial molar volume:\n");
    fprintf(fp, "v1 =\t%.3f\tm3/kmol\n", v1);
    fprintf(fp, "Final molar volume:\n");
    fprintf(fp, "v2 =\t%.3f\tm3/kmol\n\n", v2);
    
    fprintf(fp, "Initial system temperature:\n");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n", T1 - 273.15);
    fprintf(fp, "Final system temperature:\n");
    fprintf(fp, "T2 =\t%.3f\tdeg C\n\n", T2 - 273.15);
    
    fprintf(fp, "Heat capacity at constant pressure:\n");
    fprintf(fp, "c_P =\t%.3f\tkJ/kmol.K\n\n", cp);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "ds =\t%.5f\tkJ/kmol.K\n", ds);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void EntropyChangeWriteSwitch(double cp, double P1, double P2, double v1, double v2, double T1, double T2, double ds)
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
                EntropyChangeWrite(cp, P1, P2, v1, v2, T1, T2, ds);
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
void StateEntropyChange(void)
{
    int whilmain = 0;
    printf("Entropy Change Estimation\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
            //  Subroutine behaviour (Delete me when done)
        char input[maxstrlen];
        
        int control = 0;
        int method = 0;
            //  Subroutine output (Delete me when done)
        double ds = 0.0;    // Entropy change.
        
            //  Subroutine input (Delete me when done)
        double cp = 0.0;    // Heat capacity at constant pressure.
        double P1 = 0.0;    // Initial and final system pressure.
        double P2 = 0.0;
        double v1 = 0.0;    // Initial and final molar volume.
        double v2 = 0.0;
        double T1 = 0.0;    // Initial and final system temperature.
        double T2 = 0.0;
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        control = 1;
        while(control == 1)
        {
            printf("Which equation do you want to use to calculate the entropy change?\n");
            printf("1. Pressure-Temperature.\n");
            printf("2. Pressure-molar volume.\n");
            printf("3. Temperature-molar volume.\n");
            printf("Selection [1 - 3]: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                    method = 1;
                    control = 0;
                    break;
                case '2':
                    method = 2;
                    control = 0;
                    break;
                case '3':
                    method = 3;
                    control = 0;
                    break;
                case '0':
                case 'Q':
                case 'q':
                    whilmain = 0;
                    goto quit;
                    break;
                default:
                    printf("Input not recognised. Please try again.\n");
                    break;
            }
        }
        IdealChangeVariable(method, &cp, &P1, &P2, &v1, &v2, &T1, &T2);
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        // Calculation function(s)
        if(method == 1)
        {
            ds = PTIdealCalculation(cp, P1, P2, T1, T2);
            // Inferring molar volumes.
            v1 = R*T1;
            v1 = (v1)/P1;
            
            v2 = R*T2;
            v2 = (v2)/P2;
        }
        if(method == 2)
        {
            ds = PvIdealCalculation(cp, P1, P2, v1, v2);
            // Inferring system temperatures.
            T1 = P1*v1;
            T1 = (T1)/R;
            
            T2 = P2*v2;
            T2 = (T2)/R;
        }
        if(method == 3)
        {
            ds = TvIdealCalculation(cp, T1, T2, v1, v2);
            // Inferring system pressures.
            P1 = R*T1;
            P1 = (P1)/v1;
            
            P2 = R*T2;
            P2 = (P2)/v2;
        }
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        EntropyChangeDisplay(cp, P1, P2, v1, v2, T1, T2, ds);
        
        //  Writing to File
        EntropyChangeWriteSwitch(cp, P1, P2, v1, v2, T1, T2, ds);
        
        //  Continue function
        whilmain = Continue(whilmain);
    quit: printf("\n");
    }
    fflush(stdout);
}
