//
//  06dIdealReactionComposition.c
//  Process Model
//
//  Created by Matthew Cheung on 27/11/2020.
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
#include "06dIdealReactionComposition.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define R 8.3145

/// MARK: VARIABLE INPUT
void ReactionVariable(double *P, double *Pref, double *T)
{
    *Pref = inputDouble(0, 0, "reference pressure", "atm");
    
    *P = inputDouble(0, 0, "system pressure", "kPa");
    *P = (*P)/101.325;  // Conversion to atm.
    
    *T = inputDouble(1, 1, "system temperature", "deg C");
    *T = (*T) + 273.15; // Conversion to K.
}

void SpeciesVariable(int type, double *initial, double *stoich, double *gibbs)
{
    if(type == 1)
    {
        *initial = inputDouble(1, 0, "initial moles of reagent i present", "mol");
    }
    if(type == 2)
    {
        *initial = inputDouble(1, 0, "initial moles of product i present", "mol");
    }
    
    *stoich = inputDouble(1, 1, "stoichiometric coefficient of species i", "");
    if(type == 1 && (*stoich) > 0)
    {
        // Reagent specified should have a negative stoichiometric coefficient.
        *stoich = -1*(*stoich);
    }
    if(type == 2 && (*stoich) < 0)
    {
        // Product specified should have a positive stoichiometric coefficient.
        *stoich = -1*(*stoich);
    }
    
    *gibbs = inputDouble(1, 1, "species-specific Gibbs free energy of formation", "J/ mol");
}

/// MARK: GENERAL CALCULATIONS
double CompositionCalculation(double species, double total, double stoich, double stoichtotal, double EoR)
{
    double y = 0.0;
    double num = 0.0;
    double den = 0.0;
    
    num = stoich*EoR;
    num = species + (num);
    
    den = stoichtotal*EoR;
    den = total + (den);
    
    y = (num)/(den);
    
    return y;
}

double SpeciesGibbsEgyCalc(double molestotal, double gibbs, double T, double P, double Pref, double comp)
{
    double mu = 0.0;
    double sto = 0.0;
    double n = 0.0;
    
    n = comp*molestotal;
    
    mu = gibbs*n;
    
    sto = P/Pref;
    sto = log(sto);
    sto = T*(sto);
    sto = R*(sto);
    sto = n*(sto);
    mu = (mu) + (sto);
    
    sto = log(comp);
    sto = T*(sto);
    sto = R*(sto);
    sto = n*(sto);
    mu = (mu) + (sto);
    
    return mu;
}

double EquilibriumConstantCalc(species products, species reagents, int numprods, int numreags, double T)
{
    double K = 0.0;     // Equilibrium constant
    double sto = 0.0;
    
    for(int i = 0; i < numprods; ++i)
    {
        sto += (products.stoich[i])*(products.gibbs[i]);
    }
    for(int i = 0; i < numreags; ++i)
    {
        sto += (reagents.stoich[i])*(reagents.gibbs[i]);
    }
    
    K = R*T;
    K = (sto)/(K);
    K = -1*(K);
    K = exp(K);
    
    return K;
}

/// MARK: ARRAY FUNCTION
GibbsRxn GibbsMixing(species reagents, species products, int numreags, int numprods, double totalmoles, double totalstoich, double T, double P, double Pref)
{
    double sto = 0.0;
    GibbsRxn table = {0.0};
    
    // Initialising the extent of reaction.
    for(int i = 0; i < 1001; ++i)
    {
        table.EoR[i] = (double)i/1000;
    }
    // Calculating chemical species compositions
    for(int i = 0; i < 1001; ++i){
        for(int j = 0; j < numreags; ++j)
        {
            table.reags[j][i] = CompositionCalculation(reagents.initial[j], totalmoles, reagents.stoich[j], totalstoich, table.EoR[i]);
        }
    }
    for(int i = 0; i < 1001; ++i){
        for(int j = 0; j < numprods; ++j)
        {
            table.prods[j][i] = CompositionCalculation(products.initial[j], totalmoles, products.stoich[j], totalstoich, table.EoR[i]);
        }
    }
    // Calculating species chemical potentials
    for(int i = 0; i < 1001; ++i){
        for(int j = 0; j < numreags; ++j)
        {
            table.reagsmu[j][i] = SpeciesGibbsEgyCalc(totalmoles, reagents.gibbs[j], T, P, Pref, table.reags[j][i]);
        }
    }
    for(int i = 0; i < 1001; ++i){
        for(int j = 0; j < numprods; ++j)
        {
            table.prodsmu[j][i] = SpeciesGibbsEgyCalc(totalmoles, products.gibbs[j], T, P, Pref, table.prods[j][i]);
        }
    }
    
    // Calculating the Gibbs energy of mixing
    
    for(int i = 0; i < 1001; ++i){
        for(int j = 0; j < numprods; ++j)
        {
            table.Gmix[i] += table.prodsmu[j][i];
        }
    }
    
    for(int i = 0; i < 1001; ++i){
        for(int j = 0; j < numreags; ++j)
        {
            table.Gmix[i] += table.reagsmu[j][i];
        }
    }
    
    for(int i = 0; i < 1001; ++i){
        for(int j = 0; j < numreags; ++j)
        {
            sto = (table.reags[j][i])*totalmoles;   // moles of species i.
            sto = (table.reagsmu[j][i])/(sto);      // Chemical potential.
            sto = (reagents.stoich[j]) * (sto);     // Equilibrium condition.
            table.Cond[i] += sto;
            sto = 0.0;
        }
    }
    for(int i = 0; i < 1001; ++i){
        for(int j = 0; j < numprods; ++j)
        {
            sto = (table.prods[j][i])*totalmoles;   // moles of species i.
            sto = (table.prodsmu[j][i])/(sto);      // Chemical potential.
            sto = (reagents.stoich[j]) * (sto);     // Equilibrium condition.
            table.Cond[i] += sto;
            sto = 0.0;
        }
    }
    return table;
}

/// MARK: DISPLAY AND WRITE
void IdealRxnCompDisplay(species reagents, species products, int numreags, int numprods, double totalmoles, double T, double P, double Pref, GibbsRxn results, double K, double KP, double stoichtotal)
{
    printf("_Ideal_Reaction_Composition_\n");
    printf("\tInput parameters:\n");
    printf("Reference Pressure:\n");
    printf("Pref =\t%.3f\tatm\n\n", Pref);
    
    printf("System Pressure:\n");
    printf("P =\t%.3f\tatm\n", P);
    printf("System Temperature:\n");
    printf("T =\t%.3f\tdeg C\n\n", T - 273.15);
    
    printf("Total moles present:\n");
    printf("n =\t%.3f\tmol\n\n", totalmoles);
    
    printf("Equilibrium constant:\n");
    printf("K =\t%.3f\t[ ]\n\n", K);
    printf("KP =\t%.3f\tbar^%.2f\n\n", KP, stoichtotal);
    
    printf("Reagents stoichiometry:\n");
    for(int i = 0; i < numreags; ++i)
    {
        printf("v_%d =\t%.2f\n", i + 1, reagents.stoich[i]);
    }
    for(int i = 0; i < numprods; ++i)
    {
        printf("v_%d =\t%.2f\n", i + numreags + 1, products.stoich[i]);
    }
    
    printf("\tOutput parameters:\n");
    printf("\\varepsilon (mol)\t\t");
    
    for(int i = 0; i < numreags; ++i)
    {
        printf("x_%d\t", i + 1);
        printf("mu_%d\t", i + 1);
    }
    printf("\t");
    
    for(int i = 0; i < numprods; ++i)
    {
        printf("x_%d\t", i + numreags + 1);
        printf("mu_%d\t", i + numreags + 1);
    }
    printf("\t");
    
    printf("G^{mix} (J)\t\t");
    
    printf("\\sum_i \\mu_i v_i\n");
    
    for(int i = 0; i < 1001; ++i){
        printf("%.3f\t\t", results.EoR[i]);
        
        for(int j = 0; j < numreags; ++j)
        {
            printf("%.5f\t", results.reags[j][i]);
            printf("%.5f\t", results.reagsmu[j][i]);
        }
        printf("\t");
        
        for(int j = 0; j < numprods; ++j)
        {
            printf("%.5f\t", results.prods[j][i]);
            printf("%.5f\t", results.prodsmu[j][i]);
        }
        printf("\t");
        
        printf("%.3f\t\t", results.Gmix[i]);
        
        printf("%.3f\n", results.Cond[i]);
    }
}

void IdealRxnCompWrite(species reagents, species products, int numreags, int numprods, double totalmoles, double T, double P, double Pref, GibbsRxn results, double K, double KP, double totalstoich)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    char fileconds[maxstrlen];
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Ideal Reaction Composition
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Ideal Reaction Composition");
    //printf("File name: \"%s\"\n", filename);
    
    sprintf(fileconds, " T %.0f K", T);
    strcat(filename, fileconds);
    
    sprintf(fileconds, " P %.0f atm", P);
    strcat(filename, fileconds);
    
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
    fprintf(fp, "_Ideal_Reaction_Composition_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Reference Pressure:\n");
    fprintf(fp, "Pref =\t%.3f\tatm\n\n", Pref);
    
    fprintf(fp, "System Pressure:\n");
    fprintf(fp, "P =\t%.3f\tatm\n", P);
    fprintf(fp, "System Temperature:\n");
    fprintf(fp, "T =\t%.3f\tdeg C\n\n", T - 273.15);
    
    printf("Total moles present:\n");
    printf("n =\t%.3f\tmol\n\n", totalmoles);
    
    fprintf(fp, "Equilibrium constant:\n");
    fprintf(fp, "K =\t%.3f\t[ ]\n\n", K);
    fprintf(fp, "KP =\t%.3f\tbar^%.2f\n\n", KP, totalstoich);
    
    fprintf(fp, "Reagents stoichiometry:\n");
    for(int i = 0; i < numreags; ++i)
    {
        fprintf(fp, "v_%d =\t%.2f\n", i + 1, reagents.stoich[i]);
    }
    for(int i = 0; i < numprods; ++i)
    {
        fprintf(fp, "v_%d =\t%.2f\n", i + numreags + 1, products.stoich[i]);
    }
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "\\varepsilon (mol)\t\t");
    
    for(int i = 0; i < numreags; ++i)
    {
        fprintf(fp, "x_%d\t", i + 1);
        fprintf(fp, "mu_%d\t", i + 1);
    }
    fprintf(fp, "\t");
    
    for(int i = 0; i < numprods; ++i)
    {
        fprintf(fp, "x_%d\t", i + numreags + 1);
        fprintf(fp, "mu_%d\t", i + numreags + 1);
    }
    fprintf(fp, "\t");
    
    fprintf(fp, "G^{mix} (J)\t\t");
    
    fprintf(fp, "\\sum_i \\mu_i v_i\n");
    
    for(int i = 0; i < 1001; ++i){
        fprintf(fp, "%.3f\t\t", results.EoR[i]);
        
        for(int j = 0; j < numreags; ++j)
        {
            fprintf(fp, "%.5f\t", results.reags[j][i]);
            fprintf(fp, "%.5f\t", results.reagsmu[j][i]);
        }
        fprintf(fp, "\t");
        
        for(int j = 0; j < numprods; ++j)
        {
            fprintf(fp, "%.5f\t", results.prods[j][i]);
            fprintf(fp, "%.5f\t", results.prodsmu[j][i]);
        }
        fprintf(fp, "\t");
        
        fprintf(fp, "%.3f\t\t", results.Gmix[i]);
        
        fprintf(fp, "%.3f\n", results.Cond[i]);
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void IdealRxnCompSwitch(int mode, species reagents, species products, int numreags, int numprods, double totalmoles, double T, double P, double Pref, GibbsRxn results, double K, double KP, double totalstoich)
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
                    IdealRxnCompDisplay(reagents, products, numreags, numprods, totalmoles, T, P, Pref, results, K, KP, totalstoich);
                }
                if(mode == 2)
                {
                    IdealRxnCompWrite(reagents, products, numreags, numprods, totalmoles, T, P, Pref, results, K, KP, totalstoich);
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
void IdealReactionCompostion(void)
{
    int whilmain = 0;
    printf("Ideal Reaction Composition\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        char input[maxstrlen];
        int control = 0;
        int graph = 0;
        int cont = 0;
        
        GibbsRxn *table = calloc(1, sizeof(GibbsRxn));
        double Pref = 0.0;
        double P = 0.0;
        double T = 0.0;
        double K = 0.0;     // Equilibrium constant (Temperature adjustment).
        double KP = 0.0;    // Equilibrium constant (Pressure adjustment).
        double stoichtotal = 0.0;
        double molestotal = 0.0;
        
        int numreags = 0;   // Number of reagents.
        int numprods = 0;   // Number of products.
        
        species *reagents = calloc(1, sizeof(species));
        species *products = calloc(1, sizeof(species));
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        control = 1;
        while(control == 1)
        {
            printf("How many reagents are present? ");
            numreags = atoi(fgets(input, sizeof(input), stdin));
            if(numreags != 0 && numreags < 12)
            {
                control = 0;
            }else{
                printf("Please enter a value between 1 and 12.");
            }
        }
        
        control = 1;
        while(control == 1)
        {
            printf("How many products are present? ");
            numprods = atoi(fgets(input, sizeof(input), stdin));
            if(numprods != 0 && numprods < 12)
            {
                control = 0;
            }else{
                printf("Please enter a value between 1 and 12.");
            }
        }
        ReactionVariable(&P, &Pref, &T);
        
        printf("Reagent Variables:\n");
        for(int i = 0; i < numreags; ++i)
        {
            SpeciesVariable(1, &reagents->initial[i], &reagents->stoich[i], &reagents->gibbs[i]);
        }
        printf("\nProduct Variables:\n");
        for(int i = 0; i < numprods; ++i)
        {
            SpeciesVariable(2, &products->initial[i], &products->stoich[i], &products->gibbs[i]);
        }
        graph = 1;
        while(graph == 1)
        {
            //  Data Manipulation
            clock_getres(CLOCK_MONOTONIC, &start);
            clock_gettime(CLOCK_MONOTONIC, &start);
            
            // Calculation function(s)
            // Calculating overall stoichiometric coefficient.
            stoichtotal = 0.0;
            molestotal = 0.0;
            for(int i = 0; i < numreags; ++i)
            {
                stoichtotal += reagents->stoich[i];
            }
            for(int i = 0; i < numprods; ++i)
            {
                stoichtotal += products->stoich[i];
            }
            
            // Calculating total moles present
            for(int i = 0; i < numreags; ++i)
            {
                molestotal += reagents->initial[i];
            }
            for(int i = 0; i < numprods; ++i)
            {
                molestotal += products->initial[i];
            }
            *table = GibbsMixing(*reagents, *products, numreags, numprods, molestotal, stoichtotal, T, P, Pref);
            
            K = EquilibriumConstantCalc(*products, *reagents, numprods, numreags, T);
            KP = pow(Pref, stoichtotal);
            KP = (KP)*(K);
            
            clock_getres(CLOCK_MONOTONIC, &end);
            clock_gettime(CLOCK_MONOTONIC, &end);

            elapsed = timer(start, end);

            printf("Calculations completed in %.6f seconds.\n", elapsed);
            
            //  Displaying results
            IdealRxnCompSwitch(1, *reagents, *products, numreags, numprods, molestotal, T, P, Pref, *table, K, KP, stoichtotal);
            
            //  Writing to File
            IdealRxnCompSwitch(2, *reagents, *products, numreags, numprods, molestotal, T, P, Pref, *table, K, KP, stoichtotal);
            
            control = 1;
            while(control == 1)
            {
                printf("Do you want to change the system conditions? ");
                fgets(input, sizeof(input), stdin);
                switch(input[0])
                {
                    case '1':
                    case 'T':
                    case 'Y':
                    case 't':
                    case 'y':
                        cont = 1;
                        while(cont == 1)
                        {
                            printf("Which variable do you want to change?\n");
                            printf("1. System pressure.\n");
                            printf("2. System temperature.\n");
                            printf("3. Initial composition.\n");
                            printf("Selection [1 - 3]: ");
                            fgets(input, sizeof(input), stdin);
                            switch(input[0])
                            {
                                case '1':
                                    P = inputDouble(0, 0, "system pressure", "kPa");
                                    P = (P)/101.325;
                                    break;
                                case '2':
                                    T = inputDouble(1, 1, "system temperature", "deg C");
                                    T = (T)+273.15;
                                    break;
                                case '3':
                                    printf("Reagent Variables:\n");
                                    for(int i = 0; i < numreags; ++i)
                                    {
                                        reagents->initial[i] = inputDouble(1, 0, "initial moles of reagent i present", "mol");
                                    }
                                    printf("\nProduct Variables:\n");
                                    for(int i = 0; i < numprods; ++i)
                                    {
                                        products->initial[i] = inputDouble(1, 0, "initial moles of product i present", "mol");
                                    }
                                    break;
                                default:
                                    printf("Input not recognised. Please enter an integer between 1 and 3.\n");
                                    break;
                            }
                            
                            printf("Do any other system conditions need changing? [Y/N] ");
                            fgets(input, sizeof(input), stdin);
                            switch(input[0])
                            {
                                case '1':
                                case 'Y':
                                case 'y':
                                    break;
                                case '0':
                                case 'N':
                                case 'Q':
                                case 'n':
                                case 'q':
                                    cont = 0;
                                    break;
                            }
                        }
                        control = 0;
                        break;
                    case '0':
                    case 'F':
                    case 'N':
                    case 'f':
                    case 'n':
                        graph = 0;
                        control = 0;
                        break;
                    default:
                        printf("Input not recognised\n");
                        break;
                }
            }
        }
        
        //  Continue function
        whilmain = Continue(whilmain);
        free(reagents);
        free(products);
        free(table);
    }
    fflush(stdout);
}
