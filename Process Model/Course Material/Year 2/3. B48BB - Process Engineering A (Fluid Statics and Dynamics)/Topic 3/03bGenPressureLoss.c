//
//  03bGenPressureLoss.c
//  Process Model
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
#include "DimensionlessNum.h"
#include "B48BB_T3.h"
#include "03bGenPressureLoss.h"
#include "03aFrictFactor.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void PressLossVariable(double *rho, double *u, double *d, double *mu, double *L, double *vareps)
{
    *rho = inputDouble(0, 0, "fluid density", "kg/m3");
    
    *u = inputDouble(0, 0, "fluid velocity", "m/s");
    
    *mu = inputDouble(0, 0, "fluid viscosity", "cP");
    *mu = (*mu) * 0.001;
    
    *d = inputDouble(0, 0, "internal pipe diameter", "mm");
    *d = (*d) * 0.001;
    
    *L = inputDouble(0, 0, "pipe length", "m");
    
    if(ReynoldsNum(*rho, *u, *d, *mu) > 2500){
        *vareps = inputDouble(0, 0, "pipe absolute roughness", "mm");
        *vareps = (*vareps) * 0.001;
    }else{ 
        *vareps = 0.0;
    }
    fflush(stdout);
}

/// MARK: PRELIMINARY CALCULATION
double phiCalculation(double rho, double u, double d, double mu, double vareps)
{
    char menu[maxstrlen];
    
    double ReyNum = 0.0;
    double phi = 0.0;
    
    double phiTurb1 = 0.0;
    double phiTurb2 = 0.0;
    double phiTurb3 = 0.0;
    
    int roughcheck = 0;
    
    ReyNum = ReynoldsNum(rho, u, d, mu);
    
    if(ReyNum < 2000){
        phi = Laminar(rho, u, d, mu);
    }else{
        if(ReyNum < 2500){
            printf("2000 < Re < 2500: Correlations are unavailable. Assuming laminar friction factor.\n");
            phi = Laminar(rho, u, d, mu);
        }else{
            roughcheck = 1;
            while(roughcheck == 1){
                printf("Is the friction factor independent of Reynolds number? [Y/N] ");
                fgets(menu, sizeof(menu), stdin);
                switch(menu[0]){
                    case '1':
                    case 'T':
                    case 'Y':
                    case 't':
                    case 'y':
                        d = d*1000;
                        vareps = vareps*1000;
                        phi = Turbulent4(d, vareps);
                        roughcheck = 0;
                        break;
                    case '0':
                    case 'F':
                    case 'N':
                    case 'f':
                    case 'n':
                        phiTurb1 = Turbulent1(rho, u, d, mu);
                        phiTurb2 = Turbulent2(rho, u, d, mu);
                        phiTurb3 = Turbulent3(rho, u, d, mu, vareps);
                        
                        if(phiTurb1 > phiTurb2 && phiTurb1 > phiTurb3)
                        {
                            printf("Turbulent1(...) provides the highest friction factor\n");
                            phi = phiTurb1;
                            vareps = 0.0;
                        }else{
                            if(phiTurb2 > phiTurb3){
                                printf("Turbulent2(...) provides the highest friction factor\n");
                                phi = phiTurb2;
                                vareps = 0.0;
                            }else{
                                printf("Turbulent3(...) provides the highest friction factor\n");
                                phi = phiTurb3;
                            }
                        }
                        roughcheck = 0;
                        break;
                    default:
                        printf("Invalid input, please try again\n");
                        break;
                }
            }
        }
    }
    fflush(stdout);
    return phi;
}

/// MARK: GENERAL CALCULATION
double LossCalculation(double phi, double L, double d, double rho, double u)
{
    double frac1 = 0.0;
    double frac2 = 0.0;
    double dP = 0.0;
    
    frac1 = L/d;
    
    frac2 = pow(u, 2);
    frac2 = rho*(frac2);
    frac2 = (frac2)/(2.0);
    
    dP = 8*phi;
    dP = (dP)*frac1;
    dP = (dP)*frac2;
    
    return dP;
}

/// MARK: DISPLAY AND WRITE
void PressLossDisplay(double rho, double u, double d, double mu, double L, double vareps, double phi, double dP)
{
    printf("_Pressure_Loss_Equation_Results_\n");
    printf("\tInput parameters:\n");
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n", rho);
    printf("Fluid velocity:\n");
    printf("u =\t%.3f\tm/s\n", u);
    printf("Fluid viscosity:\n");
    printf("mu =\t%.3f\tcP\n\n", mu*1000);
    
    printf("Pipe diameter:\n");
    printf("d =\t%.3f\tmm\n", d*1000);
    printf("Pipe length:\n");
    printf("L =\t%.3f\tm\n", L);
    if(vareps == 0.0){
        printf("Pipe absolute roughness not used\n\n");
    }else{
        printf("Pipe absolute roughness:\n");
        printf("vareps =\t%.3f\tmm\n\n", vareps*1000);
    }
    
    printf("\tIntermediate parameters:\n");
    printf("Friction factor:\n");
    printf("phi =\t%.3f\t[]\n\n", phi);
    
    printf("\tOutput parameters:\n");
    printf("Fluid pressure loss:\n");
    printf("dP =\t%.3f\tPa\n", dP);
    fflush(stdout);
}

void PressLossWrite(double rho, double u, double d, double mu, double L, double vareps, double phi, double dP)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Pressure Loss Equation Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Pressure Loss Equation Results");
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
    fprintf(fp, "_Pressure_Loss_Equation_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Fluid density:\n");
    fprintf(fp, "rho =\t%.3f\tkg/m3\n", rho);
    fprintf(fp, "Fluid velocity:\n");
    fprintf(fp, "u =\t%.3f\tm/s\n", u);
    fprintf(fp, "Fluid viscosity:\n");
    fprintf(fp, "mu =\t%.3f\tPa.s\n\n", mu);
    
    fprintf(fp, "Pipe diameter:\n");
    fprintf(fp, "d =\t%.3f\tmm\n", d*1000);
    fprintf(fp, "Pipe length:\n");
    fprintf(fp, "L =\t%.3f\tm\n", L);
    if(vareps == 0.0){
        fprintf(fp, "Pipe absolute roughness not used\n\n");
    }else{
        fprintf(fp, "Pipe absolute roughness:\n");
        fprintf(fp, "vareps =\t%.3f\tmm\n\n", vareps*1000);
    }
    
    fprintf(fp, "\tIntermediate parameters:\n");
    fprintf(fp, "Friction factor:\n");
    fprintf(fp, "phi =\t%.3f\t[]\n", phi);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Fluid pressure loss:\n");
    fprintf(fp, "dP =\t%.3f\tPa\n", dP);
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void PressLossWriteSwitch(double rho, double u, double d, double mu, double L, double vareps, double phi, double dP)
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
                PressLossWrite(rho, u, d, mu, L, vareps, phi, dP);
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
void GeneralPressureLoss()
{
    //  Pseudo-main function.
    int whilmain = 1;
    printf("General Pressure Loss\n");
    
    while(whilmain == 1)
    {
        //  Variable declaration
        double phi = 0.0;   // Friction factor.
        double dP = 0.0;    // Frictional pressure loss.
        
        double rho = 0.0;   // Fluid density.
        double u = 0.0;     // Fluid velocity.
        double d = 0.0;     // Internal pipe diameter.
        double mu = 0.0;    // Fluid viscosity.
        double L = 0.0;     // Pipe length.
        double vareps = 0.0;// Absolute surface roughness of pipe.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data collection
        PressLossVariable(&rho, &u, &d, &mu, &L, &vareps);
        
        //  Running calculations
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        phi = phiCalculation(rho, u, d, mu, vareps);
        dP = LossCalculation(phi, L, d, rho, u);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        PressLossDisplay(rho, u, d, mu, L, vareps, phi, dP);
        
        //  Writing to File
        PressLossWriteSwitch(rho, u, d, mu, L, vareps, phi, dP);
        
        //Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
