//
//  03bForcedFlatPlate.c
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

/// MARK: HEADER DECLARATIONS
//Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Custom Header Files
#include "System.h"
#include "DimensionlessNum.h"
#include "03bFilmHTCoefficient.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void ForcedPlateVariable(double *rho, double *mu, double *cp, double *k, double *u, double *d)
{
    printf("Fluid properties:\n");
    *rho = inputDouble(0, 0, "fluid density", "kg/m3");
    *u = inputDouble(0, 0, "fluid velocity", "m/s");
    *mu = inputDouble(0, 0, "fluid viscosity", "cP");
    *mu = 0.001*(*mu);  // Conversion (cP -> Pa.s)
    
    printf("\nThermal properties:\n");
    *cp = inputDouble(0, 0, "heat capacity at constant pressure", "J/(kg.K)");
    *k = inputDouble(0, 0, "fluid thermal conductivity", "W/m.K");
    
    printf("\nPhysical properties:\n");
    *d = inputDouble(0, 0, "pipe internal diameter", "mm");
    *d = 0.001*(*d);
}

/// MARK: GENERAL CALCULATIONS
double ForcedHTCoefficientPlateLam(double Re, double Pr, double k, double d, double *Nusselt)
{
    double Nu = 0.0;
    double result = 0.0;
    double sto = 0.0;
    
    sto = (1.0)/(3.0);
    Nu = pow(Pr, sto);
    sto = pow(Re, 0.5);
    Nu *= (sto);
    
    if(Pr > 0.6)
    {
        Nu *= 0.664;
    }
    if(Pr <= 0.6)
    {
        Nu *= 0.332;
    }
    *Nusselt = Nu;
    
    result = (Nu)*k;
    result /= d;
    
    return result;
}

double ForcedHTCoefficientPlateTrans(double Re, double Pr, double k, double d, double *Nusselt)
{
    double Nu = 0.0;
    double result = 0.0;
    double sto = 0.0;
    
    sto = (1.0)/(3.0);
    Nu = pow(Pr, sto);
    sto = pow(Re, 0.8);
    sto -= 871;
    Nu *= (sto);
    
    *Nusselt = Nu;
    
    result = (Nu)*k;
    result /= d;
    
    return result;
}

double ForcedHTCoefficientPlateTur(double Re, double Pr, double k, double d, double *Nusselt)
{
    double Nu = 0.0;
    double result = 0.0;
    double sto = 0.0;
    
    sto = (1.0)/(3.0);
    Nu = pow(Pr, sto);
    sto = pow(Re, 0.8);
    Nu *= sto;
    
    if(Pr > 0.6 && Pr < 60){
        Nu *= 0.0366;
    }else{
        Nu *= 0.0296;
    }
    *Nusselt = Nu;
    
    result = (Nu)*k;
    result /= d;
    
    return result;
}

/// MARK: DISPLAY AND WRITE
void PlateHTCoeffDisplay(int eqnset, double rho, double u, double mu, double cp, double k, double d, double Re, double Pr, double Nu, double h)
{
    printf("_Film_Heat_Transfer_Coefficient_Estimation_\n");
    printf("\tInput parameters:\n");
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n", rho);
    printf("Fluid velocity:\n");
    printf("u =\t%.3f\tm/s\n", u);
    printf("Fluid viscosity:\n");
    printf("mu =\t%.3f\tcP\n\n", 1000*mu);
    
    printf("Fluid heat capacity at constant pressure:\n");
    printf("cp =\t%.3f\tJ/kg.K\n", cp);
    printf("Fluid thermal conductivity:\n");
    printf("k =\t%.3f\tW/m.K\n\n", k);
    
    printf("\tIntermediate parameters:\n");
    printf("Reynolds number:\n");
    printf("Re =\t%.3f\t[ ]\n", Re);
    printf("Prandtl number:\n");
    printf("Pr =\t%.3f\t[ ]\n", Pr);
    printf("Nusselt number:\n");
    printf("Nu =\t%.3f\t[ ]\n\n", Nu);
    
    printf("\tOutput parameters:\n");
    if(eqnset == 1)
    {
        if(Pr > 0.6){
            printf("Nu = 0.664Re^{0.5}Pr^{1/3}\n");
        }
        if(Pr <= 0.6){
            printf("Nu = 0.332Re^{0.5}Pr^{1/3}\n");
        }
    }
    if(eqnset == 2)
    {
        printf("Nu = 0.037(Re^{0.8} - 871)Pr^{1/3}\n");
        if(Pr > 0.6 && Pr < 60){
            // Correlation is valid
        }else{
            printf("Correlation condition is being violated. (0.6 < Pr < 60).\n\n");
        }
    }
    if(eqnset == 3)
    {
        if(Pr > 0.6 && Pr < 60){
            printf("Nu = 0.037Re^{0.8}Pr^{1/3}\n");
        }else{
            printf("Nu = 0.0296Re^{0.8}Pr^{1/3}\n");
        }
    }
    printf("Fluid heat transfer coefficient:\n");
    printf("h =\t%.3f\tW/m2.K\n", h);
}

void PlateHTCoeffWrite(int eqnset, double rho, double u, double mu, double cp, double k, double d, double Re, double Pr, double Nu, double h)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Fluid heat transfer coefficient (Forced Convection over a flat plate) Estimation
        //Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //Creating file name with base format "YYYYmmDD HHMMSS "
    //Allocating memory for the file name
    *filename = (char)malloc(sizeof *filename);
    
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Fluid heat transfer coefficient (Forced Convection over a flat plate) Estimation");
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
        strcat(filepath, filename);
    }
    */
    printf("Note that write sequence may be disabled by zsh\n");
    
    printf("Beginning file write...\n");
    
    //Open file
    fp = fopen(filename, "w+");
    
    //Write to file
    fprintf(fp, "_Film_Heat_Transfer_Coefficient_Estimation_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Fluid density:\n");
    fprintf(fp, "rho =\t%.3f\tkg/m3\n", rho);
    fprintf(fp, "Fluid velocity:\n");
    fprintf(fp, "u =\t%.3f\tm/s\n", u);
    fprintf(fp, "Fluid viscosity:\n");
    fprintf(fp, "mu =\t%.3f\tcP\n\n", 1000*mu);
    
    fprintf(fp, "Fluid heat capacity at constant pressure:\n");
    fprintf(fp, "cp =\t%.3f\tJ/kg.K\n", cp);
    fprintf(fp, "Fluid thermal conductivity:\n");
    fprintf(fp, "k =\t%.3f\tW/m.K\n\n", k);
    
    fprintf(fp, "Pipe internal diameter:\n");
    fprintf(fp, "d =\t%.3f\tmm\n\n", 1000*d);
    
    fprintf(fp, "\tIntermediate parameters:\n");
    fprintf(fp, "Reynolds number:\n");
    fprintf(fp, "Re =\t%.3f\t[ ]\n", Re);
    fprintf(fp, "Prandtl number:\n");
    fprintf(fp, "Pr =\t%.3f\t[ ]\n", Pr);
    fprintf(fp, "Nusselt number:\n");
    fprintf(fp, "Nu =\t%.3f\t[ ]\n\n", Nu);
    
    fprintf(fp, "\tOutput parameters:\n");
    if(eqnset == 1)
    {
        if(Pr > 0.6){
            fprintf(fp, "Nu = 0.664Re^{0.5}Pr^{1/3}\n");
        }
        if(Pr <= 0.6){
            fprintf(fp, "Nu = 0.332Re^{0.5}Pr^{1/3}\n");
        }
    }
    if(eqnset == 2)
    {
        fprintf(fp, "Nu = 0.037(Re^{0.8} - 871)Pr^{1/3}\n");
        if(Pr > 0.6 && Pr < 60){
            // Correlation is valid
        }else{
            fprintf(fp, "Correlation condition is being violated. (0.6 < Pr < 60).\n\n");
        }
    }
    if(eqnset == 3)
    {
        if(Pr > 0.6 && Pr < 60){
            fprintf(fp, "Nu = 0.037Re^{0.8}Pr^{1/3}\n");
        }else{
            fprintf(fp, "Nu = 0.0296Re^{0.8}Pr^{1/3}\n");
        }
    }
    fprintf(fp, "Fluid heat transfer coefficient:\n");
    fprintf(fp, "h =\t%.3f\tJ/m2.K\n", h);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void PlateHTCoeffWriteSwitch(int eqnset, double rho, double u, double mu, double cp, double k, double d, double Re, double Pr, double Nu, double h)
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
                PlateHTCoeffWrite(eqnset, rho, u, mu, cp, k, d, Re, Pr, Nu, h);
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
void ForcedFlatPlate(void)
{
    printf("Forced convection over a flat plate\n");
    
    //  Variable declaration
    double ReyCond = 0.0;
    int eqnset = 0;
    
    double Re = 0.0;    // Reynolds number.
    double Pr = 0.0;    // Prandtl number.
    double Nu = 0.0;    // Nusselt number.
    double h = 0.0;     // Film heat transfer coefficient.
    
    double rho = 0.0;   // Fluid density.
    double mu = 0.0;    // Fluid viscosity.
    double cp = 0.0;    // Fluid heat capacity at constant pressure.
    double k = 0.0;     // Thermal conductivity.
    double u = 0.0;     // Fluid velocity.
    double d = 0.0;     // Internal pipe diameter.
        //  Variables for timing function
    struct timespec start, end;
    double elapsed = 0.0;
    
    //  Data Collection
    ForcedPlateVariable(&rho, &mu, &cp, &k, &u, &d);
    
    //  Data Manipulation
    clock_getres(CLOCK_MONOTONIC, &start);
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Calculation function(s)
    Re = ReynoldsNum(rho, u, d, mu);
    Pr = PrandtlNum(cp, mu, k);
    ReyCond = pow(10, 5);
    ReyCond *= 5;
    
    if(Re == ReyCond)
    {
        h = ForcedHTCoefficientPlateTrans(Re, Pr, k, d, &Nu);
        eqnset = 2;
    }else{
        if(Re < ReyCond){
            h = ForcedHTCoefficientPlateLam(Re, Pr, k, d, &Nu);
            eqnset = 1;
        }
        if(Re > ReyCond){
            h = ForcedHTCoefficientPlateTur(Re, Pr, k, d, &Nu);
            eqnset = 3;
        }
    }
    
    clock_getres(CLOCK_MONOTONIC, &end);
    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed = timer(start, end);

    printf("Calculations completed in %.6f seconds.\n", elapsed);
    
    //  Displaying results
    PlateHTCoeffDisplay(eqnset, rho, u, mu, cp, k, d, Re, Pr, Nu, h);
    
    //  Writing to File
    PlateHTCoeffWriteSwitch(eqnset, rho, u, mu, cp, k, d, Re, Pr, Nu, h);
    
    fflush(stdout);
}
