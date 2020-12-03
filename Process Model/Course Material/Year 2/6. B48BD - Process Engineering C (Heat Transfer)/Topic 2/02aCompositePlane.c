//
//  02aCompositePlane.c
//  Process Model
//
//  Created by Matthew Cheung on 02/12/2020.
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
#include "01aTemperatureConversion.h"
#include "B48BD_T2.h"
#include "02aCompositePlane.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void CompPlaneExtVariable(double *T1, double *T2, double *A)
{
    *T1 = CelsiusKelvin(inputDouble(1, 1, "hot surface temperature", "deg C"));
    
    *T2 = CelsiusKelvin(inputDouble(1, 1, "cold surface temperature", "deg C"));
    
    *A = inputDouble(0, 0, "heat transfer area", "m2");
}

void CompPlaneIntVariable(double *k, double *x)
{
    *k = inputDouble(0, 0, "thermal conductivity", "W/m.K");
    
    *x = inputDouble(0, 0, "layer thickness", "m");
}

/// MARK: GENERAL CALCULATIONS
double PlaneResistanceCalculation(double k, double A, double x)
{
    double R = 0.0;
    
    R = k*A;
    R = x/(R);
    
    return R;
}

double PlaneHeatCalculation(double R, double T1, double T2)
{
    double Q = 0.0;
    
    Q = T1 - T2;
    Q = (Q)/R;
    
    return Q;
}

double PlaneTempCalculation(double T1, double x, double k, double A, double Q)
{
    double T2 = 0.0;
    double sto = 0.0;
    
    T2 = x*Q;
    sto = k*A;
    T2 = (T2)/(sto);
    
    T2 = T1 - (T2);
    
    return T2;
}

int PlaneInterfaceLocater(int medium_ID)
{
    return medium_ID*250;   // 250 elements per medium
}

/// MARK: ARRAY FUNCTION
B48BDTemps CompPlaneCalculation(int numMediums, CondPlaneMedium data, double Q, double A, double T1, int *rowsused)
{
    B48BDTemps profile = {0.0};
    int i = 0;
    double interval = 0.0;
    int count = 0;      // Counter for the number of rows generated.
    int rownum = 0;     // Variable used to deal with changing locations.
    
    interval = data.x[0]/249;
    
    for(int j = 0; j < numMediums; ++j){
        rownum = PlaneInterfaceLocater(j);
        
        for(i = 0; i < 250; ++i)
        {
            int locstore = 0;
            double dx = 0.0;
            locstore = rownum + i;
            
            profile.k[locstore - 1] = data.k[j];
            if(i == 0 && j == 0){   // Setting the initial values.
                profile.x[locstore] = 0.0;
                profile.T[locstore] = T1;
            }else{
                profile.x[locstore] = profile.x[locstore - 1] + interval;
                dx = profile.x[locstore] - profile.x[locstore - 1];
                profile.T[locstore] = PlaneTempCalculation(profile.T[locstore - 1], dx, data.k[j], A, Q);
            }
            ++count;
        }
        interval = data.x[j+1]/250;
    }
    *rowsused = count;
    return profile;
}

/// MARK: DISPLAY AND WRITE
void CompPlaneDisplay(int numMediums, CondPlaneMedium data, double Q, double A, double T1, double T2, double rowsused, B48BDTemps profile)
{
    printf("_Composite_Plane_Results_\n");
    printf("\tInput parameters:\n");
    printf("Hot side temperature:\n");
    printf("T1 =\t%.3f\tdeg C\n", T1 - 273.15);
    printf("Cold side temperature:\n");
    printf("T2 =\t%.3f\tdeg C\n\n", T2 - 273.15);
    
    printf("Heat transfer area:\n");
    printf("A =\t%.3f\tm2\n\n", A);
    
    for(int j = 0; j < numMediums; ++j)
    {
        printf("Thermal conductivity of plane %d:\n", j + 1);
        printf("k_%d =\t%.3f\tW/m.K\n", j + 1, data.k[j]);
        printf("Thickness of layer %d:\n", j + 1);
        printf("x_%d =\t%.3f\tm\n\n", j + 1, data.x[j]);
        
        printf("Layer %d resistance to heat transfer:\n", j + 1);
        printf("R_%d =\t%.3f\tK/W\n\n", j + 1, data.R[j]);
    }
    
    printf("\tIntermediate parameters:\n");
    printf("Rate of heat transfer:\n");
    printf("Q =\t%.3f\tW\n\n", Q);
    
    printf("\tOutput parameters:\n");
    printf("k (W/m.K)\tx (mm)\tT (deg C)\n");
    for(int i = 0; i < rowsused; ++i){
        if(i == 0){
            printf("%.3f\t", profile.k[i]);
        }else{
            if(profile.k[i] == profile.k[i - 1])
            {
                printf("\t");
            }else{
                printf("%.3f\t", profile.k[i]);
            }
        }
        printf("%.3f\t", 1000*profile.x[i]);
        printf("%.3f\n", KelvinCelsius(profile.T[i]));
    }
}

void CompPlaneWrite(int numMediums, CondPlaneMedium data, double Q, double A, double T1, double T2, double rowsused, B48BDTemps profile)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Composite Plane Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Composite Plane Results");
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
    fprintf(fp, "_Composite_Plane_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Hot side temperature:\n");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n", T1 - 273.15);
    fprintf(fp, "Cold side temperature:\n");
    fprintf(fp, "T2 =\t%.3f\tdeg C\n\n", T2 - 273.15);
    
    fprintf(fp, "Heat transfer area:\n");
    fprintf(fp, "A =\t%.3f\tm2\n\n", A);
    
    for(int j = 0; j < numMediums; ++j)
    {
        fprintf(fp, "Thermal conductivity of plane %d:\n", j + 1);
        fprintf(fp, "k_%d =\t%.3f\tW/m.K\n", j + 1, data.k[j]);
        fprintf(fp, "Thickness of layer %d:\n", j + 1);
        fprintf(fp, "x_%d =\t%.3f\tm\n\n", j + 1, data.x[j]);
        
        fprintf(fp, "Layer %d resistance to heat transfer:\n", j + 1);
        fprintf(fp, "R_%d =\t%.3f\tK/W\n\n", j + 1, data.R[j]);
    }
    
    fprintf(fp, "\tIntermediate parameters:\n");
    fprintf(fp, "Rate of heat transfer:\n");
    fprintf(fp, "Q =\t%.3f\tW\n\n", Q);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "k (W/m.K)\tx (mm)\tT (deg C)\n");
    for(int i = 0; i < rowsused; ++i){
        if(i == 0){
            fprintf(fp, "%.3f\t", profile.k[i]);
        }else{
            if(profile.k[i] == profile.k[i - 1])
            {
                fprintf(fp, "\t");
            }else{
                fprintf(fp, "%.3f\t", profile.k[i]);
            }
        }
        fprintf(fp, "%.3f\t", 1000*profile.x[i]);
        fprintf(fp, "%.3f\n", KelvinCelsius(profile.T[i]));
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void CompPlaneSwitch(int mode, int numMediums, CondPlaneMedium data, double Q, double A, double T1, double T2, double rowsused, B48BDTemps profile)
{
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        char input[maxstrlen];
        if(mode == 1){
            printf("Do you want to view the results? ");
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
                    CompPlaneDisplay(numMediums, data, Q, A, T1, T2, rowsused, profile);
                }
                if(mode == 2){
                    CompPlaneWrite(numMediums, data, Q, A, T1, T2, rowsused, profile);
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
void CompositePlane(void)
{
    int whilmain = 0;
    printf("Composite Plane\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        char input[maxstrlen];
        int control = 0;
        int numMediums = 0;
        int rowsused = 0;
        
        double TotResist = 0.0;
        double Q = 0.0;
        B48BDTemps *profile = calloc(1, sizeof(B48BDTemps));
        
        double T1 = 0.0;
        double T2 = 0.0;
        double A = 0.0;
        CondPlaneMedium *data = calloc(1, sizeof(CondPlaneMedium));
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        CompPlaneExtVariable(&T1, &T2, &A);
        
        control = 1;
        while(control == 1)
        {
            printf("How many layers are present? [1 - 20] ");
            numMediums = atoi(fgets(input, sizeof(input), stdin));
            if(numMediums > 20){
                // Seg fault will occur.
                printf("This subroutine can only handle a maximum of 20 layers. Please enter an integer between 1 and 20.\n");
            }else{
                control = 0;
            }
        }
        for(int i = 0; i < numMediums; ++i)
        {
            CompPlaneIntVariable(&data->k[i], &data->x[i]);
        }
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        // Calculation function(s)
        for(int i = 0; i < numMediums; ++i)
        {
            data->R[i] = PlaneResistanceCalculation(data->k[i], A, data->x[i]);
            TotResist += data->R[i];
        }
        Q = PlaneHeatCalculation(TotResist, T1, T2);
        
        *profile = CompPlaneCalculation(numMediums, *data, Q, A, T1, &rowsused);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        CompPlaneSwitch(1, numMediums, *data, Q, A, T1, T2, rowsused, *profile);
        
        //  Writing to File
        CompPlaneSwitch(2, numMediums, *data, Q, A, T1, T2, rowsused, *profile);
        
        //  Continue function
        whilmain = Continue(whilmain);
        free(data);
        free(profile);
    }
    fflush(stdout);
}
