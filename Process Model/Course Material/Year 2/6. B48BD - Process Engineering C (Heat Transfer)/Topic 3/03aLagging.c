//
//  03aLagging.c
//  Process Model
//
//  Created by Matthew Cheung on 19/12/2020.
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
#include "B48BD_T3.h"
#include "01aTemperatureConversion.h"
#include "03aLagging.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void LaggingExtVariable(double *T1, double *T2, double *r1)
{
    *T1 = CelsiusKelvin(inputDouble(1, 1, "hot surface temperature", "deg C"));
    
    *T2 = CelsiusKelvin(inputDouble(1, 1, "cold surface temperature", "deg C"));
    
    *r1 = inputDouble(0, 0, "inner pipe radius", "mm");
    *r1 = 0.001*(*r1);
}

LaggingData LaggingIntVariable(int mode1, int mode2, int i, LaggingData data)
{
    // mode1 controls whether k (1) or h (2) is collected.
    // mode2 controls whether the radius is collected [1/0].
    
    double k = 0.0;
    double h = 0.0;
    double r = 0.0;
    
    int control = 0;
    
    if(mode1 == 1)
    {
        k = inputDouble(0, 0, "thermal conductivity", "W/m.K");
        data.k[i] = k;
    }
    if(mode1 == 2)
    {
        h = inputDouble(0, 0, "fluid heat transfer coefficient", "W/m2.K");
        data.h[i] = h;
    }
    if(mode2 == 1)
    {
        control = 1;
        while(control == 1)
        {
            r = inputDouble(0, 0, "layer outer radius", "mm");
            r = 0.001*(r);
            if((data.r[i-1])<(r))
            {
                // Radius entered is bigger than the previous value.
                data.r[i] = r;
                control = 0;
            }else{
                printf("Please enter a value that is greater than %.3f mm\n", 1000*data.r[i-1]);
            }
        }
    }
    return data;
}

/// MARK: GENERAL CALCULATIONS
double LagConvResist(double h, double r)
{
    double R = 0.0;
    double sto = 0.0;
    
    sto = 2*M_PI;
    sto = (sto)*r;
    sto = h*(sto);
    
    R = 1/(sto);
    
    return R;
}

double LagCondResist(double k, double r1, double r2)
{
    double R = 0.0;
    double sto = 0.0;
    
    sto = r2/r1;
    sto = log(sto);
    
    R = 2*M_PI;
    R = k*(R);
    R = (sto)/(R);
    
    return R;
}

double LagTotalResist(LaggingData data)
{
    double R = 0.0;
    
    // Calculating resistance from convection.
    R = LagConvResist(data.h[0], data.r[0]);
    R += LagConvResist(data.h[3], data.r[3]);
    
    // Calculating resistance from conduction.
    R += LagCondResist(data.k[1], data.r[0], data.r[1]);
    R += LagCondResist(data.k[2], data.r[1], data.r[2]);
    
    return R;
}

double LagHeat(double T1, double T2, double R)
{
    double Q = 0.0;
    
    Q = T1 - T2;
    Q = (Q)/R;
    
    return Q;
}

/// MARK: ARRAY FUNCTION
LaggingTable LaggingCalculation(double T1, double T2, LaggingData *data)
{
    LaggingTable results = {0.0};
    
    // Initialising the lagging thicknesses
    double value = 0.0;
    for(int i = 0; i < 32; ++i)
    {
        results.x[i] = value;
        value += 0.01;     // Incrementing the lagging thickness by 1 cm
    }
    // Calculating the resistance table.
    for(int i = 0; i < 32; ++i)
    {
        // Calculating the unknown radi for the system (data.r[2] and data.r[3]).
        data->r[2] = data->r[1] + results.x[i];
        data->r[3] = data->r[2];
        
        // Calculating the resistances
        results.R_lag[i] = LagCondResist(data->k[2], data->r[1], data->r[2]);
        results.R_out[i] = LagConvResist(data->h[3], data->r[3]);
        results.R_tot[i] = LagTotalResist(*data);
        results.Q[i] = LagHeat(T1, T2, results.R_tot[i]);
        results.pctLag[i] = (results.R_lag[i])/(results.R_tot[i]);
    }
    
    return results;
}

/// MARK: DISPLAY AND WRITE
void LaggingDisplay(double T1, double T2, LaggingData data, LaggingTable results)
{
    printf("_Optimal_Lagging_Thickness_Results_\n");
    printf("\tInput parameters:\n");
    printf("Hot surface temperature:\n");
    printf("T1 =\t%.3f\tdeg C\n", KelvinCelsius(T1));
    printf("Cold surface temperature:\n");
    printf("T2 =\t%.3f\tdeg C\n\n", KelvinCelsius(T2));
    
    printf("k (W/m.K)\th (W/m2.K)\tr (m)\n");
    for(int i = 0; i < 4; ++i)
    {
        printf("%.3f\t", data.k[i]);
        printf("%.3f\t", data.h[i]);
        printf("%.3f\n", data.r[i]);
    }
    printf("\n");
    
    printf("\tOutput parameters:\n");
    printf("x (cm)\tR_{lag} (K.m/W)\tR_{out} (K.m/W)\tR_{tot} (K.m/W)\tQ (W/m)\t%%R_{lag}\n");
    for(int i = 0; i < 32; ++i)
    {
        printf("%.3f\t", 100*results.x[i]);
        printf("%.3f\t", results.R_lag[i]);
        printf("%.3f\t", results.R_out[i]);
        printf("%.3f\t", results.R_tot[i]);
        printf("%.3f\t", results.Q[i]);
        printf("%.3f\n", results.pctLag[i]);
    }
}

void LaggingWrite(double T1, double T2, LaggingData data, LaggingTable results)
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
    
    strcat(filename, " Optimal Lagging Results");
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
    fprintf(fp, "_Optimal_Lagging_Thickness_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Hot surface temperature:\n");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n", KelvinCelsius(T1));
    fprintf(fp, "Cold surface temperature:\n");
    fprintf(fp, "T2 =\t%.3f\tdeg C\n\n", KelvinCelsius(T2));
    
    fprintf(fp, "k (W/m.K)\th (W/m2.K)\tr (m)\n");
    for(int i = 0; i < 4; ++i)
    {
        fprintf(fp, "%.3f\t", data.k[i]);
        fprintf(fp, "%.3f\t", data.h[i]);
        fprintf(fp, "%.3f\n", data.r[i]);
    }
    fprintf(fp, "\n");
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "x (cm)\tR_{lag} (K.m/W)\tR_{out} (K.m/W)\tR_{tot} (K.m/W)\tQ (W/m)\t%%R_{lag}\n");
    for(int i = 0; i < 32; ++i)
    {
        fprintf(fp, "%.3f\t", 100*results.x[i]);
        fprintf(fp, "%.3f\t", results.R_lag[i]);
        fprintf(fp, "%.3f\t", results.R_out[i]);
        fprintf(fp, "%.3f\t", results.R_tot[i]);
        fprintf(fp, "%.3f\t", results.Q[i]);
        fprintf(fp, "%.3f\n", results.pctLag[i]);
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void LaggingSwitch(int mode, double T1, double T2, LaggingData data, LaggingTable results)
{
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        char input[maxstrlen];
        
        if(mode == 1){
            printf("Do you want to view the results? ");
        }
        if(mode == 2){
            printf("Do you want to save results to file? ");
        }
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                if(mode == 1){
                    LaggingDisplay(T1, T2, data, results);
                }
                if(mode == 2){
                    LaggingWrite(T1, T2, data, results);
                }
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
void Lagging(void)
{
    int whilmain = 0;
    printf("Optimal Lagging Thickness\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        LaggingTable *results = calloc(1, sizeof(LaggingTable));
        
        double T1 = 0.0;
        double T2 = 0.0;
        LaggingData *data = calloc(1, sizeof(LaggingData));
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        LaggingExtVariable(&T1, &T2, &data->r[0]);
        
        for(int i = 0; i < 4; ++i)
        {
            if(i == 0){
                printf("Pipe fluid parameters:\n");
            }
            if(i == 1){
                printf("Pipe wall parameters:\n");
            }
            if(i == 2){
                printf("Lagging parameters:\n");
            }
            if(i == 3){
                printf("Environment fluid parameters:\n");
            }
            if(i == 0 || i == 3){
                *data = LaggingIntVariable(2, 0, i, *data);
            }
            if(i == 1){
                *data = LaggingIntVariable(1, 1, i, *data);
            }
            if(i == 2){
                *data = LaggingIntVariable(1, 0, i, *data);
            }
            printf("\n");
        }
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        // Calculation function(s)
        *results = LaggingCalculation(T1, T2, data);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        LaggingSwitch(1, T1, T2, *data, *results);
        
        //  Writing to File
        LaggingSwitch(2, T1, T2, *data, *results);
        
        free(data);
        free(results);
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
