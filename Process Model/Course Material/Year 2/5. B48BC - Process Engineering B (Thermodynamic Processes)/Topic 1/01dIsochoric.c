//
//  01dIsochoric Process.c
//  Process Model
//
//  Created by Matthew Cheung on 08/10/2020.
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
#include "01dIsochoric.h"
#include "IdealGasLaw.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define R 8.3145

/// MARK: VARIABLE INPUT
void IsocVariable(int method, double *P1, double *P2, double *V, double *T1, double *T2, double *n, double *cv)
{
    if(method == 1){
        *P1 = inputDouble(0, 0, "initial system pressure", "kPa");
        *P1 = (*P1)*1000;
        
        *P2 = inputDouble(0, 0, "final system pressure", "kPa");
        *P2 = (*P2)*1000;
        
        *V = inputDouble(0, 0, "system volume", "m3");
    }
    if(method == 2){
        *T1 = inputDouble(1, 1, "initial system temperature", "deg C");
        *T1 = (*T1) + 273.15;
        
        *T2 = inputDouble(1, 1, "final system temperature", "deg C");
        *T2 = (*T2) + 273.15;
    }
    if(method == 1 || method == 2){
        *n = inputDouble(0, 0, "molar flowrate", "kmol/s");
        *n = (*n)*1000;
        
        *cv = inputDouble(0, 0, "heat capacity at constant volume", "J/mol.K");
    }
    fflush(stdout);
}

/// MARK: GENERAL CALCULATIONS
double IsocPressure(double P1, double P2, double V, double cv)
{
    double brack = 0.0;
    double heat = 0.0;
    
    brack = P2 - P1;
    
    heat = V/R;
    heat = (heat)*brack;
    heat = (heat)*cv;
    
    return heat;
}

double IsocTemperature(double T1, double T2, double n, double cv)
{
    double heat = 0.0;
    
    heat = T2 - T1;
    heat = cv*(heat);
    heat = n*(heat);
    
    return heat;
}

double IsocFinalTemperature(double T1, double P1, double P2)
{
    double T2 = 0.0;
    
    T2 = T1/P1;
    T2 = (T2)*P2;
    
    return T2;
}

/// MARK: ARRAY FUNCTION
T1ThermoProf IsocProfile(int method, double P1, double P2, double V, double T1, double T2, double n, double cv)
{
    double incr = 0.0;  // Increment between data points
    int reso = 0;       // Resolution of the generated plot
    int i = 0;          // Row controller
    
    T1ThermoProf profile = {0.0};
    double total = 0.0;
    
    reso = 249;
    
    if(method == 1){
        incr = P2 - P1;
        incr = (incr)/reso;
    }
    if(method == 2){
        incr = T2 - T1;
        incr = (incr)/reso;
    }
    
    // Setting the initial system conditions
    i = 0;
    if(method == 1){
        profile.P[i] = P1;
        profile.V[i] = V;
        profile.T[i] = IdealTemperature(n, profile.P[i], profile.V[i]);
    }
    if(method == 2){
        profile.P[i] = 0.0;
        profile.V[i] = 0.0;
        profile.T[i] = T1;
    }
    profile.W_V[i] = 0.0;
    profile.Q[i] = 0.0;
    total = 0.0;
    
    for(i = 1; i < (reso + 1); ++i)
    {
        if(method == 1){
            profile.P[i] = profile.P[i - 1] + incr;
            profile.V[i] = V;
            profile.T[i] = IsocFinalTemperature(profile.T[i - 1], profile.P[i - 1], profile.P[i]);
            profile.W_V[i] = 0.0;
            profile.Q[i] = IsocPressure(profile.P[i - 1], profile.P[i], profile.V[i], cv);
            total += profile.Q[i];
        }
        if(method == 2){
            profile.P[i] = 0.0;
            profile.V[i] = 0.0;
            profile.T[i] = profile.T[i - 1] + incr;
            profile.W_V[i] = 0.0;
            profile.Q[i] = IsocTemperature(profile.T[i - 1], profile.T[i], n, cv);
            total += profile.Q[i];
        }
    }
    printf("Total heat required = %.3f kW\n", total*0.001);
    printf("Profile calculated in %d rows\n\n", i);
    
    return profile;
}

/// MARK: DISPLAY AND WRITE
void IsocProcDisplay(double P1, double P2, double V, double T1, double T2, double n, double c_v, T1ThermoProf profile)
{
    double total = 0.0;
    
    printf("_Isochoric_Process_Results_\n");
    printf("\tInput parameters:\n");
    printf("Initial system pressure:\n");
    printf("P1 =\t%.3f\tkPa\n", P1*0.001);
    printf("Final system pressure:\n");
    printf("P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    printf("System volume:\n");
    printf("V =\t%.3f\tm3\n\n", V);
    
    printf("Initial system temperature:\n");
    printf("T1 =\t%.3f\tdeg C\n", T1-273.15);
    printf("Final system temperature:\n");
    printf("T2 =\t%.3f\tdeg C\n\n", T2-273.15);
    
    printf("_System-Specific_parameters:_\n");
    printf("Molar flowrate of component i:\n");
    printf("n =\t%.3f\tkmol/s\n", n*0.001);
    printf("c_v =\t%.3f\tJ/(mol. K)\n", c_v);
    printf("R =\t%.4f\tJ/(mol. K)\n\n", R);
    
    printf("\tOutput parameters:\n");
    
    // Profile (Two Temperature columns (K and deg C))
    printf("P (kPa)\tV (m3)\tT (K)\tT(deg C)\t\tQ (kW)\tQ (kW)\n");
    for(int i = 0; i < 250; ++i)
    {
        printf("%f\t", profile.P[i]*0.001);
        printf("%f\t", profile.V[i]);
        printf("%f\t", profile.T[i]);
        printf("%f\t\t", profile.T[i] - 273.15);
        printf("%f\t", profile.Q[i]*0.001);
        total += profile.Q[i]*0.001;
        printf("%f\n", total);
    }
    fflush(stdout);
}

void IsocProcWrite(double P1, double P2, double V, double T1, double T2, double n, double c_v, T1ThermoProf profile)
{
    //  Function variables
    char filename[maxstrlen];
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //  Set file name as timestamp + Isochoric Process Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Isochoric Results");
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
    double total = 0.0;
    
    fprintf(fp, "_Isochoric_Process_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial system pressure:\n");
    fprintf(fp, "P1 =\t%.3f\tkPa\n\n", P1*0.001);
    fprintf(fp, "Final system pressure:\n");
    fprintf(fp, "P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    fprintf(fp, "System volume:\n");
    fprintf(fp, "V =\t%.3f\tm3\n\n", V);
    
    fprintf(fp, "Initial system temperature:\n");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n\n", T1-273.15);
    fprintf(fp, "Final system temperature:\n");
    fprintf(fp, "T2 =\t%.3f\tdeg C\n\n", T2-273.15);
    
    fprintf(fp, "_System-Specific_parameters:_\n");
    
    fprintf(fp, "Molar flowrate of component i:\n");
    fprintf(fp, "n =\t%.3f\tkmol/s\n\n", n*0.001);
    fprintf(fp, "c_v =\t%.3f\tJ/(mol. K)\n", c_v);
    fprintf(fp, "R =\t%.4f\tJ/(mol. K)\n\n", R);
    
    fprintf(fp, "\tOutput parameters:\n");
    
    //  Profile (Two Temperature columns (K and deg C))
    fprintf(fp, "P (kPa)\tV (m3)\tT (K)\tT(deg C)\t\tQ (kW)\tQ (kW)\n");
    for(int i = 0; i < 250; ++i)
    {
        fprintf(fp, "%f\t", profile.P[i]*0.001);
        fprintf(fp, "%f\t", profile.V[i]);
        fprintf(fp, "%f\t", profile.T[i]);
        fprintf(fp, "%f\t\t", profile.T[i] - 273.15);
        fprintf(fp, "%f\t", profile.Q[i]*0.001);
        total += profile.Q[i]*0.001;
        fprintf(fp, "%f\n", total);
    }
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void IsocProcSwitch(int mode, double P1, double P2, double V, double T1, double T2, double n, double c_v, T1ThermoProf profile)
{
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        char input[maxstrlen];
        
        if(mode == 1){
            printf("Do you want to display the results? ");
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
                    IsocProcDisplay(P1, P2, V, T1, T2, n, c_v, profile);
                }
                if(mode == 2){
                    IsocProcWrite(P1, P2, V, T1, T2, n, c_v, profile);
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
void Isochoric()
{
    //Main Function
    int whilmain = 1;
    printf("Isochoric Process\n");
    
    while(whilmain == 1)
    {
        //Variable declaration
        char methodinput[maxstrlen];    // Variable used to store character input.
        int method = 0;                 // Variable used to control subroutine behaviour.
        int whilmethod = 0;             // Variable used to control user input.
        int elems = 0;                  // Variable used to store the total number of elements used in the profile struct.
        
        elems = 5*250;
        
        T1ThermoProf *profile = calloc(elems, sizeof(double));   // Struct used to store the generated isochoric profile.
        
        double P1 = 0.0;                // Initial system pressure.
        double P2 = 0.0;                // Final system pressure.
        double V = 0.0;                 // System volume.
        double T1 = 0.0;                // Initial system temperature.
        double T2 = 0.0;                // Final system temperature.
        double n = 0.0;                 // Moles of component in system.
        double cv = 0.0;                // Heat capacity at constant volume.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //Data Collection
        whilmethod = 1;
        while(whilmethod == 1)
        {
            printf("Please select from the following calculation methods:\n1. Pressure\n2. Temperature\n");
            printf("Selection [1 - 2]: ");
            fgets(methodinput, sizeof(methodinput), stdin);
            switch(methodinput[0])
            {
                case '1':
                case 'P':
                case 'p':
                    //code
                    method  = 1;
                    whilmethod = 0;
                    break;
                case '2':
                case 'T':
                case 't':
                    //code
                    method = 2;
                    whilmethod = 0;
                    break;
                case 'Q':
                case 'q':
                case '0':
                    whilmethod = 0;
                    whilmain = 0;
                    break;
                default:
                    printf("Invalid input, please try again");
                    break;
            }
        }
        if(method == 1 || method == 2){
            //  Data collection
            IsocVariable(method, &P1, &P2, &V, &T1, &T2, &n, &cv);
            
            //  Running calculations
            clock_getres(CLOCK_MONOTONIC, &start);
            clock_gettime(CLOCK_MONOTONIC, &start);
            
            *profile = IsocProfile(method, P1, P2, V, T1, T2, n, cv);
            
            clock_getres(CLOCK_MONOTONIC, &end);
            clock_gettime(CLOCK_MONOTONIC, &end);

            elapsed = timer(start, end);

            printf("Calculations completed in %.6f seconds.\n", elapsed);
            
            //  Displaying results
            IsocProcSwitch(1, P1, P2, V, T1, T2, n, cv, *profile);
            
            //  Writing to File
            IsocProcSwitch(2, P1, P2, V, T1, T2, n, cv, *profile);
            free(profile);
        }
        //Continue function
        whilmain = Continue(whilmain);
    }
}
