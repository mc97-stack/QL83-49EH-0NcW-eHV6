//
//  02bEnerCon.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 26/06/2020.
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
#include "B48BB_T2.h"
#include "02bEnerCon.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define g 9.80665

/// MARK: VARIABLE INPUT
void EnerConVariable(double *h1, double *h2, double *u1, double *u2, double *z1, double *z2, double *q, double *w)
{
    double inteng1 = 0.0;   // Initial internal energy
    double inteng2 = 0.0;   // Final internal energy
    double pres1 = 0.0;     // Initial system pressure
    double pres2 = 0.0;     // Final system pressure
    double rho1 = 0.0;      // Initial fluid density
    double rho2 = 0.0;      // Final fluid density
    
    //Function variables
    char menu[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        printf("Which definition do you want to use:\n");
        printf("1. Internal Energy (u)\n2. Enthalpy (h)\n\n");
        printf("Selection: ");
        fgets(menu, sizeof(menu), stdin);
        switch(menu[0])
        {
            case '1':
            case 'I':
            case 'U':
            case 'i':
            case 'u':
                inteng1 = inputDouble(0, 0, "initial specific internal energy", "kJ/kg");
                inteng1 = inteng1*1000;
                
                inteng2 = inputDouble(0, 0, "final specific internal energy", "kJ/kg");
                inteng2 = inteng2*1000;
                
                pres1 = inputDouble(0, 0, "initial pressure", "kPa");
                pres1 = pres1*1000;
                
                pres2 = inputDouble(0, 0, "final pressure", "kPa");
                pres2 = pres2*1000;
                
                rho1 = inputDouble(0, 0, "initial density", "kg/m3");
                
                rho2 = inputDouble(0, 0, "final density", "kg/m3");
                
                //Converting through to enthalpy using definition
                *h1 = EnthalpyConversion(inteng1, pres1, rho1);
                *h2 = EnthalpyConversion(inteng2, pres2, rho2);
                
                control = 0;
            break;
            case '2':
            case 'E':
            case 'H':
            case 'e':
            case 'h':
                *h1 = inputDouble(0, 0, "initial specific enthalpy", "kJ/kg");
                *h1 = (*h1)*1000;
                
                *h2 = inputDouble(0, 0, "final specific enthalpy", "kJ/kg");
                *h2 = (*h2)*1000;
                
                control = 0;
            break;
            default:
                printf("Input not recognised\n\n");
            break;
        }
        fflush(stdout);
    }
    
    *u1 = inputDouble(0, 0, "initial velocity", "m/s");
    
    *u2 = inputDouble(0, 0, "final velocity", "m/s");
    
    *z1 = inputDouble(0, 0, "initial fluid height", "m");
    
    *z2 = inputDouble(0, 0, "final fluid height", "m");
    
    *q = inputDouble(0, 0, "specific process heat", "kJ/kg");
    *q = (*q)*1000;
    
    *w = inputDouble(0, 0, "specific process work", "kJ/kg");
    *w = (*w)*1000;
}

/// MARK: GENERAL CALCULATIONS
double EnthalpyConversion(double u, double P, double rho)
{
    double h = 0.0; //Declaring and initialising
    
    h = P/rho;
    h = u + (h);
    
    return h;
}

double EnerConFluidCalculation(double h, double u, double z)
{
    double kin = 0.0;   // Kinetic energy
    double pot = 0.0;   // Potential energy
    
    double EnerCont = 0.0;  // Total energy control or the Hamiltonian operator + fluid enthalpy.
    
    kin = pow(u, 2);
    kin = (kin)/2;
    kin = (kin)*0.001;
    
    pot = z*g;
    pot = (pot)*0.001;
    
    EnerCont = h + (kin);
    
    EnerCont = (EnerCont) + (pot);
    
    return EnerCont;
}

double EnerConProcessCalculation(double q, double w)
{
    double Energy = 0.0;
    
    Energy  = q + w;
    return Energy;
}

/// MARK: DISPLAY AND WRITE
void EnerConDisplay(double h1, double h2, double u1, double u2, double z1, double z2, double q, double w, double state1, double state2, double process, double check)
{
    printf("_Steady-Flow_Energy_Equation_\n");
    printf("Assuming the fluid is incompressible. \n");
    printf("g =\t%.3f\tm/s2\n\n", g);
    printf("\tInput parameters:\n");
    printf("Initial fluid enthalpy:\n");
    printf("h1 =\t%.3f\tkJ/kg\n", h1*0.001);
    printf("Final fluid enthalpy:\n");
    printf("h2 =\t%.3f\tkJ/kg\n", h2*0.001);
    printf("Initial fluid velocity:\n");
    printf("u1 =\t%.3f\tm/s\n", u1);
    printf("Final fluid velocity:\n");
    printf("u2 =\t%.3f\tm/s\n", u2);
    printf("Initial fluid height:\n");
    printf("z1 =\t%.3f\tm\n", z1);
    printf("Final fluid height:\n");
    printf("z2 =\t%.3f\tm\n\n", z2);
    
    printf("Specific process heat:\n");
    printf("q =\t%.3f\tkJ/kg\n", q*0.001);
    printf("Specific process work:\n");
    printf("w =\t%.3f\tkJ/kg\n\n", w*0.001);
    
    printf("\tOutput parameters:\n");
    printf("Energy content at state 1:\n");
    printf("state1 =\t%.3f\tkJ/kg\n", state1*0.001);
    printf("Energy content at state 2:\n");
    printf("state2 =\t%.3f\tkJ/kg\n\n", state1*0.001);
    
    printf("Net process energy:\n");
    printf("q + w =\t%.3f\tkJ/kg\n\n", process*0.001);
    
    printf("check =\t%.3f\tkJ/kg\n", check*0.001);
    if(fabs(check) <= 0.001)
    {
        printf("Your process should work in reality\n");
    }else{
        printf("Your process is not at steady-state\n");
    }
    fflush(stdout);
}

void EnerConWrite(double h1, double h2, double u1, double u2, double z1, double z2, double q, double w, double state1, double state2, double process, double check)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Steady Flow Energy Equation Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Steady Flow Energy Equation Results");
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
    fprintf(fp, "_Steady-Flow_Energy_Equation_\n");
    fprintf(fp, "Assuming the fluid is incompressible. \n");
    fprintf(fp, "g =\t%.3f\tm/s2\n\n", g);
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial fluid enthalpy:\n");
    fprintf(fp, "h1 =\t%.3f\tkJ/kg\n", h1*0.001);
    fprintf(fp, "Final fluid enthalpy:\n");
    fprintf(fp, "h2 =\t%.3f\tkJ/kg\n", h2*0.001);
    fprintf(fp, "Initial fluid velocity:\n");
    fprintf(fp, "u1 =\t%.3f\tm/s\n", u1);
    fprintf(fp, "Final fluid velocity:\n");
    fprintf(fp, "u2 =\t%.3f\tm/s\n", u2);
    fprintf(fp, "Initial fluid height:\n");
    fprintf(fp, "z1 =\t%.3f\tm\n", z1);
    fprintf(fp, "Final fluid height:\n");
    fprintf(fp, "z2 =\t%.3f\tm\n\n", z2);
    
    fprintf(fp, "Specific process heat:\n");
    fprintf(fp, "q =\t%.3f\tkJ/kg\n", q*0.001);
    fprintf(fp, "Specific process work:\n");
    fprintf(fp, "w =\t%.3f\tkJ/kg\n\n", w*0.001);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Energy content at state 1:\n");
    fprintf(fp, "state1 =\t%.3f\tkJ/kg\n", state1*0.001);
    fprintf(fp, "Energy content at state 2:\n");
    fprintf(fp, "state2 =\t%.3f\tkJ/kg\n\n", state1*0.001);
    
    fprintf(fp, "Net process energy:\n");
    fprintf(fp, "q + w =\t%.3f\tkJ/kg\n\n", process*0.001);
    
    fprintf(fp, "check =\t%.3f\tkJ/kg\n", check*0.001);
    
    if(fabs(check) <= 0.001)
    {
        fprintf(fp, "Your process should work in reality\n");
    }else{
        fprintf(fp, "Your process is not at steady-state\n");
    }
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void EnerConWriteSwitch(double h1, double h2, double u1, double u2, double z1, double z2, double q, double w, double state1, double state2, double process, double check)
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
                EnerConWrite(h1, h2, u1, u2, z1, z2, q, w, state1, state2, process, check);
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
void EnergyConservation()
{
    //  Pseudo-main function.
    int whilmain = 0;
    printf("Energy Conservation Check\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        double state1 = 0.0;    // Fluid energy content at state 1.
        double state2 = 0.0;    // Fluid energy content at state 2.
        double process = 0.0;   // Net energy inputted/ removed to/from process.
        double check = 0.0;     // Store variable for hold the difference between fluid state energies and process energies.
        
        double h1 = 0.0;        // Fluid enthalpy at state 1.
        double h2 = 0.0;        // Fluid enthalpy at state 2.
        double u1 = 0.0;        // Fluid velocity at state 1.
        double u2 = 0.0;        // Fluid velocity at state 2.
        double z1 = 0.0;        // Fluid elevation at state 1.
        double z2 = 0.0;        // Fluid elevation at state 2.
        double q = 0.0;         // Total heat inputted into/removed from process.
        double w = 0.0;         // Total work done by/on or process.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data collection
        EnerConVariable(&h1, &h2, &u1, &u2, &z1, &z2, &q, &w);
        
        //  Running calculations
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        state1 = EnerConFluidCalculation(h1, u1, z1);
        
        state2 = EnerConFluidCalculation(h2, u2, z2);
        
        process = EnerConProcessCalculation(q, w);
        
        check = state2 - state1;
        check = (check) - process;
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        EnerConDisplay(h1, h2, u1, u2, z1, z2, q, w, state1, state2, process, check);
        
        //  Writing to file
        EnerConWriteSwitch(h1, h2, u1, u2, z1, z2, q, w, state1, state2, process, check);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
