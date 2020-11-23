//
//  01aPolytropic.c
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
//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Custom header files
#include "System.h"
#include "B48BC_T1.h"
#include "01aPolytropic.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void PolyVariable(int method, double *P1, double *P2, double *V1, double *T1,double *T2, double *n, double *R, double *alpha)
{
    if(method == 2){
        *T1 = inputDouble(1, 1, "initial system semperature", "deg C");
        *T1 = (*T1) + 273.15;
    }
    if(method == 2){
        *T2 = inputDouble(1, 1, "final system temperature", "deg C");
        *T2 = (*T2) + 273.15;
    }
    if(method == 2 && fabs(*T2 - *T1) < 0.005){
        printf("You have stated an isothermal process. Changing to the Pressure-Volume equation.\n\n");
        method = 1;
    }
    if(method == 1){
        *P1 = inputDouble(0, 0, "initial system pressure", "kPa");
        *P1 = (*P1)*1000;
        
        *P2 = inputDouble(0, 0, "final system pressure", "kPa");
        *P2 = (*P2)*1000;
        
        *V1 = inputDouble(0, 0, "initial system volume", "m3");
    }
    if(method == 1 || method == 2){
        *n = inputDouble(0, 0, "molar flowrate", "kmol/s");
        *n = (*n)*1000;
        
        *R = inputDouble(0, 0, "gas constant (R)", "(kJ/(kmol.K))");
        
        *alpha = inputDouble(0, 0, "polytropic index", "[ ]");
    }
}

/// MARK: GENERAL CALCULATIONS
double PolyVolume(double P1, double P2, double V1, double alpha)
{
    double power = 0.0;
    double brack = 0.0;
    double fracnum = 0.0;
    double fracden = 0.0;
    double work = 0.0;
    
    power = alpha - 1;
    power = (power)/alpha;
    
    brack = P2/P1;
    brack = pow(brack, power);
    brack = 1 - (brack);
    
    fracnum = P1*V1;
    fracden = alpha - 1;
    
    work = fracnum/fracden;
    work = (work)*brack;
    work = -1*(work);
    
    return work;
}

double PolyTemperature(double n, double R, double T1, double T2, double alpha)
{
    double brack = 0.0;
    double fracnum = 0.0;
    double fracden = 0.0;
    double work = 0.0;
    
    brack = T2/T1;
    brack = (brack) - 1;
    
    fracnum = n*R;
    fracnum = (fracnum)*T1;
    fracden = alpha - 1;
    
    work = fracnum/fracden;
    work = (work)*brack;
    
    return work;
}

double PolyFinalVolume(double P1, double P2, double V1, double alpha)
{
    double logfrac = 0.0;
    double frac = 0.0;
    double V2 = 0.0;
    
    logfrac = pow(V1, alpha);
    logfrac = P1*(logfrac);
    logfrac = (logfrac)/P2;
    logfrac = log(logfrac);
    
    frac = (logfrac)/alpha;
    
    V2 = exp(frac);
    
    return V2;
}

double PolyFinalPressure(double T1, double T2, double P1, double alpha)
{
    double power = 0.0;
    double logfrac = 0.0;
    double frac = 0.0;
    double P2 = 0.0;
    
    power = 1.0 - alpha;
    power = (power)/alpha;
    
    logfrac = pow(P1, power);
    logfrac = T1*(logfrac);
    logfrac = (logfrac)/T2;
    logfrac = log(logfrac);
    
    frac = (logfrac)/(power);
    
    P2 = exp(frac);
    
    return P2;
}

double PolyFinalTemperature(double T1, double P1, double P2, double alpha)
{
    double T2 = 0.0;
    double power = 0.0;
    double frac = 0.0;
    
    power = 1 - alpha;
    power = (power)/alpha;
    
    frac = P1/P2;
    
    T2 = pow(frac, power);
    T2 = T1 * (T2);
    
    return T2;
}

/// MARK: ARRAY FUNCTION
T1ThermoProf PolyProfile(int method, double P1, double P2, double V1, double T1, double T2, double n, double R, double alpha)
{
    double incr = 0.0;  // Increment between data points
    int reso = 0;       // Resolution of generated plot
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
    
    i = 0;
    if(method == 1){
        // Pressure and volume must be stated
        double Tnum = 0.0;
        double Tden = 0.0;
        
        profile.P[i] = P1;
        profile.V[i] = V1;
        
        Tnum = (profile.P[i])*(profile.V[i]);
        Tden = n*R;
        profile.T[i] = Tnum/Tden;
    }
    if(method == 2){
        // Temperature must be known. Not enough information is given to calculate the system pressure or volume
        printf("Assuming Ideal Gas Law applies\n\n");
        profile.P[i] = 0.0;
        profile.V[i] = 0.0;
        profile.T[i] = T1;
    }
    profile.W_V[i] = 0.0;
    
    for(i = 1; i < (reso + 1); ++i)
    {
        if(method == 1){
            double Tnum = 0.0;
            double Tden = 0.0;
            
            profile.P[i] = profile.P[i-1] + incr;
            profile.V[i] = PolyFinalVolume(profile.P[i-1], profile.P[i], profile.V[i-1], alpha);
            
            Tnum = (profile.P[i])*(profile.V[i]);
            Tden = n*R;
            profile.T[i] = Tnum/Tden;
            
            profile.W_V[i] = PolyVolume(profile.P[i-1], profile.P[i], profile.V[i-1], alpha);
            total = total + profile.W_V[i];
        }
        if(method == 2){
            profile.P[i] = 0.0;
            profile.V[i] = 0.0;
            profile.T[i] = profile.T[i - 1] + incr;
            profile.W_V[i] = PolyTemperature(n, R, profile.T[i - 1], profile.T[i], alpha);
            total = total + profile.W_V[i];
        }
    }
    
    printf("Total Volume work done = %.3f kW\n", total*0.001);
    printf("Profile calculated in %d rows\n\n", i);
    
    fflush(stdout);
    return profile;
}

/// MARK: DISPLAY AND WRITE
void PolyProcDisp(double P1, double P2, double V1, double V2, double T1, double T2, double n, double R, double alpha, T1ThermoProf profile)
{
    char input[maxstrlen];
    
    double total = 0.0;
    
    int control = 0;        // Variable used to force character input.
    
    printf("_Polytropic_Process_Results_\n");
    printf("\tInput parameters:\n");
    printf("Initial system pressure:\n");
    printf("P1 =\t%.3f\tkPa\n", P1*0.001);
    printf("Final system pressure:\n");
    printf("P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    printf("Initial system volume:\n");
    printf("V1 =\t%.3f\tm3\n", V1);
    printf("Final system volume:\n");
    printf("V2 =\t%.3f\tm3\n\n", V2);
    
    printf("Initial system temperature:\n");
    printf("T1 =\t%.3f\tdeg C\n", T1-273.15);
    printf("Final system temperature:\n");
    printf("T2 =\t%.3f\tdeg C\n\n", T2-273.15);
    
    printf("_System-Specific_parameters:_\n");
    
    printf("Molar flowrate of component i:\n");
    printf("n =\t%.3f\tkmol/s\n", n*0.001);
    if( (fabs( R - (8.3145) ) < 0.001 && ((R >= 8.3140) || (R < 8.31449 && R < 8.31451))) ){
        printf("Universal Gas Constant:\n");
        printf("R =\t%.4f\tJ/(mol. K)\n\n", R);
    }else{
        printf("Specific Gas Constant:\n");
        printf("R =\t%.4f\tJ/(mol. K)\n\n", R);
    }
    
    printf("Polytropic Index:\n");
    printf("alpha =\t%.3f\t[ ]\n\n", alpha);
    
    control = 1;
    while(control == 1)
    {
        printf("Do you want to display the generated profile? ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
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
    fflush(stdout);
}

void PolyProcWrite(double P1, double P2, double V1, double V2, double T1, double T2, double n, double R, double alpha, T1ThermoProf profile)
{
    //  Function variables
    char filename[maxstrlen];
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //  Set file name as timestamp + Polytropic Process Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Polytropic Results");
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
    
    fprintf(fp, "_Polytropic_Process_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial system pressure:\n");
    fprintf(fp, "P1 =\t%.3f\tkPa\n", P1*0.001);
    fprintf(fp, "Final system pressure:\n");
    fprintf(fp, "P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
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
    fprintf(fp, "n =\t%.3f\tkmol/s\n\n", n*0.001);
    if( (fabs( R - (8.3145) ) < 0.001 && ((R >= 8.3140) || (R < 8.31449 && R < 8.31451))) ){
        fprintf(fp, "Universal Gas Constant:\n");
        fprintf(fp, "R =\t%.4f\tJ/(mol. K)\n\n", R);
    }else{
        fprintf(fp, "Specific Gas Constant:\n");
        fprintf(fp, "R =\t%.4f\tJ/(mol. K)\n\n", R);
    }
    
    fprintf(fp, "Polytropic Index:\n");
    fprintf(fp, "alpha =\t%.3f\t[ ]\n\n", alpha);
    
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

void PolyProcSwitch(int mode, double P1, double P2, double V1, double V2, double T1, double T2, double n, double R, double alpha, T1ThermoProf profile)
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
                    PolyProcDisp(P1, P2, V1, V2, T1, T2, n, R, alpha, profile);
                }
                if(mode == 2){
                    PolyProcWrite(P1, P2, V1, V2, T1, T2, n, R, alpha, profile);
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
void Polytropic()
{
    int whilmain = 0;
    printf("Polytropic Volume Work\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        // Variable declaration
        char input[maxstrlen];          // Variable used for character input.
        int method = 0;                 // Variable used to control subroutine behaviour.
        int whilmethod = 0;             // Variable used to control user input.
        int elems = 0;                  // Variable used to store the total number of elements used in the profile struct.
        
        elems = 5*250;
        
        T1ThermoProf *profile = calloc(elems, sizeof(double));   // Struct used to store the polytropic process profile.
        double V2 = 0.0;                // Final process volume.
        
        double P1 = 0.0;                // Initial system pressure.
        double P2 = 0.0;                // Final system pressure.
        double V1 = 0.0;                // Initial system volume.
        double T1 = 0.0;                // Initial system temperature.
        double T2 = 0.0;                // Final system temperature.
        double n = 0.0;                 // Moles of component in system.
        double R = 0.0;                 // Gas constant.
        double alpha = 0.0;             // Polytropic index.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        whilmethod = 1;
        while(whilmethod == 1)
        {
            printf("Please select from the following calculation methods:\n1. Pressure-Volume\n2. Temperature\n");
            printf("Selection [1 - 2]: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
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
        if(method == 1||method == 2){
            PolyVariable(method, &P1, &P2, &V1, &T1, &T2, &n, &R, &alpha);
            
            // Running calculations
            clock_getres(CLOCK_MONOTONIC, &start);
            clock_gettime(CLOCK_MONOTONIC, &start);
            
            *profile = PolyProfile(method, P1, P2, V1, T1, T2, n, R, alpha);
            
                //  Gathering unknown variables
            V2 = profile->V[249];
            if(method == 1){
                T1 = profile->T[0];
                T2 = profile->T[249];
            }
            if(method == 2){
                P1 = profile->P[0];
                P2 = profile->P[249];
                V1 = profile->V[0];
                V2 = profile->V[249];
            }
            clock_getres(CLOCK_MONOTONIC, &end);
            clock_gettime(CLOCK_MONOTONIC, &end);

            elapsed = timer(start, end);

            printf("Calculations completed in %.6f seconds.\n", elapsed);
            
            //  Displaying Results
            PolyProcSwitch(1, P1, P2, V1, V2, T1, T2, n, R, alpha, *profile);
            
            // Writing to File
            PolyProcSwitch(2, P1, P2, V1, V2, T1, T2, n, R, alpha, *profile);
            free(profile);
        }
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
