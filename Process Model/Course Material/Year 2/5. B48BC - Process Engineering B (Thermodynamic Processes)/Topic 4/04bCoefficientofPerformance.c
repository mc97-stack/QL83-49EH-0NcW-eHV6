//
//  04bCoefficientofPerformance.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 31/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
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
#include "B48BC_T4.h"
#include "04bCoefficientofPerformance.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void CoPVariable(int method, double *wnet, double *qhot, double *qcold, double *THot, double *TCold)
{
    if(method == 1)
    {
        *qcold = inputDouble(0, 1, "specific heat received from cold reservoir", "kJ/kg");
    }
    if(method == 2)
    {
        *qhot = inputDouble(0, 0, "specific heat supplied to hot reservoir", "kJ/kg");
    }
    if(method == 1 || method == 2)
    {
        *wnet = inputDouble(1, 1, "specific net work to/from thermodynamic cycle", "kJ/kg");
        
        *THot = inputDouble(0, 0, "temperature of hot reservoir", "K");
        *TCold = inputDouble(0, 0, "temperature of cold reservoir", "K");
    }
}

/// MARK: GENERAL CALCULATIONS
double CoPFridge(double qcold, double wnet)
{
    double CoP = 0.0;
    
    qcold = fabs(qcold);
    wnet = fabs(wnet);
    
    CoP = qcold/wnet;
    
    return CoP;
}

double CoPHeatPump(double qhot, double wnet)
{
    double CoP = 0.0;
    
    qhot = fabs(qhot);
    wnet = fabs(wnet);
    
    CoP = qhot/wnet;
    
    return CoP;
}

double CoPRevFridge(double TCold, double THot)
{
    double CoP = 0.0;
    
    CoP = THot - TCold;
    CoP = TCold/(CoP);
    
    return CoP;
}

double CoPRevHeatPump(double TCold, double THot)
{
    double CoP = 0.0;
    
    CoP = THot - TCold;
    CoP = THot/(CoP);
    
    return CoP;
}

double etaFridge(double CoP)
{
    double eta = 0.0;
    
    eta = CoP + 1;
    eta = 1/(eta);
    
    return eta;
}

double etaHeatPump(double CoP)
{
    double eta = 0.0;
    
    eta = 1/(CoP);
    
    return eta;
}

/// MARK: DISPLAY AND WRITE
void CoPDisplay(int method, double wnet, double qhot, double qcold, double THot, double TCold, double CoP, double CoPRev, double eta, double etac)
{
    printf("_Thermal_Efficiency_Results_\n");
    printf("\tInput parameters:\n");
    if(method == 1)
    {
        //Fridge selected
        printf("Specific heat received from cold reservoir:\n");
        printf("q_cold =\t%.3f\tkJ/kg\n", qcold);
    }
    if(method == 2)
    {
        //Heat pump selected
        printf("Specific heat supplied to hot reservoir:\n");
        printf("q_hot =\t%.3f\tkJ/kg\n", qhot);
    }
    
    printf("Specific net work:\n");
    printf("w_net =\t%.3f\tkJ/kg\n\n", wnet);
    
    printf("Hot reservoir temperature:\n");
    printf("T_Hot =\t%.3f\tkJ/kg\n", THot);
    printf("Cold reservoir temperature:\n");
    printf("T_cold =\t%.3f\tkJ/kg\n", TCold);
    
    printf("\tOutput parameters:\n");
    if(method == 1)
    {
        printf("Coefficient of Performance:\n");
        printf("CoP_fridge =\t%.3f\t[ ]\n", CoP);
        printf("Thermal efficiency:\n");
        printf("eta_fridge =\t%.3f\t%%\n\n", eta);
        
        printf("Reversible Coefficient of Performance:\n");
        printf("CoP_{fridge}^{Rev} =\t%.3f\t[ ]\n", CoPRev);
    }
    if(method == 2)
    {
        printf("Coefficient of Performance:\n");
        printf("CoP_{heat pump} =\t%.3f\t[ ]\n", CoP);
        printf("Thermal efficiency:\n");
        printf("eta_{heat pump} =\t%.3f\t%%\n\n", eta);
        
        printf("Reversible Coefficient of Performance:\n");
        printf("CoP_{heat pump}^{Rev} =\t%.3f\t[ ]\n", CoPRev);
    }
    printf("Reversible thermal efficiency:\n");
    printf("eta_Carnot =\t%.3f\t%%\n\n", etac);
    
    if(CoP == CoPRev)
    {
        printf("This process is reversible.\n");
    }else{
        if(CoP < CoPRev)
        {
            printf("This process is irreversible.\n");
        }else{
            printf("This process violates the second law.\n");
        }
    }
    fflush(stdout);
}

void CoPWrite(int method, double wnet, double qhot, double qcold, double THot, double TCold, double CoP, double CoPRev, double eta, double etac)
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
    
    strcat(filename, " [Program Name] Results");
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    /*
    //driveloc is not suitable when determining the file path for mac

    //printf("Save file to: /Users/user/Documents/ ");
    strcpy(filepath, "/Users/user/Documents/ModelFiles/");

    strcat(filepath, filename);

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
    
    //  Open file
    fp = fopen(filename, "w+");
    
    //  Write to file
    fprintf(fp, "_Thermal_Efficiency_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    if(method == 1)
    {
        //Fridge selected
        fprintf(fp, "Specific heat received from cold reservoir:\n");
        fprintf(fp, "q_cold =\t%.3f\tkJ/kg\n", qcold);
    }
    if(method == 2)
    {
        //Heat pump selected
        fprintf(fp, "Specific heat supplied to hot reservoir:\n");
        fprintf(fp, "q_hot =\t%.3f\tkJ/kg\n", qhot);
    }
    
    fprintf(fp, "Specific net work:\n");
    fprintf(fp, "w_net =\t%.3f\tkJ/kg\n\n", wnet);
    
    fprintf(fp, "Hot reservoir temperature:\n");
    fprintf(fp, "T_Hot =\t%.3f\tkJ/kg\n", THot);
    fprintf(fp, "Cold reservoir temperature:\n");
    fprintf(fp, "T_cold =\t%.3f\tkJ/kg\n", TCold);
    
    fprintf(fp, "\tOutput parameters:\n");
    if(method == 1)
    {
        fprintf(fp, "Coefficient of Performance:\n");
        fprintf(fp, "CoP_fridge =\t%.3f\t[ ]\n", CoP);
        fprintf(fp, "Thermal efficiency:\n");
        fprintf(fp, "eta_fridge =\t%.3f\t%%\n\n", eta);
        
        fprintf(fp, "Reversible Coefficient of Performance:\n");
        fprintf(fp, "CoP_{fridge}^{Rev} =\t%.3f\t[ ]\n", CoPRev);
    }
    if(method == 2)
    {
        fprintf(fp, "Coefficient of Performance:\n");
        fprintf(fp, "CoP_{heat pump} =\t%.3f\t[ ]\n", CoP);
        fprintf(fp, "Thermal efficiency:\n");
        fprintf(fp, "eta_{heat pump} =\t%.3f\t%%\n\n", eta);
        
        fprintf(fp, "Reversible Coefficient of Performance:\n");
        fprintf(fp, "CoP_{heat pump}^{Rev} =\t%.3f\t[ ]\n", CoPRev);
    }
    fprintf(fp, "Reversible thermal efficiency:\n");
    fprintf(fp, "eta_Carnot =\t%.3f\t%%\n\n", etac);
    
    if(CoP == CoPRev)
    {
        fprintf(fp, "This process is reversible.\n");
    }else{
        if(CoP < CoPRev)
        {
            fprintf(fp, "This process is irreversible.\n");
        }else{
            fprintf(fp, "This process violates the second law.\n");
        }
    }
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void CoPWriteSwitch(int method, double wnet, double qhot, double qcold, double THot, double TCold, double CoP, double CoPRev, double eta, double etac)
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
                CoPWrite(method, wnet, qhot, qcold, THot, TCold, CoP, CoPRev, eta, etac);
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
void CoefficientofPerformance(void)
{
    //  Pseudo-main function.
    int whilmain = 0;
    printf("Coefficient of Performance Calculation\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        char input[maxstrlen];  // Variable store to receive character input.
        int method = 0;         // Variable used to both control system behaviour and control user input.
        
        double CoP = 0.0;       // Process Coefficient of Performance.
        double CoPRev = 0.0;    // Equivalent reversible process Coefficient of Performance.
        double eta = 0.0;       // Thermal efficiency.
        double etac = 0.0;      // Reversible thermal efficiency.
        
        double wnet = 0.0;      // Net work done.
        double qhot = 0.0;      // Heat received to system from hot reservoir.
        double qcold = 0.0;     // Heat sent from system to cold reservoir.
        double THot = 0.0;      // Temperature of hot reservoir.
        double TCold = 0.0;     // Temperature of cold reservoir.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        while(method == 0)
        {
            printf("Please select from one of the two listed processes:\n");
            printf("1. Refrigerator.\n2. Heat Pump\nSelection [1, 2]: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0]){
                case '1':
                    method = 1;
                    break;
                case '2':
                    method = 2;
                    break;
                default:
                    printf("Invalid input. Please enter either '1' or '2'.\n");
                    break;
            }
        }
        CoPVariable(method, &wnet, &qhot, &qcold, &THot, &TCold);
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        if(method == 1)
        {
            CoP = CoPFridge(qcold, wnet);
            CoPRev = CoPRevFridge(TCold, THot);
            
            eta = etaFridge(CoP);
            etac = etaFridge(CoPRev);
        }
        if(method == 2)
        {
            CoP = CoPHeatPump(qhot, wnet);
            CoPRev = CoPRevHeatPump(TCold, THot);
            
            eta = etaHeatPump(CoP);
            etac = etaHeatPump(CoPRev);
        }
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        CoPDisplay(method, wnet, qhot, qcold, THot, TCold, CoP, CoPRev, eta, etac);
        
        //  Writing to File
        CoPWriteSwitch(method, wnet, qhot, qcold, THot, TCold, CoP, CoPRev, eta, etac);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
