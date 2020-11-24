//
//  ThermophysicalProperties.c
//  Process Model
//
//  Created by Matthew Cheung on 24/11/2020.
//

#include <stdio.h>
#include <stdlib.h>

#include "ThermophysicalProperties.h"

#define maxstrlen 128

void ThermoProps()
{
    char input[maxstrlen];
    int selection = 0;
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        printf("Thermophysical Properties\n\n");
        printf("Please make a selection from the following chapters:\n");
        printf("1. Acentric factor calculation\n");
        printf("2. P-V-T relations for pure component gas or liquid.\n");
        printf("3. Volumetric properties applied to mixtures.\n");
        printf("4. Thermodynamic properties.\n");
        printf("5. Ideal gas thermodynamic properties.\n");
        printf("6. Vapour pressure and vapourisation enthalpies.\n");
        printf("7. Multicomponent phase equilibria.\n");
        printf("8. Viscosity.\n");
        printf("9. Thermal conductivity.\n");
        printf("10. Diffusion coefficients.\n");
        printf("11. Surface tension.\n");
        printf("0. Exit menu.\n\n");
        
        printf("Selection [1 - 11]: ");
        selection = atoi(fgets(input, sizeof(input), stdin));
        switch(selection){
            case 1:
                pureComponentConstants();
                break;
            case 2:
                statePropertyRelations();
                break;
            case 3:
                //mixtures();
                printf("Bear with me, this is still being written...\n");
                break;
            case 4:
                //thermodynamicProperties();
                printf("Bear with me, this is still being written...\n");
                break;
            case 5:
                //idealGasThermodynamicProperties();
                printf("Bear with me, this is still being written...\n");
                break;
            case 6:
                //Vaporisation();
                printf("Bear with me, this is still being written...\n");
                break;
            case 7:
                //multiphaseEquilibria();
                printf("Bear with me, this is still being written...\n");
                break;
            case 8:
                //Viscosity();
                printf("Bear with me, this is still being written...\n");
                break;
            case 9:
                //thermalConductivity();
                printf("Bear with me, this is still being written...\n");
                break;
            case 10:
                //diffusivity();
                printf("Bear with me, this is still being written...\n");
                break;
            case 11:
                //surfaceTension();
                printf("Bear with me, this is still being written...\n");
                break;
            case 0:
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer value between 1 and 11.\n");
                break;
        }
    }
    fflush(stdout);
}
