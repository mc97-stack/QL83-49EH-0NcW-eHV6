//
//  05bEngineEntropyBalance.c
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
#include "04dClausiusInequality.h"
#include "05aEntropyBalance.h"
#include "05bEngineEntropyBalance.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void CycleVariable(int mode, double *work)
{
    if(mode == 1){
        // If the cycle is producing work, the cycle will be losing work to the surroundings. Therefore net work can be negative.
        *work = inputDouble(1, 1, "net work", "kJ/kg");
    }
    if(mode == 2){
        // A heat pump, by definition, can only require work. Therefore a negative value can not be accepted.
        *work = inputDouble(1, 0, "work required", "kJ/kg");
    }
}

void HotResVariable(int mode, double *qHot, double *THot)
{
    *qHot = inputDouble(1, 0, "heat supplied to cycle from hot reservoir", "kJ/kg");
    
    *THot = inputDouble(1, 1, "hot reservoir temperature", "deg C");
    *THot = (*THot) + 273.15;
}

void ColdResVariable(int mode, double *qCold, double *TCold)
{
    *qCold = inputDouble(1, 0, "heat supplied to cycle from cold reservoir", "kJ/kg");
    
    *TCold = inputDouble(1, 1, "cold reservoir temperature", "deg C");
    *TCold = (*TCold) + 273.15;
}

void SurrVariable(double *TSurr)
{
    *TSurr = inputDouble(1, 1, "temperature of surroundings", "deg C");
    *TSurr = (*TSurr) + 273.15;
}

/// MARK: GENERAL CALCULATIONS
double HeatEngineEntropyBalance(int HotCount, T5Reservoir hot, double work, double TSurr, double *dSHot, double *dSCold)
{
    double HotHeat = 0.0;
    
    for(int i = 0; i < HotCount; ++i){
        // Calculating the entropy change for the hot reservoir(s)
        hot.s[i] = EntropyCalc(-1*(hot.q[i]), hot.T[i]); // Calculating dS_{Surr, H}
        *dSHot += hot.s[i];                 // Calculating total entropy change in the hot reservoir(s)
        
        HotHeat += hot.q[i];               // Finding q_H
    }
    *dSCold = HotHeat - work;                // Calculating q_C
    *dSCold = EntropyCalc(*dSCold, TSurr);    // Calculating dS_{Surr, C}
    
    return EntropyBalance(0, (*dSHot + *dSCold));
}

double HeatPumpEntropyBalance(int ColdCount, T5Reservoir cold, double work, double TSurr, double *dSHot, double *dSCold)
{
    double ColdHeat = 0.0;
    
    for(int i = 0; i < ColdCount; ++i){
        // Calculating the entropy change for the cold reservoir(s)
        cold.s[i] = EntropyCalc(-1*(cold.q[i]), cold.T[i]);   // Calculating dS_{Surr, C}
        *dSCold += cold.s[i];               // Calculating total entropy change in the cold reservoir(s)
        
        ColdHeat += cold.q[i];             // Finding q_C
    }
    *dSHot = ColdHeat + work;                // Calculating q_H
    *dSHot = EntropyCalc(*dSHot, TSurr);      // Calculating dS_{Surr, H}
    
    return EntropyBalance(0, (*dSHot + *dSCold));
}

/// MARK: DISPLAY AND WRITE
void EngineEntropyDisplay(int mode, double work, double TSurr, T5Reservoir hot, T5Reservoir cold, int HotCount, int ColdCount, double dSHot, double dSCold, double dSTotal)
{
    if(mode == 1){
        printf("_Heat_Engine_Entropy_Balance_Results_\n");
    }
    if(mode == 2){
        printf("_Heat_Pump_Entropy_Balance_Results_\n");
    }
    printf("\tInput parameters:\n");
    if(mode == 1){
        printf("Net work:\n");
        printf("work =\t%.3f\tkJ/kg\n", work);
    }
    if(mode == 2){
        printf("Work input:\n");
        printf("work =\t%.3f\tkJ/kg\n", work);
    }
    printf("Temperature of surroundings:\n");
    printf("T_{Surr} =\t%.3f\tdeg C\n\n", TSurr - 273.15);
    
    printf("\tIntermediate parameters:\n");
    if(mode == 1){
        printf("q_H (kJ/kg)");
    }
    if(mode == 2){
        printf("q_C (kJ/kg)");
    }
    printf("\tT (deg C)\t\t ds (kJ/(kg.K))\n");
    if(mode == 1){
        for(int i = 0; i < HotCount; ++i){
            printf("%.3f\t", hot.q[i]);
            printf("%.2f\t\t", hot.T[i]-273.15);
            printf("%.3f\n", hot.s[i]);
        }
    }
    if(mode == 2){
        for(int i = 0; i < ColdCount; ++i){
            printf("%.3f\t", cold.q[i]);
            printf("%.2f\t\t", cold.T[i]-273.15);
            printf("%.3f\n", cold.s[i]);
        }
    }
    
    printf("\n");
    printf("\tOutput parameters:\n");
    printf("Entropy change of hot reservoir(s):\n");
    printf("dS_{Hot} =\t%.5f\tkJ/kg\n", dSHot);
    printf("Entropy change of cold reservoir(s):\n");
    printf("dS_{Cold} =\t%.5f\tkJ/kg\n", dSCold);
    printf("Entropy generated:\n");
    printf("dS_{Total} =\t%.5f\tkJ/kg\n", dSTotal);
    
    if(dSTotal > 0){
        printf("This process is irreversible.\n");
    }else{
        if(dSTotal == 0){
            printf("This process is reversible.\n");
        }else{
            printf("This process is impossible.\n");
        }
    }
}

void EngineEntropyWrite(int mode, double work, double TSurr, T5Reservoir hot, T5Reservoir cold, int HotCount, int ColdCount, double dSHot, double dSCold, double dSTotal)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Heat Engine Entropy Balance Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    if(mode == 1){
        strcat(filename, " Heat Engine Entropy Balance Results");
    }
    if(mode == 2){
        strcat(filename, " Heat Pump Entropy Balance Results");
    }
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
    if(mode == 1){
        fprintf(fp, "_Heat_Engine_Entropy_Balance_Results_\n");
    }
    if(mode == 2){
        fprintf(fp, "_Heat_Pump_Entropy_Balance_Results_\n");
    }
    fprintf(fp, "\tInput parameters:\n");
    if(mode == 1){
        fprintf(fp, "Net work:\n");
        fprintf(fp, "work =\t%.3f\tkJ/kg\n", work);
    }
    if(mode == 2){
        fprintf(fp, "Work input:\n");
        fprintf(fp, "work =\t%.3f\tkJ/kg\n", work);
    }
    fprintf(fp, "Temperature of surroundings:\n");
    fprintf(fp, "T_{Surr} =\t%.3f\tdeg C\n\n", TSurr - 273.15);
    
    fprintf(fp, "\tIntermediate parameters:\n");
    if(mode == 1){
        fprintf(fp, "q_H (kJ/kg)");
    }
    if(mode == 2){
        fprintf(fp, "q_C (kJ/kg)");
    }
    fprintf(fp, "\tT (deg C)\t\t ds (kJ/(kg.K))\n");
    if(mode == 1){
        for(int i = 0; i < HotCount; ++i){
            fprintf(fp, "%.3f\t", hot.q[i]);
            fprintf(fp, "%.2f\t\t", hot.T[i]-273.15);
            fprintf(fp, "%.3f\n", hot.s[i]);
        }
    }
    if(mode == 2){
        for(int i = 0; i < ColdCount; ++i){
            fprintf(fp, "%.3f\t", cold.q[i]);
            fprintf(fp, "%.2f\t\t", cold.T[i]-273.15);
            fprintf(fp, "%.3f\n", cold.s[i]);
        }
    }
    
    fprintf(fp, "\n");
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Entropy change of hot reservoir(s):\n");
    fprintf(fp, "dS_{Hot} =\t%.5f\tkJ/kg\n", dSHot);
    fprintf(fp, "Entropy change of cold reservoir(s):\n");
    fprintf(fp, "dS_{Cold} =\t%.5f\tkJ/kg\n", dSCold);
    fprintf(fp, "Entropy generated:\n");
    fprintf(fp, "dS_{Total} =\t%.5f\tkJ/kg\n", dSTotal);
    
    if(dSTotal > 0){
        fprintf(fp, "This process is irreversible.\n");
    }else{
        if(dSTotal == 0){
            fprintf(fp, "This process is reversible.\n");
        }else{
            fprintf(fp, "This process is impossible.\n");
        }
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void EngineEntropyWriteSwitch(int mode, double work, double TSurr, T5Reservoir hot, T5Reservoir cold, int HotCount, int ColdCount, double dSHot, double dSCold, double dSTotal)
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
                EngineEntropyWrite(mode, work, TSurr, hot, cold, HotCount, ColdCount, dSHot, dSCold, dSTotal);
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
void EngineEntropyBalance(void)
{
    int whilmain = 0;
    printf("Heat Engine/Pump Thermodynamic Analysis\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        char input[maxstrlen];
        int control = 0;
        int mode = 0;
        int HotCount = 0;
        int ColdCount = 0;
        
        double dSHot = 0.0;
        double dSCold = 0.0;
        double dSTotal = 0.0;
        
        double work = 0.0;
        double TSurr = 0.0;
        T5Reservoir *hot = calloc(1, sizeof(T5Reservoir));
        T5Reservoir *cold = calloc(1, sizeof(T5Reservoir));
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        control = 1;
        while(control == 1)
        {
            printf("What type of heat engine are you analysing?\n");
            printf("1. Heat engine.\n");
            printf("2. Heat pump/Refrigerator.\n\n");
            
            printf("Selection [1 - 2]: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                    mode = 1;
                    control = 0;
                    break;
                case '2':
                    mode = 2;
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
        
        control = 1;
        while(control == 1)
        {
            if(mode == 1){
                printf("How many hot reservoirs are present? ");
                HotCount = atoi(fgets(input, sizeof(input), stdin));
                if(HotCount > 32){
                    printf("This subroutine can only handle a maximum of 32 hot reservoirs. Please enter an integer value that is less than 33.\n");
                }else{
                    if(HotCount == 0){
                        printf("Invalid integer. Please enter a non-zero integer that is also less than 33.\n");
                    }else{
                        control = 0;
                    }
                }
            }
            if(mode == 2){
                printf("How many cold reservoirs are present? ");
                ColdCount = atoi(fgets(input, sizeof(input), stdin));
                if(ColdCount > 32){
                    printf("This subroutine can only handle a maximum of 32 cold reservoirs. Please enter an integer value that is less than 33.\n");
                }else{
                    if(ColdCount == 0){
                        printf("Invalid integer. Please enter a non-zero integer that is also less than 33.\n");
                    }else{
                        control = 0;
                    }
                }
            }
        }
        CycleVariable(mode, &work);
        if(mode == 1)
        {
            for(int i = 0; i < HotCount; ++i){
                HotResVariable(mode, &hot->q[i], &hot->T[i]);
            }
        }
        if(mode == 2)
        {
            for(int i = 0; i < ColdCount; ++i){
                ColdResVariable(mode, &cold->q[i], &cold->T[i]);
            }
        }
        SurrVariable(&TSurr);
        printf("\n");
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        // Calculation function(s)
        if(mode == 1)
        {
            dSTotal = HeatEngineEntropyBalance(HotCount, *hot, work, TSurr, &dSHot, &dSCold);
        }
        if(mode == 2)
        {
            dSTotal = HeatPumpEntropyBalance(ColdCount, *cold, work, TSurr, &dSHot, &dSCold);
        }
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        EngineEntropyDisplay(mode, work, TSurr, *hot, *cold, HotCount, ColdCount, dSHot, dSCold, dSTotal);
        
        //  Writing to File
        EngineEntropyWriteSwitch(mode, work, TSurr, *hot, *cold, HotCount, ColdCount, dSHot, dSCold, dSTotal);
        
        //  Continue function
        whilmain = Continue(whilmain);
        
    quit:
        free(hot);
        free(cold);
    }
    fflush(stdout);
}
