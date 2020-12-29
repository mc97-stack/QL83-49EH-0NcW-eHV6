//
//  03bInsideCylinder.c
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
void InCylVariable(int eqn, double *rho, double *mu, double *mu_s, double *cp, double *k, double *u, double *d)
{
    printf("Fluid properties:\n");
    *rho = inputDouble(0, 0, "fluid density", "kg/m3");
    *u = inputDouble(0, 0, "fluid velocity", "m/s");
    *mu = inputDouble(0, 0, "fluid viscosity", "cP");
    *mu = 0.001*(*mu);  // Conversion (cP -> Pa.s)
    
    if(eqn == 4)
    {
        *mu_s = inputDouble(0, 0, "fluid viscosity at wall", "cP");
        *mu_s = 0.001*(*mu_s);  // Conversion (cP -> Pa.s)
    }
    
    printf("\nThermal properties:\n");
    *cp = inputDouble(0, 0, "heat capacity at constant pressure", "J/(kg.K)");
    *k = inputDouble(0, 0, "fluid thermal conductivity", "W/m.K");
    
    printf("\nPhysical properties:\n");
    *d = inputDouble(0, 0, "pipe internal diameter", "mm");
    *d = 0.001*(*d);
}

/// MARK: GENERAL CALCULATIONS
double DittusBoelter(int mode, double Re, double Pr, double k, double d, double *Nusselt)
{
    /* 
     if mode == 1: heating
     if mode == 2: cooling
     */
    double Nu = 0.0;
    double result = 0.0;
    double sto = 0.0;
    
    if(mode == 1)
    {
        Nu = pow(Pr, 0.4);
    }
    if(mode == 2)
    {
        Nu = pow(Pr, 0.3);
    }
    sto = pow(Re, 0.8);
    Nu *= sto;
    Nu *= 0.023;
    
    result = (Nu)*k;
    result /= d;
    
    return result;
}

double Colburn(double Re, double Pr, double k, double d, double *Nusselt)
{
    double Nu = 0.0;
    double result = 0.0;
    double sto = 0.0;
    
    sto = pow(Pr, 0.33);
    Nu = sto;
    sto = pow(Re, 0.8);
    Nu *= Re;
    Nu *= 0.023;
    
    result = (Nu)*k;
    result /= d;
    
    return result;
}

double Stanton(double rho, double u, double d, double mu, double cp, double k, double *Stanton)
{
    double result = 0.0;
    double Re = 0.0;
    double Pr = 0.0;
    double St = 0.0;
    double jh = 0.0;
    double sto = 0.0;
    
    Re = ReynoldsNum(rho, u, d, mu);
    sto = -0.2;
    sto = pow(Re, sto);
    jh *= 0.023;
    
    Pr = PrandtlNum(cp, mu, k);
    sto = pow(Pr, 0.67);
    
    St = jh/sto;
    *Stanton = St;
    
    result = cp*rho;
    result *= u;
    result *= St;
    
    return result;
}

double SiederTate(double Re, double Pr, double mu, double mu_wall, double k, double d, double *Nusselt)
{
    double result = 0.0;
    double Nu = 0.0;
    double sto = 0.0;
    
    sto = mu/mu_wall;
    Nu = pow(sto, 0.14);
    
    sto = pow(Pr, 0.33);
    Nu *= sto;
    
    sto = pow(Re, 0.8);
    Nu *= sto;
    Nu *= 0.023;
    
    result = (Nu)*k;
    result /= d;
    
    return result;
}

/// MARK: DISPLAY AND WRITE
void InCylHTCoeffDisplay(int eqn, double rho, double u, double mu, double mu_wall, double cp, double k, double d, double Re, double Pr, double St, double Nu, double h)
{
    printf("_Film_Heat_Transfer_Coefficient_Estimation_\n");
    printf("\tInput parameters:\n");
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n", rho);
    printf("Fluid velocity:\n");
    printf("u =\t%.3f\tm/s\n", u);
    printf("Fluid viscosity:\n");
    printf("mu =\t%.3f\tcP\n", 1000*mu);
    if(eqn == 4){
        printf("Fluid viscosity at wall:\n");
        printf("mu_wall =\t%.3f\tcP\n\n", 1000*mu_wall);
    }
    
    printf("Fluid heat capacity at constant pressure:\n");
    printf("cp =\t%.3f\tJ/kg.K\n", cp);
    printf("Fluid thermal conductivity:\n");
    printf("k =\t%.3f\tW/m.K\n\n", k);
    
    printf("Pipe internal diameter:\n");
    printf("d =\t%.3f\tmm\n\n", 1000*d);
    
    printf("\tIntermediate parameters:\n");
    printf("Reynolds number:\n");
    printf("Re =\t%.3f\t[ ]\n", Re);
    printf("Prandtl number:\n");
    printf("Pr =\t%.3f\t[ ]\n", Pr);
    if(eqn == 3){
        printf("Stanton number:\n");
        printf("St =\t%.3f\t[ ]\n", St);
    }else{
        printf("Nusselt number:\n");
        printf("Nu =\t%.3f\t[ ]\n", Nu);
    }
    printf("\n");
    
    printf("\tOutput parameters:\n");
    printf("Fluid heat transfer coefficient:\n");
    printf("h =\t%.3f\tJ/m2.K\n", h);
}

void InCylHTCoeffWrite(int eqn, double rho, double u, double mu, double mu_wall, double cp, double k, double d, double Re, double Pr, double St, double Nu, double h)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Polytropic Process Results
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
    
    strcat(filename, " Fluid heat transfer coefficient (Forced Convection inside cylindrical tubes) Estimation");
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
    fprintf(fp, "mu =\t%.3f\tcP\n", 1000*mu);
    if(eqn == 4){
        fprintf(fp, "Fluid viscosity at wall:\n");
        fprintf(fp, "mu_wall =\t%.3f\tcP\n\n", 1000*mu_wall);
    }
    
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
    if(eqn == 3){
        fprintf(fp, "Stanton number:\n");
        fprintf(fp, "St =\t%.3f\t[ ]\n", St);
    }else{
        fprintf(fp, "Nusselt number:\n");
        fprintf(fp, "Nu =\t%.3f\t[ ]\n", Nu);
    }
    fprintf(fp, "\n");
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Fluid heat transfer coefficient:\n");
    fprintf(fp, "h =\t%.3f\tJ/m2.K\n", h);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void InCylHTCoeffWriteSwitch(int eqn, double rho, double u, double mu, double mu_wall, double cp, double k, double d, double Re, double Pr, double St, double Nu, double h)
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
                InCylHTCoeffWrite(eqn, rho, u, mu, mu_wall, cp, k, d, Re, Pr, St, Nu, h);
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
void InsideCylinder(void)
{
    printf("Forced convection inside cylindrical tubes.\n");
    
    //  Variable declaration
    char input[maxstrlen];
    int control = 0;
    int contmode = 0;
    int eqn = 0;
    int mode = 0;
    
    double Re = 0.0;    // Reynolds number.
    double Pr = 0.0;    // Prandtl number.
    double St = 0.0;    // Stanton number.
    double Nu = 0.0;    // Nusselt number.
    double h = 0.0;     // Film heat transfer coefficient.
    
    double rho = 0.0;   // Fluid density.
    double mu = 0.0;    // Fluid bulk viscosity.
    double mu_s = 0.0;  // Fluid viscosity at wall.
    double cp = 0.0;    // Fluid heat capacity at constant pressure.
    double k = 0.0;     // Thermal conductivity.
    double u = 0.0;     // Fluid velocity.
    double d = 0.0;     // Inner pipe diameter.
        //  Variables for timing function
    struct timespec start, end;
    double elapsed = 0.0;
    
    //  Data Collection
    printf("Please select from the following methods:\n");
    printf("1. Dittus-Boelter equation.\n");
    printf("2. Colburn equation.\n");
    printf("3. Stanton number.\n");
    printf("4. Sider and Tate correlation.\n");
    control = 1;
    while(control == 1)
    {
        printf("Selection [1 - 4]: ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
                eqn = 1;
                printf("Please select from the following modes:\n");
                printf("1. Cooling.\n");
                printf("2. Heating.\n");
                contmode = 1;
                while(contmode == 1)
                {
                    printf("Selection [1 - 2]: ");
                    fgets(input, sizeof(input), stdin);
                    switch(input[0])
                    {
                        case '1':
                            mode = 2;
                            contmode = 0;
                            break;
                        case '2':
                            mode = 1;
                            contmode = 0;
                            break;
                        default:
                            printf("Input not recognised. Please enter either '1' or '2'\n");
                            break;
                    }
                }
                
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
            case '0':
            case 'Q':
            case 'q':
                goto quit;
                break;
            default:
                printf("Input not recognised. Please enter a value between 1 and 4.\n");
                break;
        }
    }
    InCylVariable(eqn, &rho, &mu, &mu_s, &cp, &k, &u, &d);
    
    //  Data Manipulation
    clock_getres(CLOCK_MONOTONIC, &start);
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Calculation function(s)
    Re = ReynoldsNum(rho, u, d, mu);
    Pr = PrandtlNum(cp, mu, k);
    switch(eqn)
    {
        case 1:
            h = DittusBoelter(mode, Re, Pr, k, d, &Nu);
            break;
        case 2:
            h = Colburn(Re, Pr, k, d, &Nu);
            break;
        case 3:
            h = Stanton(rho, u, d, mu, cp, k, &St);
            break;
        case 4:
            h = SiederTate(Re, Pr, mu, mu_s, k, d, &Nu);
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
    InCylHTCoeffDisplay(eqn, rho, u, mu, mu_s, cp, k, d, Re, Pr, St, Nu, h);
    
    //  Writing to File
    InCylHTCoeffWriteSwitch(eqn, rho, u, mu, mu_s, cp, k, d, Re, Pr, St, Nu, h);
    
quit:
    fflush(stdout);
}
