//
//  EntropyBalance.c
//  Process Model
//
//  Created by Matthew Cheung on 24/11/2020.
//
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

//Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Custom Header Files
#include "System.h"
#include "B48BC_T5.h"
#include "05aEntropyBalance.h"

#define maxstrlen 128

void EntropyBalanceVariable(double *m, double *cp, double *T1, double *T2, double *TSurr)
{
    *m = inputDouble(0, 0, "mass in system", "kg/s");
    
    *cp = inputDouble(0, 0, "heat capacity at constant pressure", "kJ/kg.K");
    
    *T1 = inputDouble(1, 1, "initial system temperature", "deg C");
    *T1 = (*T1)+273.15;
    
    *T2 = inputDouble(1, 1, "final system temperature", "deg C");
    *T2 = (*T2)+273.15;
    
    *TSurr = inputDouble(1, 1, "temperature of surroundings", "deg C");
    *TSurr = (*TSurr)+273.15;
}

double EntropyBalanceSysCalc(double m, double cp, double T1, double T2)
{
    double dS = 0.0;
    double sto = 0.0;
    
    sto = T2/T1;
    sto = log(sto);
    dS = m*cp;
    dS = (dS)*(sto);
    
    return dS;
}

double EntropyBalanceSurrCalc(double m, double cp, double T1, double T2, double TSurr)
{
    double dS = 0.0;
    double sto = 0.0;
    
    sto = T2 - T1;
    dS = m*cp;
    sto = (dS)*(sto);
    dS = 0.0;           // Total heat transferred to system calculated.
    
    dS = -1*(sto);      // Total heat transferred from system to surroundings calculated.
    dS = (dS)/TSurr;    // Entropy change of surroundings calculated.
    
    return dS;
}

double EntropyBalance(double System, double Surroundings)
{
    return System + Surroundings;
}

void EntropyBalanceDisplay(double m, double cp, double T1, double T2, double TSurr, double SysEntropy, double SurrEntropy, double TotalEntropy)
{
    printf("_Steady-State_Entropy_Balance_Results_\n");
    printf("\tInput parameters:\n");
    printf("Mass flow rate through system:\n");
    printf("m =\t%.3f\tkg/s\n", m);
    printf("Heat capacity at constant pressure:\n");
    printf("cp =\t%.3f\tkJ/kg.K\n\n", cp);
    
    printf("Initial system temperature:\n");
    printf("T1 =\t%.3f\tdeg C\n", T1 - 273.15);
    printf("Final system temperature:\n");
    printf("T2 =\t%.3f\tdeg C\n", T2 - 273.15);
    printf("Temperature of system surroundings:\n");
    printf("TSurr =\t%.3f\tdeg C\n\n", TSurr - 273.15);
    
    printf("\tOutput parameters:\n");
    printf("System entropy change:\n");
    printf("dS_{sys} =\t%.3f\tkW/K\n", SysEntropy);
    printf("System entropy change:\n");
    printf("dS_{surr} =\t%.3f\tkW/K\n", SurrEntropy);
    printf("System entropy change:\n");
    printf("dS_{total} =\t%.3f\tkW/K\n\n", TotalEntropy);
    
    if(TotalEntropy > 0){
        printf("This isobaric process is irreversible.\n");
    }else{
        if(TotalEntropy == 0){
            printf("This isobaric process is reversible.\n");
        }else{
            printf("This isobaric process is impossible.\n");
        }
    }
}

void EntropyBalanceWrite(double m, double cp, double T1, double T2, double TSurr, double SysEntropy, double SurrEntropy, double TotalEntropy)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Entropy Balance Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Isobaric Entropy Balance Results");
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
    fprintf(fp, "_Steady-State_Entropy_Balance_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Mass flow rate through system:\n");
    fprintf(fp, "m =\t%.3f\tkg/s\n", m);
    fprintf(fp, "Heat capacity at constant pressure:\n");
    fprintf(fp, "cp =\t%.3f\tkJ/kg.K\n\n", cp);
    
    fprintf(fp, "Initial system temperature:\n");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n", T1 - 273.15);
    fprintf(fp, "Final system temperature:\n");
    fprintf(fp, "T2 =\t%.3f\tdeg C\n", T2 - 273.15);
    fprintf(fp, "Temperature of system surroundings:\n");
    fprintf(fp, "TSurr =\t%.3f\tdeg C\n\n", TSurr - 273.15);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "System entropy change:\n");
    fprintf(fp, "dS_{sys} =\t%.3f\tkW/K\n", SysEntropy);
    fprintf(fp, "System entropy change:\n");
    fprintf(fp, "dS_{surr} =\t%.3f\tkW/K\n", SurrEntropy);
    fprintf(fp, "System entropy change:\n");
    fprintf(fp, "dS_{total} =\t%.3f\tkW/K\n\n", TotalEntropy);
    
    if(TotalEntropy > 0){
        fprintf(fp, "This isobaric process is irreversible.\n");
    }else{
        if(TotalEntropy == 0){
            fprintf(fp, "This isobaric process is reversible.\n");
        }else{
            fprintf(fp, "This isobaric process is impossible.\n");
        }
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void EntropyBalanceWriteSwitch(double m, double cp, double T1, double T2, double TSurr, double SysEntropy, double SurrEntropy, double TotalEntropy)
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
                EntropyBalanceWrite(m, cp, T1, T2, TSurr, SysEntropy, SurrEntropy, TotalEntropy);
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

void SteadyStateEntropyBalance(void)
{
    int whilmain = 0;
    printf("Steady-State Entropy Balance (Isobaric).\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
            //  Subroutine behaviour (Delete me when done)
        
        double TotalEntropy = 0.0;
        double SysEntropy = 0.0;
        double SurrEntropy = 0.0;
        
        double m = 0.0;         // Mass flowrate through the system.
        double cp = 0.0;        // Heat capacity at constant pressure.
        double T1 = 0.0;        // Initial system temperature.
        double T2 = 0.0;        // Final system temperature.
        double TSurr = 0.0;     // Temperature of surroundings.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        EntropyBalanceVariable(&m, &cp, &T1, &T2, &TSurr);
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        // Calculation function(s)
        SysEntropy = EntropyBalanceSysCalc(m, cp, T1, T2);
        SurrEntropy = EntropyBalanceSurrCalc(m, cp, T1, T2, TSurr);
        
        TotalEntropy = EntropyBalance(SysEntropy, SurrEntropy);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("\nCalculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        EntropyBalanceDisplay(m, cp, T1, T2, TSurr, SysEntropy, SurrEntropy, TotalEntropy);
        
        //  Writing to File
        EntropyBalanceWriteSwitch(m, cp, T1, T2, TSurr, SysEntropy, SurrEntropy, TotalEntropy);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
