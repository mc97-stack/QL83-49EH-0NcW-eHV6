//
//  06bEquilibriumConversion.c
//  Process Model
//
//  Created by Matthew Cheung on 26/11/2020.
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
#include "B48BC_T6.h"
#include "06bEquilibriumConversion.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void EquiConvVariable(int mode, double *reacted, double *stoich, double *EoR, double *initial)
{
    if(mode == 1)
    {
        *reacted = inputDouble(0, 1, "moles of i reacted", "mol");
    }
    if(mode == 2)
    {
        *stoich = inputDouble(0, 1, "stoichiometric coefficient", "");
        
        *EoR = inputDouble(0, 0, "extent of reaction", "mol");
    }
    *initial = inputDouble(0, 0, "initial moles of species i", "mol");
}

/// MARK: GENERAL CALCULATIONS
double EquiConvCalc1(double reacted, double initial)
{
    reacted = fabs(reacted);
    
    return reacted/initial;
}

double EquiConvCalc2(double stoich, double EoR, double initial)
{
    stoich = fabs(stoich);
    stoich = (stoich)*EoR;
    
    return stoich/initial;
}

/// MARK: DISPLAY AND WRITE
void EquiConvDisplay(int mode, double reacted, double stoich, double EoR, double initial, double Conv)
{
    printf("_Equilibrium_Conversion_Results_\n");
    printf("\tInput parameters:\n");
    if(mode == 1)
    {
        printf("Moles of i ");
        if(stoich < 0){
            printf("reacted:\n");
        }else{
            printf("produced:\n");
        }
        printf("\\Delta{n}_i =\t%.3f\tmol\n", reacted);
    }
    if(mode == 2)
    {
        printf("Stoichiometric coefficient:\n");
        printf("v_i =\t%.3f\n", stoich);
        
        printf("Extent of reaction:\n");
        printf("\\varepsilon =\t%.3f\tmol\n", EoR);
    }
    printf("Initial moles of species i:\n");
    printf("n_{i, 0} =\t%.3f\tmol\n\n", initial);
    
    if(mode == 2)
    {
        printf("\tIntermediate parameters:\n");
        printf("Moles of i");
        if(stoich < 0){
            printf(" reacted:\n");
        }else{
            printf(" produced:\n");
        }
        printf("\\Delta{n}_i =\t%.3f\tmol\n\n", stoich*EoR);
    }
    
    printf("\tOutput parameters:\n");
    printf("Equilibrium conversion:\n");
    printf("\\chi =\t%.3f\n", Conv);
}

void EquiConvWrite(int mode, double reacted, double stoich, double EoR, double initial, double Conv)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Equilibrium Conversion Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Equilibrium Conversion Results");
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
    fprintf(fp, "_Equilibrium_Conversion_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    if(mode == 1)
    {
        fprintf(fp, "Moles of i ");
        if(stoich < 0){
            fprintf(fp, "reacted:\n");
        }else{
            fprintf(fp, "produced:\n");
        }
        fprintf(fp, "\\Delta{n}_i =\t%.3f\tmol\n", reacted);
    }
    if(mode == 2)
    {
        fprintf(fp, "Stoichiometric coefficient:\n");
        fprintf(fp, "v_i =\t%.3f\n", stoich);
        
        fprintf(fp, "Extent of reaction:\n");
        fprintf(fp, "\\varepsilon =\t%.3f\tmol\n", EoR);
    }
    fprintf(fp, "Initial moles of species i:\n");
    fprintf(fp, "n_{i, 0} =\t%.3f\tmol\n\n", initial);
    
    if(mode == 2)
    {
        fprintf(fp, "\tIntermediate parameters:\n");
        fprintf(fp, "Moles of i");
        if(stoich < 0){
            fprintf(fp, " reacted:\n");
        }else{
            fprintf(fp, " produced:\n");
        }
        fprintf(fp, "\\Delta{n}_i =\t%.3f\tmol\n\n", stoich*EoR);
    }
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Equilibrium conversion:\n");
    fprintf(fp, "\\chi =\t%.3f\n", Conv);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void EquiConvWriteSwitch(int mode, double reacted, double stoich, double EoR, double initial, double Conv)
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
                EquiConvWrite(mode, reacted, stoich, EoR, initial, Conv);
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
void EquilibriumConversion(void)
{
    int whilmain = 0;
    printf("Equilibrium Conversion\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        char input[maxstrlen];
        int control = 0;
        int mode = 0;
        
        double EquiConv = 0.0;
        
        double reacted = 0.0;
        double stoich = 0.0;
        double EoR = 0.0;
        double initial = 0.0;
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        control = 1;
        while(control == 1)
        {
            printf("Please select from the following methods:\n");
            printf("1. Moles of species i reacted.\n");
            printf("2. Extent of reaction and stoichiometric coefficient.\n");
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
                    goto skip;
                    break;
                default:
                    printf("Input not recognised. Please try again.\n");
                    break;
            }
        }
        EquiConvVariable(mode, &reacted, &stoich, &EoR, &initial);
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        // Calculation function(s)
        if(mode == 1)
        {
            EquiConv = EquiConvCalc1(reacted, initial);
        }
        if(mode == 2)
        {
            EquiConv = EquiConvCalc2(stoich, EoR, initial);
        }
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        EquiConvDisplay(mode, reacted, stoich, EoR, initial, EquiConv);
        
        //  Writing to File
        EquiConvWriteSwitch(mode, reacted, stoich, EoR, initial, EquiConv);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
skip:
    fflush(stdout);
}
