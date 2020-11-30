//
//  01bConduction.c
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
#include "01bConduction.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void FouriersLawVariable(double *k, double *A, double *T1, double *T2, double *x)
{
    *k = inputDouble(0, 0, "thermal conductivity", "W/m.K");
    
    *A = inputDouble(0, 0, "heat transfer area", "m2");
    
    *x = inputDouble(0, 0, "surface thickness", "mm");
    *x = (*x)*0.001;    // Conversion to m.
    
    *T1 = inputDouble(1, 1, "initial temperature", "deg C");
    
    *T2 = inputDouble(1, 1, "final temperature", "deg C");
}

/// MARK: GENERAL CALCULATIONS
double FouriersLawCalculation(double k, double A, double x, double T1, double T2)
{
    double Q = 0.0;
    double sto = 0.0;
    
    sto = T2 - T1;
    sto = (sto)/x;
    Q = k*A;
    Q = (Q)*(sto);
    Q = -1*(Q);
    
    return Q;
}

/// MARK: DISPLAY AND WRITE
void FouriersLawDisplay(double k, double A, double x, double T1, double T2, double Q)
{
    printf("_Fourier's_Law_Results_\n");
    printf("\tInput parameters:\n");
    printf("Thermal conductivity:\n");
    printf("k =\t%.3f\tW/m.K\n", k);
    printf("Heat transfer area:\n");
    printf("A =\t%.3f\tm2\n", A);
    printf("Surface thickness:\n");
    printf("x =\t%.3f\tmm\n\n", x*1000);
    
    printf("Initial temperature:\n");
    printf("T1 =\t%.3f\tdeg C\n", T1);
    printf("Final temperature:\n");
    printf("T2 =\t%.3f\tdeg C\n\n", T2);
    
    printf("\tOutput parameters:\n");
    printf("Rate of heat transfer:\n");
    printf("Q =\t%.3f\tW\n", Q);
}

void FouriersLawWrite(double k, double A, double x, double T1, double T2, double Q)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Conduction Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Conduction Results");
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
    fprintf(fp, "_Fourier's_Law_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Thermal conductivity:\n");
    fprintf(fp, "k =\t%.3f\tW/m.K\n", k);
    fprintf(fp, "Heat transfer area:\n");
    fprintf(fp, "A =\t%.3f\tm2\n", A);
    fprintf(fp, "Surface thickness:\n");
    fprintf(fp, "x =\t%.3f\tmm\n\n", x*1000);
    
    fprintf(fp, "Initial temperature:\n");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n", T1);
    fprintf(fp, "Final temperature:\n");
    fprintf(fp, "T2 =\t%.3f\tdeg C\n\n", T2);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Rate of heat transfer:\n");
    fprintf(fp, "Q =\t%.3f\tW\n", Q);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void FouriersLawWriteSwitch(double k, double A, double x, double T1, double T2, double Q)
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
                FouriersLawWrite(k, A, x, T1, T2, Q);
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
void Conduction(void)
{
    int whilmain = 0;
    printf("Fourier's Law\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        double Q = 0.0;     // Rate of heat transfer.
        
        double k = 0.0;     // Thermal conductivity.
        double A = 0.0;     // Heat transfer area.
        double x = 0.0;     // Surface thickness.
        double T1 = 0.0;    // Initial temperature.
        double T2 = 0.0;    // Final temperature.
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        FouriersLawVariable(&k, &A, &T1, &T2, &x);
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        // Calculation function(s)
        Q = FouriersLawCalculation(k, A, x, T1, T2);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        FouriersLawDisplay(k, A, x, T1, T2, Q);
        
        //  Writing to File
        FouriersLawWriteSwitch(k, A, x, T1, T2, Q);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
