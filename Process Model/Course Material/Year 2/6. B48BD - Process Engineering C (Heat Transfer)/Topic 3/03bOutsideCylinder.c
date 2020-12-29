//
//  03bOutsideCylinder.c
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
void OutCylVariable(int eqn, double *rho, double *mu, double *mu_s, double *cp, double *k, double *u, double *d, double *a, double *m, double *F1, double *F2)
{
    double sto1 = 0.0;
    double sto2 = 0.0;
    
    printf("Fluid properties:\n");
    *rho = inputDouble(0, 0, "fluid density", "kg/m3");
    *u = inputDouble(0, 0, "fluid velocity", "m/s");
    *mu = inputDouble(0, 0, "fluid viscosity", "cP");
    *mu = 0.001*(*mu);  // Conversion (cP -> Pa.s)
    if(eqn == 3)
    {
        *mu_s = inputDouble(0, 0, "fluid viscosity at wall", "cP");
        *mu_s = 0.001*(*mu);  // Conversion (cP -> Pa.s)
    }
    
    printf("\nThermal properties:\n");
    *cp = inputDouble(0, 0, "heat capacity at constant pressure", "J/(kg.K)");
    *k = inputDouble(0, 0, "fluid thermal conductivity", "W/m.K");
    
    printf("\nPhysical properties:\n");
    *d = inputDouble(0, 0, "equivalent pipe diameter", "mm");
    *d = 0.001*(*d);
    
    if(eqn == 3)
    {
        printf("Correlation constants:\n");
        sto1 = ReynoldsNum(*rho, *u, *d, *mu);
        printf("Re = %.3f [ ]\n", sto1);
        
        *a = inputDouble(0, 0, "correlation constant", "");
        
    }
    if(eqn == 3 || eqn == 4)
    {
        *m = inputDouble(0, 0, "Reynolds number exponent", "");
        
    }
    if(eqn == 3)
    {
        sto1 = PrandtlNum(*cp, *mu, *k);
        sto2 = PrandtlNum(*cp, *mu_s, *k);
        sto1 /= sto2;
        *F1 = pow(sto1, 0.26);
        
        *F2 = inputDouble(0, 0, "F2", "");
        
    }
}

/// MARK: GENERAL CALCULATIONS
double OutCylHTCoeffAir(double Re, double k, double d, double *Nusselt)
{
    double result = 0.0;
    double Nu = 0.0;
    double sto = 0.0;
    
    if(Re >= 40 && Re <= 4000){
        sto = pow(Re, 0.466);
        Nu = 0.615*sto;
    }
    if(Re >= 4000 && Re <= 40000){
        sto = pow(Re, 0.618);
        Nu = 0.174*sto;
    }
    if(Re >= 40000 && Re <= 4000000){
        sto = pow(Re, 0.805);
        Nu = 0.0239*sto;
    }
    *Nusselt = Nu;
    
    result = (Nu)*k;
    result /= d;
    
    return result;
}

double OutCylHTCoeffChurchillBernstein(double Re, double Pr, double d, double k, double *Nusselt)
{
    double result = 0.0;
    double Nu = 0.0;
    double power = 0.0;
    double sto1 = 0.0;
    double sto2 = 0.0;
    double sto3 = 0.0;
    
    power = (5.0)/(8.0);
    sto1 = Re/282000;
    sto1 = pow(sto1, power);
    sto1 += 1;
    sto1 = pow(sto1, 0.8);
    Nu = sto1;
    
    power = (2.0)/(3.0);
    sto2 = 0.4/Pr;
    sto2 = pow(sto2, power);
    sto2 += 1;
    sto2 = pow(sto2, 0.25);
    power = (1.0)/(3.0);
    sto3 = pow(Pr, power);
    sto3 *= pow(Re, 0.5);
    sto3 *= 0.62;
    sto2 /= sto3;       // Value saved to sto2
    Nu *= sto2;
    
    Nu += 0.3;
    
    *Nusselt = Nu;
    
    result = (Nu)*k;
    result /= d;
    
    return result;
}

double OutCylHTCoeffGeneral(double Re, double Pr, double a, double m, double F1, double F2, double k, double d, double *Nusselt)
{
    double result = 0.0;
    double Nu = 0.0;
    double sto = 0.0;
    
    sto = (1.0)/(3.0);
    Nu = pow(Pr, sto);
    sto = pow(Re, m);
    Nu *= sto;
    Nu *= a;
    sto = F1*F2;
    Nu *= sto;
    
    *Nusselt = Nu;
    
    result = (Nu)*k;
    result /= d;
    
    return result;
}

double OutCylHTCoeffSquare(double Re, double Pr, double m, double k, double d, double *Nusselt)
{
    double result = 0.0;
    double Nu = 0.0;
    double sto = 0.0;
    
    sto = (1.0)/(3.0);
    Nu = pow(Pr, sto);
    sto = pow(Re, m);
    Nu *= sto;
    Nu *= 1.13;
    
    *Nusselt = Nu;
    
    result = (Nu)*k;
    result /= d;
    
    return result;
}

/// MARK: DISPLAY AND WRITE
void OutCylHTCoeffDisplay(int eqn, double rho, double u, double mu, double mu_s, double d, double cp, double k, double a, double m, double F1, double F2, double Re, double Pr, double Nu, double h)
{
    printf("_Film_Heat_Transfer_Coefficient_Estimation_\n");
    printf("\tInput parameters:\n");
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n", rho);
    printf("Fluid velocity:\n");
    printf("u =\t%.3f\tm/s\n", u);
    
    if(eqn == 3){
        printf("Bulk fluid viscosity:\n");
        printf("mu =\t%.3f\tcP\n", 1000*mu);
        printf("Fluid viscosity at wall:\n");
        printf("mu_s =\t%.3f\tcP\n\n", 1000*mu_s);
    }else{
        printf("Fluid viscosity:\n");
        printf("mu =\t%.3f\tcP\n\n", 1000*mu);
    }
    printf("Fluid heat capacity at constant pressure:\n");
    printf("cp =\t%.3f\tJ/kg.K\n", cp);
    printf("Thermal conductivity:\n");
    printf("k =\t%.3f\tW/m.K\n\n", k);
    
    printf("Equivalent pipe diameter:\n");
    printf("d =\t%.3f\tmm\n\n", 1000*d);
    
    if(eqn == 3 || eqn == 4){
        printf("Correlation constants:\n");
    }
    if(eqn == 3){
        printf("a =\t%.3f\t[ ]\n", a);
    }
    if(eqn == 3 || eqn == 4){
        printf("m =\t%.3f\t[ ]\n", m);
    }
    if(eqn == 3){
        printf("F1 =\t%.3f\t[ ]\n", F1);
        printf("F2 =\t%.3f\t[ ]\n", F2);
    }
    printf("\n");
    
    printf("\tIntermediate parameters:\n");
    printf("Reynolds number:\n");
    printf("Re =\t%.3f\t[ ]\n", Re);
    printf("Prandtl number:\n");
    printf("Pr =\t%.3f\t[ ]\n", Pr);
    printf("Nusselt number:\n");
    printf("Nu =\t%.3f\t[ ]\n\n", Nu);
    
    printf("\tOutput parameters:\n");
    printf("Fluid heat transfer coefficient:\n");
    printf("h =\t%.3f\tW/m3.K\n", h);
}

void OutCylHTCoeffWrite(int eqn, double rho, double u, double mu, double mu_s, double d, double cp, double k, double a, double m, double F1, double F2, double Re, double Pr, double Nu, double h)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Fluid heat transfer coefficient (Forced Convection outside cylindrical tubes) Estimation
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
    
    strcat(filename, " Fluid heat transfer coefficient (Forced Convection outside cylindrical tubes) Estimation");
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
    
    if(eqn == 3){
        fprintf(fp, "Bulk fluid viscosity:\n");
        fprintf(fp, "mu =\t%.3f\tcP\n", 1000*mu);
        fprintf(fp, "Fluid viscosity at wall:\n");
        fprintf(fp, "mu_s =\t%.3f\tcP\n\n", 1000*mu_s);
    }else{
        fprintf(fp, "Fluid viscosity:\n");
        fprintf(fp, "mu =\t%.3f\tcP\n\n", 1000*mu);
    }
    fprintf(fp, "Fluid heat capacity at constant pressure:\n");
    fprintf(fp, "cp =\t%.3f\tJ/kg.K\n", cp);
    fprintf(fp, "Thermal conductivity:\n");
    fprintf(fp, "k =\t%.3f\tW/m.K\n\n", k);
    
    fprintf(fp, "Equivalent pipe diameter:\n");
    fprintf(fp, "d =\t%.3f\tmm\n\n", 1000*d);
    
    if(eqn == 3 || eqn == 4){
        fprintf(fp, "Correlation constants:\n");
    }
    if(eqn == 3){
        fprintf(fp, "a =\t%.3f\t[ ]\n", a);
    }
    if(eqn == 3 || eqn == 4){
        fprintf(fp, "m =\t%.3f\t[ ]\n", m);
    }
    if(eqn == 3){
        fprintf(fp, "F1 =\t%.3f\t[ ]\n", F1);
        fprintf(fp, "F2 =\t%.3f\t[ ]\n", F2);
    }
    fprintf(fp, "\n");
    
    fprintf(fp, "\tIntermediate parameters:\n");
    fprintf(fp, "Reynolds number:\n");
    fprintf(fp, "Re =\t%.3f\t[ ]\n", Re);
    fprintf(fp, "Prandtl number:\n");
    fprintf(fp, "Pr =\t%.3f\t[ ]\n", Pr);
    fprintf(fp, "Nusselt number:\n");
    fprintf(fp, "Nu =\t%.3f\t[ ]\n\n", Nu);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Fluid heat transfer coefficient:\n");
    fprintf(fp, "h =\t%.3f\tW/m3.K\n", h);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void OutCylHTCoeffWriteSwitch(int eqn, double rho, double u, double mu, double mu_s, double d, double cp, double k, double a, double m, double F1, double F2, double Re, double Pr, double Nu, double h)
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
                OutCylHTCoeffWrite(eqn, rho, u, mu, mu_s, d, cp, k, a, m, F1, F2, Re, Pr, Nu, h);
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
void OutsideCylinder(void)
{
    printf("Forced convection outside cylindrical tubes.\n");
    
    //  Variable declaration
    char input[maxstrlen];
    int control = 0;
    int eqn = 0.0;
    
    double Re = 0.0;    // Reynolds number.
    double Pr = 0.0;    // Prandtl number.
    double Nu = 0.0;    // Nusselt number.
    double h = 0.0;     // Film heat transfer coefficient.
    
    double rho = 0.0;   // Fluid density.
    double mu = 0.0;    // Bulk fluid viscosity.
    double mu_s = 0.0;  // Fluid viscosity at wall.
    double cp = 0.0;    // Fluid heat capacity at constant pressure.
    double k = 0.0;     // Thermal conductivity.
    double u = 0.0;     // Fluid velocity.
    double d = 0.0;     // Inner pipe diameter.
    double a = 0.0;     // Correlation constant.
    double m = 0.0;     // Correlation constant.
    double F1 = 0.0;    // Correlation constant.
    double F2 = 0.0;    // Correlation constant.
        //  Variables for timing function
    struct timespec start, end;
    double elapsed = 0.0;
    
    //  Data Collection
    printf("Please select from the following methods:\n");
    printf("1. Hilpert's correlation (Air over a cylinder).\n");
    printf("2. Churchill and Bernstien (Fluid over a cylinder.\n");
    printf("3. Generalised Nusselt correlation.\n");
    printf("4. Square/Staggered tube layout.\n");
    control = 1;
    while(control == 1)
    {
        printf("Selection [1 - 4]: ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
                eqn = 1;
                control = 0;
                break;
            case '2':
                eqn = 2;
                control = 0;
                break;
            case '3':
                eqn = 3;
                control = 0;
                break;
            case '4':
                eqn = 4;
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer value between 1 and 3.\n");
                break;
        }
    }
    OutCylVariable(eqn, &rho, &mu, &mu_s, &cp, &k, &u, &d, &a, &m, &F1, &F2);
    
    //  Data Manipulation
    clock_getres(CLOCK_MONOTONIC, &start);
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Calculation function(s)
    Re = ReynoldsNum(rho, u, d, mu);
    Pr = PrandtlNum(cp, mu, k);
    switch(eqn)
    {
        case 1:
            h = OutCylHTCoeffAir(Re, k, d, &Nu);
            break;
        case 2:
            h = OutCylHTCoeffChurchillBernstein(Re, Pr, d, k, &Nu);
            break;
        case 3:
            h = OutCylHTCoeffGeneral(Re, Pr, a, m, F1, F2, k, d, &Nu);
            break;
        case 4:
            h = OutCylHTCoeffSquare(Re, Pr, m, k, d, &Nu);
            break;
        default:
            printf("Invalid variable not passed.\n");
            goto quit;
            break;
    }
    
    clock_getres(CLOCK_MONOTONIC, &end);
    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed = timer(start, end);

    printf("Calculations completed in %.6f seconds.\n", elapsed);
    
    //  Displaying results
    OutCylHTCoeffDisplay(eqn, rho, u, mu, mu_s, d, cp, k, a, m, F1, F2, Re, Pr, Nu, h);
    
    //  Writing to File
    OutCylHTCoeffWriteSwitch(eqn, rho, u, mu, mu_s, d, cp, k, a, m, F1, F2, Re, Pr, Nu, h);
    
quit:
    fflush(stdout);
}
