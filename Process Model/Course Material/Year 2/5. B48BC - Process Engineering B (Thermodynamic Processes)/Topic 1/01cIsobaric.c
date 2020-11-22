//
//  01cIsobaric.c
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
#include "01cIsobaric.h"
#include "IdealGasLaw.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define R 8.3145

/// MARK: VARIABLE INPUT
void IsobVariable(int method, double *P, double *V1,double *V2, double *T1, double *T2, double *n)
{
    if(method == 1){
        *P = inputDouble(0, 0, "system pressure", "kPa");
        *P = (*P)*1000;
        
        *V1 = inputDouble(0, 0, "initial system volume", "m3");
        
        *V2 = inputDouble(0, 0, "final system volume", "m3");
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
    }
}

/// MARK: GENERAL CALCULATION
double IsobVolume(double P, double V1, double V2)
{
    double work = 0.0;
    
    work = V2 - V1;
    work = P*(work);
    
    return work;
}

double IsobTemperature(double n, double T1, double T2)
{
    double work = 0.0;
    
    work = T2 - T1;
    work = R*(work);
    work = n*(work);
    work = -1 *(work);
    
    work = -1*(work);
    
    return work;
}

double IsobFinalTemperature(double V1, double V2, double T1)
{
    double T2 = 0.0;
    
    T2 = V2/V1;
    T2 = (T2)*T1;
    
    return T2;
}

/// MARK: ARRAY FUNCTION
T1ThermoProf IsobProfile(int method, double P, double V1, double V2, double T1, double T2, double n)
{
    double incr = 0.0;  // Increment between data points
    int reso = 0;       // Resolution of generated plot
    int i = 0;          // Row controller
    
    T1ThermoProf profile = {0.0};
    double total = 0.0;
    
    reso = 249;
    
    if(method == 1){
        incr = V2 - V1;
        incr = (incr)/reso;
    }
    if(method == 2){
        incr = T2 - T1;
        incr = (incr)/reso;
    }
    
    // Setting initial system conditions
    i = 0;
    if(method == 1){
        profile.P[i] = P;
        profile.V[i] = V1;
        profile.T[i] = IdealTemperature(n, profile.P[i], profile.V[i]);
    }
    if(method == 2){
        profile.P[i] = 0.0;
        profile.V[i] = 0.0;
        profile.T[i] = T1;
    }
    profile.W_V[i] = 0.0;
    
    for(i = 1; i < (reso + 1); ++i)
    {
        if(method == 1){
            profile.P[i] = P;
            profile.V[i] = profile.V[i - 1] + incr;
            profile.T[i] = IsobFinalTemperature(profile.V[i - 1], profile.V[i], profile.T[i - 1]);
            profile.W_V[i] = IsobVolume(profile.P[i], profile.V[i-1], profile.V[i]);
            total = total + profile.W_V[i];
        }
        if(method == 2){
            profile.P[i] = 0.0;
            profile.V[i] = 0.0;
            profile.T[i] = profile.T[i - 1] + incr;
            profile.W_V[i] = IsobTemperature(n, profile.T[i - 1], profile.T[i]);
            total = total + profile.W_V[i];
        }
    }
    
    if(method == 1 || method == 2){
        printf("Total Volume work done = %.3f kW\n", total*0.001);
        printf("Profile calculated in %d rows\n\n", i);
    }
    return profile;
}

/// MARK: DISPLAY AND WRITE
void IsobProcDisplay(double P, double V1, double V2, double T1, double T2, double n, T1ThermoProf profile)
{
    double total = 0.0;
    
    printf("_Isobaric_Process_Results_\n");
    printf("\tInput parameters:\n");
    printf("System pressure:\n");
    printf("P =\t%.3f\tkPa\n\n", P*0.001);
    
    printf("Initial system volume:\n");
    printf("V1 =\t%.3f\tm3\n", V1);
    printf("Final system volume:\n");
    printf("V2 =\t%.3f\tm3\n\n", V2);
    
    printf("Initial system temperature:\n");
    printf("T1 =\t%.3f\tdeg C\n", T1-273.15);
    printf("Final system volume:\n");
    printf("T2 =\t%.3f\tdeg C\n\n", T2-273.15);
    
    printf("_System-Specific_parameters:_\n");
    
    printf("Molar flowrate of component i:\n");
    printf("n =\t%.3f\tkmol/s\n", n*0.001);
    printf("R =\t%.4f\tJ/(mol. K)\n\n", R);
    
    printf("\tOutput parameters:\n");
    
    // Profile (Two Temperature columns (K and deg C))
    printf("P (kPa)\tV (m3)\tT (K)\tT(deg C)\t\tW_V (kW)\tW_V (kW)\n");
    for(int i = 0; i < 250; ++i)
    {
        printf("%f\t", profile.P[i]*0.001);
        printf("%f\t", profile.V[i]);
        printf("%f\t", profile.T[i]);
        printf("%f\t\t", profile.T[i] - 273.15);
        printf("%f\t", profile.W_V[i]*0.001);
        total += profile.W_V[i]*0.001;
        printf("%f\n", total);
    }
    fflush(stdout);
}

void IsobProcWrite(double P, double V1, double V2, double T1, double T2, double n, T1ThermoProf profile)
{
    //  Function variables
    char filename[maxstrlen];
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //  Set file name as timestamp + Isobaric Process Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Isobaric Results");
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
    
    fprintf(fp, "_Isobaric_Process_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "System pressure:\n");
    fprintf(fp, "P =\t%.3f\tkPa\n\n", P*0.001);
    
    fprintf(fp, "Initial system volume:\n");
    fprintf(fp, "V1 =\t%.3f\tm3\n", V1);
    fprintf(fp, "Final system volume:\n");
    fprintf(fp, "V2 =\t%.3f\tm3\n\n", V2);
    
    fprintf(fp, "Initial system temperature:\n");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n", T1-273.15);
    fprintf(fp, "Final system temperature:\n");
    fprintf(fp, "T2 =\t%.3f\tdeg C\n\n", T2-273.15);
    
    fprintf(fp, "_System-Specific_parameters:_\n");
    
    fprintf(fp, "Molar flowrate of component i:\n");
    fprintf(fp, "n =\t%.3f\tkmol/s\n", n*0.001);
    fprintf(fp, "R =\t%.4f\tJ/(mol. K)\n\n", R);
    
    fprintf(fp, "\tOutput parameters:\n");
    
    //  Profile (Two Temperature columns (K and deg C))
    fprintf(fp, "P (kPa)\tV (m3)\tT (K)\tT(deg C)\t\tW_V (kW)\tW_V (kW)\n");
    for(int i = 0; i < 250; ++i)
    {
        fprintf(fp, "%f\t", profile.P[i]*0.001);
        fprintf(fp, "%f\t", profile.V[i]);
        fprintf(fp, "%f\t", profile.T[i]);
        fprintf(fp, "%f\t\t", profile.T[i] - 273.15);
        fprintf(fp, "%f\t", profile.W_V[i]*0.001);
        total += profile.W_V[i]*0.001;
        fprintf(fp, "%f\n", total);
    }
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void IsobProcSwitch(int mode, double P, double V1, double V2, double T1, double T2, double n, T1ThermoProf profile)
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
                    IsobProcDisplay(P, V1, V2, T1, T2, n, profile);
                }
                if(mode == 2){
                    IsobProcWrite(P, V1, V2, T1, T2, n, profile);
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
void Isobaric()
{
    //Main Function
    int whilmain = 0;
    printf("Isobaric Process\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
        char methodinput[maxstrlen];    // Variable used to store character input.
        int method = 0;                 // Variable used to control subroutine behaviour.
        int whilmethod = 0;             // Variable used to control user input.
        int elems = 0;                  // Variable used to store the total number of elements used in the profile struct.
        
        elems = 5*250;
        
        T1ThermoProf *profile = calloc(elems, sizeof(double));   // Struct used to store the generated isobaric process profile.
        
        double P = 0.0;                 // System pressure.
        double V1 = 0.0;                // Initial system volume.
        double V2 = 0.0;                // Final system volume.
        double T1 = 0.0;                // Initial system temperature.
        double T2 = 0.0;                // Final system temperature.
        double n = 0.0;                 // Moles of component present in system.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        whilmethod = 1;
        while(whilmethod == 1)
        {
            printf("Please select from the following calculation methods:\n1. Pressure-Volume\n2. Temperature\n");
            printf("Selection [1 - 2]: ");
            fgets(methodinput, sizeof(methodinput), stdin);
            switch(methodinput[0])
            {
                case '1':
                case 'V':
                case 'v':
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
            IsobVariable(method, &P, &V1, &V2, &T1, &T2, &n);
            
            //  Running calculations
            clock_getres(CLOCK_MONOTONIC, &start);
            clock_gettime(CLOCK_MONOTONIC, &start);
            
            *profile = IsobProfile(method, P, V1, V2, T1, T2, n);
            
            clock_getres(CLOCK_MONOTONIC, &end);
            clock_gettime(CLOCK_MONOTONIC, &end);

            elapsed = timer(start, end);

            printf("Calculations completed in %.6f seconds.\n", elapsed);
            
            //  Displaying results
            IsobProcSwitch(1, P, V1, V2, T1, T2, n, *profile);
            
            //  Writing to File
            IsobProcSwitch(2, P, V1, V2, T1, T2, n, *profile);
            free(profile);
        }
        //Continue function
        whilmain = Continue(whilmain);
        fflush(stdout);
    }
}
