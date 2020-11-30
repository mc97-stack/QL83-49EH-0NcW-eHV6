//
//  06cEquilibriumConstant.c
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
#include "06cEquilibriumConstant.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define R 8.3145

/// MARK: VARIABLE INPUT
void EquiConstVariable(int mode, double *h_rxn, double *K1, double *T1, double *T2, double *P1, double *stoich)
{
    *h_rxn = inputDouble(0, 1, "reaction enthalpy", "J/mol");
    
    *T1 = inputDouble(1, 1, "reference temperature", "deg C");
    *T1 = (*T1) + 273.15;
    
    *K1 = inputDouble(0, 0, "Equilibrium constant at reference temperature", "[ ]");
    
    *T2 = inputDouble(1, 1, "temperature of K2", "deg C");
    *T2 = (*T2) + 273.15;
    
    if(mode == 2)
    {
        *P1 = inputDouble(0, 0, "reference pressure", "bar");
        
        *stoich = inputDouble(1, 1, "overall stoichiometric coefficient", "");
    }
}

/// MARK: GENERAL CALCULATIONS
double VantHoffCalculation(double h_rxn, double K1, double T1, double T2)
{
    double K2 = 0.0;
    double sto1 = 0.0;
    double sto2 = 0.0;
    
    sto1 = 1/T2;
    sto2 = 1/T1;
    sto1 = (sto1) - (sto2);     // Bracket RHS term calculated.
    
    sto2 = h_rxn/R;
    sto2 = -1*(sto2);
    sto1 = (sto2)*(sto1);       // RHS calculated.
    
    K2 = (sto1) + log(K1);      // Applying log rules.
    K2 = exp(K2);               // K2 at T2 estimated.
    
    return K2;
}

double VantHoffCalc(double h_rxn, double K1, double T1, double T2)
{
    typedef struct CalcTable{
        double T1[100];
        double T2[100];
        double K1[100];
        double K2[100];
    } CalcTable;
    
    int reso = 100;
    double incr = 0.0;
    
    double K2 = 0.0;
    
    incr = T2 - T1;
    incr = (incr)/((double)reso);
    
    CalcTable *table = calloc(1, sizeof(CalcTable));
    // Initialising first row
    int i = 0;
    table->T1[i] = T1;
    table->T2[i] = table->T1[i] + incr;
    table->K1[i] = K1;
    table->K2[i] = VantHoffCalculation(h_rxn, table->K1[i], table->T1[i], table->T2[i]);
    
    for(i = 1; i < 100; ++i)
    {
        table->T1[i] = table->T2[i - 1];
        table->T2[i] = table->T1[i] + incr;
        table->K1[i] = table->K2[i - 1];
        table->K2[i] = VantHoffCalculation(h_rxn, table->K1[i], table->T1[i], table->T2[i]);
    }
    
    K2 = table->K2[99];
    
    free(table);
    
    return K2;
}

double KPCalculation(double Pref, double stoich, double K2)
{
    double KP = 0.0;
    
    KP = pow(Pref, stoich);
    
    return KP*K2;
}

/// MARK: DISPLAY AND WRITE
void EquiConstDisplay(int mode, double h_rxn, double K1, double K2, double KP, double T1, double T2, double P1, double stoich)
{
    printf("_Equilibrium_Constant_Estimation_\n");
    printf("\tInput parameters:\n");
    printf("Overall stoichiometric coefficient:\n");
    printf("v =\t%.3f\n", stoich);
    printf("Enthalpy change of reaction:\n");
    printf("h_rxn =\t%.3f\tJ/mol\n\n", h_rxn);
    
    printf("Reference equilibrium constant:\n");
    printf("K1 =\t%.3f\t[ ]\n\n", K1);
    
    printf("Reference temperature:\n");
    printf("T1 =\t%.3f\tdeg C\n", T1 - 273.15);
    printf("System temperature:\n");
    printf("T2 =\t%.3f\tdeg C\n\n", T2 - 273.15);
    
    if(mode == 2)
    {
        printf("Reference pressure:\n");
        printf("P1 =\t%.3f\tbar\n\n", P1);
        
        printf("\tIntermediate parameters:\n");
        printf("Temperature adjusted equilibrium constant:\n");
        printf("K2 =\t%.3f\t[ ]\n\n", K2);
    }
    
    printf("\tOutput parameters:\n");
    if(mode == 1)
    {
        printf("Temperature adjusted equilibrium constant:\n");
        printf("K2 =\t%.3f\t[ ]\n\n", K2);
    }
    if(mode == 2)
    {
        printf("Pressure adjusted equilibrium constant:\n");
        printf("KP =\t%.3f\t[ ]\n\n", KP);
    }
}

void EquiConstWrite(int mode, double h_rxn, double K1, double K2, double KP, double T1, double T2, double P1, double stoich)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Equilibrium Constant Estimation
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Equilibrium Constant Estimation");
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
    fprintf(fp, "_Equilibrium_Constant_Estimation_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Overall stoichiometric coefficient:\n");
    fprintf(fp, "v =\t%.3f\n", stoich);
    fprintf(fp, "Enthalpy change of reaction:\n");
    fprintf(fp, "h_rxn =\t%.3f\tJ/mol\n\n", h_rxn);
    
    fprintf(fp, "Reference equilibrium constant:\n");
    fprintf(fp, "K1 =\t%.3f\t[ ]\n\n", K1);
    
    fprintf(fp, "Reference temperature:\n");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n", T1 - 273.15);
    fprintf(fp, "System temperature:\n");
    fprintf(fp, "T2 =\t%.3f\tdeg C\n\n", T2 - 273.15);
    
    if(mode == 2)
    {
        fprintf(fp, "Reference pressure:\n");
        fprintf(fp, "P1 =\t%.3f\tbar\n\n", P1);
        
        fprintf(fp, "\tIntermediate parameters:\n");
        fprintf(fp, "Temperature adjusted equilibrium constant:\n");
        fprintf(fp, "K2 =\t%.3f\t[ ]\n\n", K2);
    }
    
    fprintf(fp, "\tOutput parameters:\n");
    if(mode == 1)
    {
        fprintf(fp, "Temperature adjusted equilibrium constant:\n");
        fprintf(fp, "K2 =\t%.3f\t[ ]\n\n", K2);
    }
    if(mode == 2)
    {
        fprintf(fp, "Pressure adjusted equilibrium constant:\n");
        fprintf(fp, "KP =\t%.3f\t[ ]\n\n", KP);
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void EquiConstWriteSwitch(int mode, double h_rxn, double K1, double K2, double KP, double T1, double T2, double P1, double stoich)
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
                EquiConstWrite(mode, h_rxn, K1, K2, KP, T1, T2, P1, stoich);
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
void EquilibriumConstant(void)
{
    int whilmain = 0;
    printf("Equilibrium Constant Estimation\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        char input[maxstrlen];
        int control = 0;
        int mode = 0;
        
        double K2 = 0.0;        // Temperature adjusted equilibrium constant.
        double KP = 0.0;        // Pressure adjusted equilibrium constant.
        
        double h_rxn = 0.0;     // Enthalpy change of reaction.
        double T1 = 0.0;        // Reference temperature.
        double T2 = 0.0;        // System temperature.
        double K1 = 0.0;        // Reference equilibrium constant.
        double P1 = 0.0;        // Reference pressure.
        double stoich = 0.0;    // Overall stoichiometric coefficient.
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        control = 1;
        while(control == 1)
        {
            printf("What correction does your reference equilibrium constant need?\n");
            printf("1. Temperature.\n");
            printf("2. Temperature and Pressure.\n");
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
                    
                    break;
                default:
                    printf("Input not recognised. Please try again.\n");
                    break;
            }
        }
        EquiConstVariable(mode, &h_rxn, &K1, &T1, &T2, &P1, &stoich);
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        // Calculation function(s)
        K2 = VantHoffCalc(h_rxn, K1, T1, T2);
        
        if(mode == 2)
        {
            KP = KPCalculation(P1, stoich, K2);
        }
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        EquiConstDisplay(mode, h_rxn, K1, K2, KP, T1, T2, P1, stoich);
        
        //  Writing to File
        EquiConstWriteSwitch(mode, h_rxn, K1, K2, KP, T1, T2, P1, stoich);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
