//
//  03daoneK.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 09/10/2020.
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

//  Custom Header Files
#include "System.h"
#include "03dOneK.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define g 9.80665

/// MARK: DATA BANK
OneKFittings OneKData(OneKFittings input)
{
    input.data[0] = 0.35;
    input.data[1] = 0.8;
    input.data[2] = 1.5;
    input.data[3] = 1.2;
    input.data[4] = 1.8;
    input.data[5] = 0.5;
    input.data[6] = 1.0;
    input.data[7] = 0.04;
    input.data[8] = 6.0;
    input.data[9] = 0.15;
    input.data[10] = 1.0;
    input.data[11] = 4.0;
    input.data[12] = 16.0;
    input.data[13] = 0.4;
    input.data[14] = 0.4;
    
    return input;
}

/// MARK: VARIABLE INPUT
OneKFittings OneKVariable(OneKFittings table, double *u)
{
    char input[maxstrlen];  // Variable used to store keyboard input.
    
    //  Setting data to data column
    table = OneKData(table);
    
    //  Collecting fluid velocity
    *u = inputDouble(0, 0, "fluid velocity", "m/s");
    
    //  Collecting table.count
    printf("Standard 45 deg elbow = ");
    table.count[0] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg elbow standard radius = ");
    table.count[1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg square elbow = ");
    table.count[2] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Entry from leg T-piece = ");
    table.count[3] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Entry into leg T-piece = ");
    table.count[4] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Sudden Reduction (Tank outlet) = ");
    table.count[5] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Sudden Expansion (Tank Inlet) = ");
    table.count[6] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Unions and Couplings = ");
    table.count[7] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Globe valve fully open = ");
    table.count[8] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (100 pct) = ");
    table.count[9] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (75 pct) = ");
    table.count[10] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (50 pct) = ");
    table.count[11] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (25 pct) = ");
    table.count[12] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Ball valve (100 pct) = ");
    table.count[13] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Plug valve open = ");
    table.count[14] = atoi(fgets(input, sizeof(input), stdin));
    
    return table;
}

/// MARK: GENERAL CALCULATION
double OneKCalculation(int count, double data, double u)
{
    double hf = 0.0;
    
    hf = pow(u, 2);
    hf = (hf)/(2*g);
    hf = data*(hf);
    hf = count *(hf);
    
    return hf;
}

/// MARK: ARRAY FUNCTION
OneKFittings OneKFinalTable(OneKFittings data, double u)
{
    // Counts and database should already be specified prior to this function being run
    for(int i = 0; i < 15; ++i)
    {
        data.headloss[i] = OneKCalculation(data.count[i], data.data[i], u);
    }
    return data;
}

/// MARK: DISPLAY AND WRITE
void OneKDisplay(OneKFittings table, double u, double total)
{
    int i = 0;
    
    printf("Fluid velocity:\n");
    printf("u =\t%.3f\tm/s\n", u);
    
    printf("Total Head Loss:\n");
    printf("total =\t%.3f\tm\n\n", total);
    
    printf("h_L = K \\frac{u^2}{2*g}\n");
    printf("Fitting\tk\tCount\tHead loss (m)\n");
    i = 0;
    printf("Standard 45 deg elbow\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    
    printf("90 deg elbow standard radius\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    ++i;
    
    printf("90 deg square elbow\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    ++i;
    
    printf("Entry from leg T-piece\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    ++i;
    
    printf("Entry into leg T-piece\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    ++i;
    
    printf("Sudden Reduction (Tank outlet)\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    ++i;
    
    printf("Sudden Expansion (Tank Inlet)\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    ++i;
    
    printf("Unions and Couplings\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    ++i;
    
    printf("Globe valve fully open\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    ++i;
    
    printf("Gate valve (100 pct)\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    ++i;
    
    printf("Gate valve (75 pct)\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    ++i;
    
    printf("Gate valve (50 pct)\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    ++i;
    
    printf("Gate valve (25 pct)\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    ++i;
    
    printf("Ball valve (100 pct)\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    ++i;
    
    printf("Plug valve open\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    fflush(stdout);
}

void OneKWrite(OneKFittings table, double u, double total)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + 1K Results Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " 1K Results");
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
    fprintf(fp, "_Pressure_Loss_Through_Pipe_Fittings_(1K_Method)_Results_\n");
    
    int i = 0;
    
    fprintf(fp, "Fluid velocity:\n");
    fprintf(fp, "u =\t%.3f\tm/s\n", u);
    
    fprintf(fp, "Total Head Loss:\n");
    fprintf(fp, "total =\t%.3f\tm\n\n", total);
    
    fprintf(fp, "h_L = K \\frac{u^2}{2*g}\n");
    fprintf(fp, "Fitting\tk\tCount\tHead loss (m)\n");
    i = 0;
    fprintf(fp, "Standard 45 deg elbow\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    i = 1;
    fprintf(fp, "90 deg elbow standard radius\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    i = 2;
    fprintf(fp, "90 deg square elbow\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    i = 3;
    fprintf(fp, "Entry from leg T-piece\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    i = 4;
    fprintf(fp, "Entry into leg T-piece\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    i = 5;
    fprintf(fp, "Sudden Reduction (Tank outlet)\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    i = 6;
    fprintf(fp, "Sudden Expansion (Tank Inlet)\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    i = 7;
    fprintf(fp, "Unions and Couplings\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    i = 8;
    fprintf(fp, "Globe valve fully open\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    i = 9;
    fprintf(fp, "Gate valve (100 pct)\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    i = 10;
    fprintf(fp, "Gate valve (75 pct)\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    i = 11;
    fprintf(fp, "Gate valve (50 pct)\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    i = 12;
    fprintf(fp, "Gate valve (25 pct)\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    i = 13;
    fprintf(fp, "Ball valve (100 pct)\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    i = 14;
    fprintf(fp, "Plug valve open\t");
    fprintf(fp, "%.2f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\n", table.headloss[i]);
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void OneKWriteSwitch(OneKFittings table, double u, double total)
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
                OneKWrite(table, u, total);
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
void OneK()
{
    //  Variable declaration
    OneKFittings *OneKTable = calloc(1, sizeof(OneKFittings)); // Struct used to store collected
    double totalHead = 0.0;         // Total head loss through stated fittings.
    
    double u = 0.0;                 // Fluid velocity.
    
        //  Variables for timing function
    struct timespec start, end;
    double elapsed = 0.0;
    
    //  Collecting data
    *OneKTable = OneKVariable(*OneKTable, &u);
    
    //  Performing calculations
    clock_getres(CLOCK_MONOTONIC, &start);
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    *OneKTable = OneKFinalTable(*OneKTable, u);
    
    //  Calculating total head loss
    for(int i = 0; i < 15; ++i)
    {
        totalHead += OneKTable->headloss[i];
    }
    clock_getres(CLOCK_MONOTONIC, &end);
    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed = timer(start, end);

    printf("Calculations completed in %.6f seconds.\n", elapsed);
    
    // Displaying data
    OneKDisplay(*OneKTable, u, totalHead);
    
    // Writing data
    OneKWriteSwitch(*OneKTable, u, totalHead);
    free(OneKTable);
}
