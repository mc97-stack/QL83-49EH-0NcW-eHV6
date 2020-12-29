//
//  03bNaturalConvection.c
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
#include "01aTemperatureConversion.h"
#include "03bFilmHTCoefficient.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void FluidHTNaturalVariable(double *rho, double *mu, double *cp, double *k, double *u, double *d, double *T1, double *T2, double *beta, double *constant, double *n, double *m)
{
    printf("Fluid properties:\n");
    *rho = inputDouble(0, 0, "fluid density", "kg/m3");
    *u = inputDouble(0, 0, "fluid velocity", "m/s");
    *mu = inputDouble(0, 0, "fluid viscosity", "cP");
    *mu = 0.001*(*mu);  // Conversion (cP -> Pa.s)
    *beta = inputDouble(0, 0, "coefficient of cubic expansion", "m/K");
    
    printf("\nThermal properties:\n");
    *cp = inputDouble(0, 0, "heat capacity at constant pressure", "J/(kg.K)");
    *k = inputDouble(0, 0, "fluid thermal conductivity", "W/m.K");
    
    printf("\nSystem properties:\n");
    *d = inputDouble(0, 0, "internal pipe diameter", "mm");
    *d = 0.001*(*d);
    
    *T1 = CelsiusKelvin(inputDouble(1, 1, "fluid film hot side temperature", "deg C"));
    *T2 = CelsiusKelvin(inputDouble(1, 1, "fluid film cold side temperature", "deg C"));
    
    printf("\nCorrelation constants:\n");
    *constant = inputDouble(0, 0, "correlation constant", "");
    *n = inputDouble(0, 0, "n", "");
    *m = inputDouble(0, 0, "m", "");
}

/// MARK: GENERAL CALCULATIONS
double NaturalHTCoefficient(double constant, double n, double m, double beta, double T1, double T2, double d, double rho, double mu, double cp, double k, double *Nusselt, double *Grashof, double *Prandtl)
{
    double Nu = 0.0;
    double result = 0.0;
    double sto = 0.0;
    
    *Grashof = GrashofNum(beta, T1, T2, d, rho, mu);
    sto = *Grashof;
    sto = pow(sto, n);
    Nu = constant*(sto);
    
    *Prandtl = PrandtlNum(cp, mu, k);
    sto = *Prandtl;
    sto = pow(sto, m);
    Nu *= (sto);
    *Nusselt = Nu;
    
    result = (Nu)*k;
    result /= d;
    
    return result;
}

/// MARK: DISPLAY AND WRITE
void NaturalHTCoeffDisplay(double rho, double u, double mu, double beta, double cp, double k, double d, double T1, double T2, double constant, double n, double m, double Gr, double Pr, double Nu, double h)
{
    printf("_Film_Heat_Transfer_Coefficient_(Natural_Convection)_Results_\n");
    printf("\tInput parameters:\n");
    printf("Fluid properties\n");
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n", rho);
    printf("Fluid velocity:\n");
    printf("u =\t%.3f\tm/s\n", u);
    printf("Fluid viscosity:\n");
    printf("mu =\t%.3f\tcP\n", mu);
    printf("Coefficient of cubic expansion:\n");
    printf("beta =\t%.3f\tm/K\n\n", beta);
    
    printf("Thermal properties\n");
    printf("Heat capacity at constant pressure:\n");
    printf("cp =\t%.3f\tJ/kg.K\n", cp);
    printf("Fluid thermal conductivity:\n");
    printf("k =\t%.3f\tW/m.K\n\n", k);
    
    printf("System properties\n");
    printf("Internal pipe diameter:\n");
    printf("d =\t%.3f\tmm\n", d*1000);
    printf("Fluid film hot side temperature:\n");
    printf("T1 =\t%.3f\tdeg C\n", KelvinCelsius(T1));
    printf("Fluid film cold side temperature:\n");
    printf("T2 =\t%.3f\tdeg C\n\n", KelvinCelsius(T2));
    
    printf("Correlation constants\n");
    printf("constant =\t%.3f\t[ ]\n", constant);
    printf("n =\t%.3f\t[ ]\n", n);
    printf("m =\t%.3f\t[ ]\n\n", m);
    
    printf("\tIntermediate parameters:\n");
    printf("Grashof number:\n");
    printf("Gr =\t%.3f\t[ ]\n", Gr);
    printf("Prandtl number:\n");
    printf("Pr =\t%.3f\t[ ]\n", Pr);
    printf("Nusselt number:\n");
    printf("Nu =\t%.3f\t[ ]\n\n", Nu);
    
    printf("\tOutput parameters:\n");
    printf("Film heat transfer coefficient:\n");
    printf("h =\t%.3f\tW/m2.K\n", h);
}

void NaturalHTCoeffWrite(double rho, double u, double mu, double beta, double cp, double k, double d, double T1, double T2, double constant, double n, double m, double Gr, double Pr, double Nu, double h)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Heat Transfer Coefficient Results (Natural Convection)
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
    
    strcat(filename, " Heat Transfer Coefficient Results (Natural Convection)");
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
    fprintf(fp, "_Film_Heat_Transfer_Coefficient_(Natural_Convection)_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Fluid properties\n");
    fprintf(fp, "Fluid density:\n");
    fprintf(fp, "rho =\t%.3f\tkg/m3\n", rho);
    fprintf(fp, "Fluid velocity:\n");
    fprintf(fp, "u =\t%.3f\tm/s\n", u);
    fprintf(fp, "Fluid viscosity:\n");
    fprintf(fp, "mu =\t%.3f\tcP\n", mu);
    fprintf(fp, "Coefficient of cubic expansion:\n");
    fprintf(fp, "beta =\t%.3f\tm/K\n\n", beta);
    
    fprintf(fp, "Thermal properties\n");
    fprintf(fp, "Heat capacity at constant pressure:\n");
    fprintf(fp, "cp =\t%.3f\tJ/kg.K\n", cp);
    fprintf(fp, "Fluid thermal conductivity:\n");
    fprintf(fp, "k =\t%.3f\tW/m.K\n\n", k);
    
    fprintf(fp, "System properties\n");
    fprintf(fp, "Internal pipe diameter:\n");
    fprintf(fp, "d =\t%.3f\tmm\n", d*1000);
    fprintf(fp, "Fluid film hot side temperature:\n");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n", KelvinCelsius(T1));
    fprintf(fp, "Fluid film cold side temperature:\n");
    fprintf(fp, "T2 =\t%.3f\tdeg C\n\n", KelvinCelsius(T2));
    
    fprintf(fp, "Correlation constants\n");
    fprintf(fp, "constant =\t%.3f\t[ ]\n", constant);
    fprintf(fp, "n =\t%.3f\t[ ]\n", n);
    fprintf(fp, "m =\t%.3f\t[ ]\n\n", m);
    
    fprintf(fp, "\tIntermediate parameters:\n");
    fprintf(fp, "Grashof number:\n");
    fprintf(fp, "Gr =\t%.3f\t[ ]\n", Gr);
    fprintf(fp, "Prandtl number:\n");
    fprintf(fp, "Pr =\t%.3f\t[ ]\n", Pr);
    fprintf(fp, "Nusselt number:\n");
    fprintf(fp, "Nu =\t%.3f\t[ ]\n\n", Nu);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Film heat transfer coefficient:\n");
    fprintf(fp, "h =\t%.3f\tW/m2.K\n", h);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void NaturalHTCoeffSwitch(int mode, double rho, double u, double mu, double beta, double cp, double k, double d, double T1, double T2, double constant, double n, double m, double Gr, double Pr, double Nu, double h)
{
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        char input[maxstrlen];
        if(mode == 1)
        {
            printf("Do you want to view the results? ");
        }
        if(mode == 2)
        {
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
                if(mode == 1)
                {
                    NaturalHTCoeffDisplay(rho, u, mu, beta, cp, k, d, T1, T2, constant, n, m, Gr, Pr, Nu, h);
                }
                if(mode == 2)
                {
                    NaturalHTCoeffWrite(rho, u, mu, beta, cp, k, d, T1, T2, constant, n, m, Gr, Pr, Nu, h);
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
void NaturalConvection(void)
{
    printf("Natural Convection\n");
    
    //  Variable declaration
    double Gr = 0.0;        // Grashof number.
    double Pr = 0.0;        // Prandtl number.
    double Nu = 0.0;        // Nusselt number.
    double h = 0.0;         // Film heat transfer coefficient.
    
    double rho = 0.0;       // Fluid density.
    double mu = 0.0;        // Fluid viscosity.
    double cp = 0.0;        // Fluid heat capacity at constant pressure.
    double k = 0.0;         // Thermal conductivity.
    double u = 0.0;         // Fluid velocity.
    double d = 0.0;         // Internal pipe diameter.
    double T1 = 0.0;        // Hot side film temperature. 
    double T2 = 0.0;        // Cold side film temperature.
    double beta = 0.0;      // Coefficient of cubic expansion.
    double constant = 0.0;  // Correlation equation constant.
    double n = 0.0;         // Grashof number exponent.
    double m = 0.0;         // Prandtl number exponent.
    
        //  Variables for timing function
    struct timespec start, end;
    double elapsed = 0.0;
    
    //  Data Collection
    FluidHTNaturalVariable(&rho, &mu, &cp, &k, &u, &d, &T1, &T2, &beta, &constant, &n, &m);
    
    //  Data Manipulation
    clock_getres(CLOCK_MONOTONIC, &start);
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Calculation function(s)
    h = NaturalHTCoefficient(constant, n, m, beta, T1, T2, d, rho, mu, cp, k, &Nu, &Gr, &Pr);
    
    clock_getres(CLOCK_MONOTONIC, &end);
    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed = timer(start, end);

    printf("Calculations completed in %.6f seconds.\n", elapsed);
    
    //  Displaying results
    NaturalHTCoeffSwitch(1, rho, u, mu, beta, cp, k, d, T1, T2, constant, n, m, Gr, Pr, Nu, h);
    
    //  Writing to File
    NaturalHTCoeffSwitch(2, rho, u, mu, beta, cp, k, d, T1, T2, constant, n, m, Gr, Pr, Nu, h);
    
    fflush(stdout);
}
