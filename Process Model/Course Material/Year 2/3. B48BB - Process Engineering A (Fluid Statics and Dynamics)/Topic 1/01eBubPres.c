//
//  01eBubPres.c
//  Process Model
//
//  Created by Matthew Cheung on 25/06/2020.
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
//  Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Custom header files
#include "System.h"
#include "B48BB_T1.h"
#include "01eBubPres.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void BubPresVariable(double *sigma, double *r)
{
    *sigma = inputDouble(0, 0, "surface tension", "N/m");
    
    *r = inputDouble(0, 0, "radius of fluid droplet", "mm");
    *r = (*r)*0.001; //Conversion (mm to m)
}

/// MARK: GENERAL CALCULATION
double BubPresCalculation(double sigma, double r)
{
    double top = 0.0;
    double P = 0.0; // Bubble pressure.
    
    top = 0.0; //Initialising variable
    
    top = 2*sigma;
    P = (top)/r;
    
    return P;
}

/// MARK: DISPLAY AND WRITE
void BubPresDisplay(double sigma, double r, double P)
{
    printf("_Bubble_Pressure_Calculations_\n");
    printf("\tInput Parameters:\n");
    printf("Surface tension:\n");
    printf("sigma =\t%.3f\tN/m\n", sigma);
    printf("Bubble radius:\n");
    printf("r =\t%.3f\tmm\n\n", r*1000);
    
    printf("\tOutput Parameters:\n");
    printf("P =\t%.3f\tPa\t=\\frac{2\\sigma}{r}\n", P);
    fflush(stdout);
}

void BubPresWrite(double sigma, double r, double P)
{
    //  Function variables
    char filename[maxstrlen];   // Character array used to store file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Bubble Pressure Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Bubble Pressure Results");
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
    void free(void *filename);
    
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
    
    //  Open file
    fp = fopen(filename, "w+");
    
    //  Write to file
    fprintf(fp, "_Bubble_Pressure_Calculations_\n");
    fprintf(fp, "\tInput Parameters:\n");
    fprintf(fp, "Surface tension:\n");
    fprintf(fp, "sigma =\t%.3f\tN/m\n", sigma);
    fprintf(fp, "Bubble radius:\n");
    fprintf(fp, "r =\t%.3f\tmm\n\n", r*1000);
    
    fprintf(fp, "\tOutput Parameters:\n");
    fprintf(fp, "P =\t%.3f\tPa\t=\\frac{2\\sigma}{r}\n", P);
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void BubPresWriteSwitch(double sigma, double r, double P)
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
                BubPresWrite(sigma, r, P);
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
void BubblePressure()
{
    //  Pseudo-main function.
    int whilmain = 0;
    printf("Bubble Pressure Calculator\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Declaring variables
        double P = 0.0;     // Pressure inside a spherical droplet.
        
        double sigma = 0.0; // Surface tension.
        double r = 0.0;     // Radius of spherical droplet.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Collecting data
        BubPresVariable(&sigma, &r);
        
        //  Running calculations
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        P = BubPresCalculation(sigma, r);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        BubPresDisplay(sigma, r, P);
        
        //  Writing to file
        BubPresWriteSwitch(sigma, r, P);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
