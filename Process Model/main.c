//
//  main.c
//  Process Model
//
//  Created by Matthew Cheung on 23/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

//  Standard header files
#include <stdio.h>
#include <stdlib.h>

//  Custom header files
#include "main.h"
#include "ThermophysicalProperties.h"

#define maxstrlen 128

void MinorUnitOps()
{
    printf("Minor\n\n");
}

void MajorUnitOps()
{
    printf("Major\n\n");
}

void CourseSelection()
{
    char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        printf("Which year would you like to enter or 'q' to exit selection? [1 - 4]\n\n");
        printf("Year ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
                Year1();
                break;
            case '2':
                Year2();
                break;
            case '3':
                Year3();
                break;
            case '4':
                Year4();
                break;
            case '0':
            case 'Q':
            case 'q':
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer between 1 and 4.\n");
                break;
        }
        fflush(stdout);
    }
    fflush(stdout);
}

void ThermoProps()
{
    char input[maxstrlen];
    int selection = 0;
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        printf("Primary source where information was collected from:\n");
        printf("The Properties of Gases && Liquids (4th Ed.) - Reid, Prausnitz and Poling.\n\n");
        printf("Thermophysical Properties\n\n");
        printf("Please make a selection from the following areas:\n");
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
    
    
}

void DynProcessSim()
{
    printf("Dynamic Process Simulator\n\n");
}

void NiceThings()
{
    printf("Bonus Content!\n\n");
}

int main()
{
    printf("_Process Model - alpha build_\n");
    printf("Copyright (C) 2020  Matthew Cheung \nThis program comes with ABSOL");
    printf("UTELY NO WARRANTY; \nThis is free software, and you are welcome to ");
    printf("redistribute it\nunder certain conditions; Type '7' for full licensing details\n\n");
    
    char MainSelect[maxstrlen];
    
    int whilmain = 0;
    
    //Main menu for program
    whilmain = 1;
    while(whilmain == 1)
    {
        printf("Please select from the following options:\n");
        printf("1. Minor Unit Operations\n");
        printf("2. Major Unit Operations\n");
        printf("3. Course Files\n");
        printf("4. Thermophysical Properties\n");
        printf("5. Dynamic Process Simulation\n");
        printf("6. Other nice things\n");
        printf("7. GNU General Public License\n");
        printf("q. Exit Program\n\n");
        printf("Selection [3 - 4, 7]: ");
        fflush(stdout);
        fgets(MainSelect, sizeof(MainSelect), stdin);
        switch(MainSelect[0])
        {
            case '1':
                MinorUnitOps();
                break;
            case '2':
                MajorUnitOps();
                break;
            case '3':
                CourseSelection();
                break;
            case '4':
                ThermoProps();
                break;
            case '5':
                DynProcessSim();
                break;
            case '6':
                NiceThings();
                break;
            case '7':
                License();
                break;
            case '0':
            case 'Q':
            case 'q':
                whilmain = 0;
                break;
            default:
                printf("Input not recognised. Please enter either '3' or '4'.\n");
                break;
        }
    }
    return 0;
}
