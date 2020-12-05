//
//  02dCompositePipe.c
//  Process Model
//
//  Created by Matthew Cheung on 05/12/2020.
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
#include "02bCompositeCylinder.h"
#include "02dCompositePipe.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void CompPipeExtVariable(double *T1, double *T2, double *L, double *r1)
{
    *T1 = CelsiusKelvin(inputDouble(1, 1, "hot surface temperature", "deg C"));
    
    *T2 = CelsiusKelvin(inputDouble(1, 1, "cold surface temperature", "deg C"));
    
    *L = inputDouble(0, 0, "pipe length", "m");
    
    *r1 = inputDouble(0, 0, "innermost cylinder radius", "mm");
    *r1 = (*r1)*0.001;  // Conversion (mm to m)
}

void CondIntVariable(PipeMedium data, int i, double *k, double *r)
{
    int control = 0;
    *k = inputDouble(0, 0, "thermal conductivity", "W/m.K");
    
    control = 1;
    while(control == 1)
    {
        *r = inputDouble(0, 0, "layer outer radius", "mm");
        *r = (*r)*0.001;  // Conversion (mm to m)
        
        if(*r < data.r[i - 1])
        {
            // Radius given is smaller than previous.
            printf("Please enter a radius that it bigger that %.2f mm.\n", 1000*data.r[i - 1]);
        }else{
            control = 0;
        }
    }
}

void ConvIntVariable(double *h)
{
    *h = inputDouble(0, 0, "fluid heat transfer coefficient", "W/m2.K");
}

/// MARK: GENERAL CALCULATIONS
double ConvResistanceCalculation(double h, double r)
{
    double R = 0.0;
    
    R = pow(r, 2);
    R = M_PI*(R);
    R = h*(R);
    
    R = 1/(R);
    
    return R;
}

double PipeHeatCalculation(double R, double T1, double T2)
{
    double Q = 0.0;
    
    Q = T1 - T2;
    Q = (Q)/R;
    
    return Q;
}

double ConvTempCalculation(double R, double Q, double T1)
{
    double T2 = 0.0;
    
    T2 = Q*R;
    T2 = T1 - (T2);
    
    return T2;
}

/// MARK: ARRAY FUNCTION
TempProfile CompPipeCalculation(int numMediums, PipeMedium data, double T1, double r1, double L, double Q, int *rowsused)
{
    TempProfile profile = {0.0};
    double interval = 0.0;
    double R = 0.0;
    int count = 0;
    
    // Setting initial values
    profile.r[0] = r1;
    profile.T[0] = T1;
    ++count;
    
    for(int j = 1; j < numMediums + 1; ++j)
    {
        if(data.k[j] == 0.0)
        {
            // Using fluid heat transfer coefficient.
            profile.h[count] = data.h[j];
            profile.r[count] = data.r[j];
            R = ConvResistanceCalculation(profile.h[count], profile.r[count]);
            profile.T[count] = ConvTempCalculation(R, Q, profile.T[count - 1]);
            ++count;
        }else{
            interval = data.r[j] - data.r[j - 1];
            interval = (interval)/250;
            // Using thermal conductivity.
            for(int i = 0; i < 250; ++i)
            {
                profile.k[count] = data.k[j];
                profile.r[count] = profile.r[count - 1] + interval;
                R = CylResistanceCalculation(profile.k[count], L, profile.r[count - 1], profile.r[count]);
                profile.T[count] = CylTempCalculation(profile.T[count - 1], R, Q);
                ++count;
            }
        }
    }
    
    *rowsused = count;
    return profile;
}

/// MARK: DISPLAY AND WRITE
void CompPipeDisplay(int numMediums, PipeMedium data, double Q, double L, double T1, double T2, int rowsused, TempProfile profile)
{
    printf("_Composite_Pipe_Results_\n");
    printf("\tInput parameters:\n");
    printf("Hot side temperature:\n");
    printf("T1 =\t%.3f\tdeg C\n", T1 - 273.15);
    printf("Cold side temperature:\n");
    printf("T2 =\t%.3f\tdeg C\n\n", T2 - 273.15);
    
    printf("Pipe length:\n");
    printf("L =\t%.3f\tm\n\n", L);
    
    printf("Inner radius:\n");
    printf("r_1 =\t%.3f\tm\n\n", data.r[0]);
    
    for(int j = 1; j < numMediums+1; ++j)
    {
        if(data.k[j] == 0.0){
            printf("Fluid heat transfer coefficient of layer %d:\n", j);
            printf("h_%d =\t%.3f\tW/m2.K\n", j, data.h[j]);
        }else{
            printf("Thermal conductivity of layer %d:\n", j);
            printf("k_%d =\t%.3f\tW/m.K\n", j, data.k[j]);
        }
        printf("Outer radius of layer %d:\n", j);
        printf("r_%d =\t%.3f\tm\n\n", j + 1, data.r[j]);
        
        printf("Layer %d resistance to heat transfer:\n", j);
        printf("R_%d =\t%.3f\tK/W\n\n", j + 1, data.R[j]);
    }
    
    printf("\tIntermediate parameters:\n");
    printf("Rate of heat transfer:\n");
    printf("Q =\t%.3f\tW\n\n", Q);
    
    printf("\tOutput parameters:\n");
    printf("k (W/m.K)\th (W/m2.K)\tr (mm)\tT (deg C)\n");
    for(int i = 0; i < rowsused; ++i)
    {
        if(i > 0 && profile.k[i - 1] == profile.k[i]){
            printf("\t");
        }else{
            printf("%.3f\t", profile.k[i]);
        }
        if(i > 0 && profile.h[i - 1] == profile.h[i]){
            printf("\t");
        }else{
            printf("%.3f\t", profile.h[i]);
        }
        printf("%.5f\t", 1000*profile.r[i]);
        printf("%.5f\n", KelvinCelsius(profile.T[i]));
    }
}

void CompPipeWrite(int numMediums, PipeMedium data, double Q, double L, double T1, double T2, int rowsused, TempProfile profile)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Composite Pipe Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Composite Pipe Results");
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
    fprintf(fp, "_Composite_Pipe_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Hot side temperature:\n");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n", T1 - 273.15);
    fprintf(fp, "Cold side temperature:\n");
    fprintf(fp, "T2 =\t%.3f\tdeg C\n\n", T2 - 273.15);
    
    fprintf(fp, "Pipe length:\n");
    fprintf(fp, "L =\t%.3f\tm\n\n", L);
    
    fprintf(fp, "Inner radius:\n");
    fprintf(fp, "r_1 =\t%.3f\tm\n\n", data.r[0]);
    
    for(int j = 1; j < numMediums+1; ++j)
    {
        if(data.k[j] == 0.0){
            fprintf(fp, "Fluid heat transfer coefficient of layer %d:\n", j);
            fprintf(fp, "h_%d =\t%.3f\tW/m2.K\n", j, data.h[j]);
        }else{
            fprintf(fp, "Thermal conductivity of layer %d:\n", j);
            fprintf(fp, "k_%d =\t%.3f\tW/m.K\n", j, data.k[j]);
        }
        fprintf(fp, "Outer radius of layer %d:\n", j);
        fprintf(fp, "r_%d =\t%.3f\tm\n\n", j + 1, data.r[j]);
        
        fprintf(fp, "Layer %d resistance to heat transfer:\n", j);
        fprintf(fp, "R_%d =\t%.3f\tK/W\n\n", j + 1, data.R[j]);
    }
    
    fprintf(fp, "\tIntermediate parameters:\n");
    fprintf(fp, "Rate of heat transfer:\n");
    fprintf(fp, "Q =\t%.3f\tW\n\n", Q);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "k (W/m.K)\th (W/m2.K)\tr (mm)\tT (deg C)\n");
    for(int i = 0; i < rowsused; ++i)
    {
        if(i > 0 && profile.k[i - 1] == profile.k[i]){
            fprintf(fp, "\t");
        }else{
            fprintf(fp, "%.3f\t", profile.k[i]);
        }
        if(i > 0 && profile.h[i - 1] == profile.h[i]){
            fprintf(fp, "\t");
        }else{
            fprintf(fp, "%.3f\t", profile.h[i]);
        }
        fprintf(fp, "%.5f\t", 1000*profile.r[i]);
        fprintf(fp, "%.5f\n", KelvinCelsius(profile.T[i]));
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void CompPipeSwitch(int mode, int numMediums, PipeMedium data, double Q, double L, double T1, double T2, int rowsused, TempProfile profile)
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
                    CompPipeDisplay(numMediums, data, Q, L, T1, T2, rowsused, profile);
                }
                if(mode == 2){
                    CompPipeWrite(numMediums, data, Q, L, T1, T2, rowsused, profile);
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
void CompositePipe(void)
{
    int whilmain = 0;
    printf("Composite Pipe\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        char input[maxstrlen];
        int control = 0;
        int numMediums = 0;
        int rows = 0;
        
        double R = 0.0;
        double Q = 0.0;
        TempProfile *profile = calloc(1, sizeof(TempProfile));
        
        double T1 = 0.0;
        double T2 = 0.0;
        double L = 0.0;
        PipeMedium *data = calloc(1, sizeof(PipeMedium));
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        CompPipeExtVariable(&T1, &T2, &L, &data->r[0]);
        
        for(int j = 1; j < 21; ++j)
        {
            control = 1;
            while(control == 1)
            {
                printf("Please select the physical state of layer %d:\n", j);
                printf("1. Fluid.\n");
                printf("2. Solid.\n");
                if(j != 1){
                    printf("0. All layers entered.\n");
                    printf("Selection [0 - 2]: ");
                }else{
                    printf("Selection [1 - 2]: ");
                }
                fgets(input, sizeof(input), stdin);
                switch(input[0])
                {
                    case '1':
                        ConvIntVariable(&data->h[j]);
                        data->r[j] = data->r[j - 1];
                        ++numMediums;
                        control = 0;
                        break;
                    case '2':
                        CondIntVariable(*data, j, &data->k[j], &data->r[j]);
                        ++numMediums;
                        control = 0;
                        break;
                    case '0':
                        if(j == 1){
                            printf("Input not recognised. Please try again.\n");
                        }else{
                            goto done;
                        }
                        break;
                    default:
                        printf("Input not recognised. Please try again.\n");
                        break;
                }
            }
        }
    done:
        fflush(stdout);
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        // Calculation function(s)
        for(int i  = 1; i < numMediums + 1; ++i)
        {
            if(data->k[i] == 0)
            {
                // Using fluid heat transfer coefficient.
                data->R[i] = ConvResistanceCalculation(data->h[i], data->r[i]);
            }else{
                // Using thermal conductivity.
                data->R[i] = CylResistanceCalculation(data->k[i], L, data->r[i - 1], data->r[i]);
            }
            R += data->R[i];
        }
        
        Q = PipeHeatCalculation(R, T1, T2);
        
        *profile = CompPipeCalculation(numMediums, *data, T1, data->r[0], L, Q, &rows);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        CompPipeSwitch(1, numMediums, *data, Q, L, T1, T2, rows, *profile);
        
        //  Writing to File
        CompPipeSwitch(2, numMediums, *data, Q, L, T1, T2, rows, *profile);
        
        //  Continue function
        whilmain = Continue(whilmain);
        free(data);
        free(profile);
    }
    fflush(stdout);
}
