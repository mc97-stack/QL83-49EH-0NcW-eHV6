//
//  06aExtentOfReaction.c
//  Process Model
//
//  Created by Matthew Cheung on 26/11/2020.
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
#include "B48BC_T6.h"
#include "06aExtentOfReaction.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void EoRVariable(double *reacted, double *stoich)
{
    *reacted = inputDouble(0, 0, "moles of species reacted", "mol");
    
    *stoich = inputDouble(1, 1, "stoichiometric coefficient", "");
}

/// MARK: GENERAL CALCULATIONS
double EoRCalculation(double reacted, double stoich)
{
    return reacted/stoich;
}

/// MARK: DISPLAY AND WRITE
void EoRDisplay(double reacted, double stoich, double EoR)
{
    printf("_Extent_of_Reaction_Results_\n");
    printf("\tInput parameters:\n");
    printf("Moles of species reacted:\n");
    printf("\\Delta{n}_i =\t%.3f\tmol\n", reacted);
    printf("Stoichiometric coefficient:\n");
    printf("v_i =\t%.3f\n\n", stoich);
    
    printf("\tOutput parameters:\n");
    printf("Extent of Reaction:\n");
    printf("\\varepsilon = \t%.3f\tmol\n", EoR);
}

void EoRWrite(double reacted, double stoich, double EoR)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Extent of Reaction Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Extent of Reaction Results");
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
    fprintf(fp, "_Extent_of_Reaction_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Moles of species reacted:\n");
    fprintf(fp, "\\Delta{n}_i =\t%.3f\tmol\n", reacted);
    fprintf(fp, "Stoichiometric coefficient:\n");
    fprintf(fp, "v_i =\t%.3f\n\n", stoich);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Extent of Reaction:\n");
    fprintf(fp, "\\varepsilon = \t%.3f\tmol\n", EoR);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void EoRWriteSwitch(double reacted, double stoich, double EoR)
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
                EoRWrite(reacted, stoich, EoR);
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
void ExtentOfReaction(void)
{
    int whilmain = 0;
    printf("Extent of Reaction\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        int hold = 0;           // Variable used to store the absolute value of the stoichiometric coefficient.
        
        double EoR = 0.0;       // Extent of reaction.
        
        double reacted = 0.0;   // Moles consumed by the reaction.
        double stoich = 0;      // Stoichiometric coefficient.
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        EoRVariable(&reacted, &stoich);
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        if(stoich < 0)
        {
            // Stoichiometric coefficient relates to a reagent.
            hold = fabs(stoich);
        }else{
            hold = stoich;
        }
        
        // Calculation function(s)
        EoR = EoRCalculation(reacted, hold);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        EoRDisplay(reacted, stoich, EoR);
        
        //  Writing to File
        EoRWriteSwitch(reacted, stoich, EoR);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
