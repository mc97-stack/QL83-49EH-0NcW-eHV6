//
//  03cHydrDiam.c
//  Process Model
//
//  Created by Matthew Cheung on 02/07/2020.
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
//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Custom header files
#include "System.h"
#include "B48BB_T3.h"
#include "03cHydrDiam.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void HydrDiamVariable(double *A_F, double *P_W)
{
    double convfactor = 0.0;    // Conversion factor
    
    *A_F = inputDouble(0, 0, "cross-sectional flow area", "mm2");
    
    convfactor = pow(1000,2);
    convfactor = 1/(convfactor);
    *A_F = (*A_F)*convfactor;
    
    *P_W = inputDouble(0, 0, "wetted perimeter", "cm");
    *P_W = (*P_W)*0.01;
    
    fflush(stdout);
}

/// MARK: GENERAL CALCULATION
double HydrDiamCalculation(double A_F, double P_W)
{
    double d_H = 0.0;
    double top = 0.0;
    double bot = 0.0;
    
    top = 4*A_F;
    bot = P_W;
    d_H = (top)/(bot);
    
    return d_H;
}

/// MARK: DISPLAY AND WRITE
void HydrDiamDisplay(double A_F, double P_W, double d_H)
{
    printf("_Hydraulic_Diameter_Results_\n");
    printf("\tInput parameters:\n");
    printf("Cross-sectional flow area:\n");
    printf("A_F =\t%.3f\tmm2\n", A_F*pow(1000,2));
    printf("Wetted perimeter:\n");
    printf("P_W =\t%.3f\tcm\n\n", P_W*100);
    
    printf("\tOutput parameters:\n");
    printf("Hydraulic diameter:\n");
    printf("d_H =\t%.3f\tmm\n", d_H*1000);
    fflush(stdout);
}

void HydrDiamWrite(double A_F, double P_W, double d_H)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Hydraulic Diameter Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Hydraulic Diameter Results");
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
    fprintf(fp, "_Hydraulic_Diameter_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Cross-sectional flow area:\n");
    fprintf(fp, "A_F =\t%.3f\tmm2\n", A_F*pow(1000,2));
    fprintf(fp, "Wetted perimeter:\n");
    fprintf(fp, "P_W =\t%.3f\tcm\n\n", P_W*100);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Hydraulic diameter:\n");
    fprintf(fp, "d_H =\t%.3f\tmm\n", d_H*1000);
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void HydrDiamWriteSwitch(double A_F, double P_W, double d_H)
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
                HydrDiamWrite(A_F, P_W, d_H);
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
void HydraulicDiameter()
{
    //  Pseudo-main function.
    int whilmain = 0;
    printf("Hydraulic diameter calculation\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        double d_H = 0.0;   // Hydraulic diameter
        
        double A_F = 0.0;   // Wetted perimeter
        double P_W = 0.0;   // Cross-sectional flow area
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data collection
        HydrDiamVariable(&A_F, &P_W);
        
        //  Running calculations
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        d_H = HydrDiamCalculation(A_F, P_W);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        HydrDiamDisplay(A_F, P_W, d_H);
        
        //  Writing to File
        HydrDiamWriteSwitch(A_F, P_W, d_H);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
