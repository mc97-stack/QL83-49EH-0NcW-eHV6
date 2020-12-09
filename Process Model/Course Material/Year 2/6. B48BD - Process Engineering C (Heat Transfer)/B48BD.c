//
//  B48BD.c
//  Process Model
//
//  Created by Matthew Cheung on 29/11/2020.
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

//  Standard header files
#include <stdio.h>
#include <stdlib.h>

//  Custom header files
#include "Courses.h"
#include "B48BDMenu.h"
#include "B48BD_T1.h"
#include "B48BD_T2.h"
#include "B48BD_T3.h"

#define maxstrlen 128

void B48BDTopComm(){
    printf("Please select from the following programs: \n");
}

void B48BDtopic1(){
    char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1){
        B48BDTopComm();
        printf("1. Temperature conversion.\n");
        printf("2. Heat transfer by conduction.\n");
        printf("3. Heat transfer by convection.\n");
        printf("4. Heat transfer by radiation.\n\n");
        
        printf("q. Exit topic.\n");
        printf("Selection [1 - 4]: ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
                TemperatureConversion();
                break;
            case '2':
                Conduction();
                break;
            case '3':
                Convection();
                break;
            case '4':
                Radiation();
                break;
            case '0':
            case 'Q':
            case 'q':
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer value between 1 and 4.\n");
                break;
        }
    }
}

void B48BDtopic2(){
    char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1){
        B48BDTopComm();
        printf("1. Composite plane.\n");
        printf("2. Composite cylinder.\n");
        printf("3. Composite sphere.\n");
        printf("4. Composite cylinder (fluid flow).\n");
        
        printf("q. Exit topic.\n");
        printf("Selection [1 - 4]: ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
                CompositePlane();
                break;
            case '2':
                CompositeCylinder();
                break;
            case '3':
                CompositeSphere();
                break;
            case '4':
                CompositePipe();
                break;
            case '0':
            case 'Q':
            case 'q':
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer value between 1 and 4.\n");
                break;
        }
    }
}

void B48BDtopic3(){
    char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1){
        B48BDTopComm();
        printf("1. Lagging thickness.\n");
        printf("2. Film heat transfer coefficient.\n");
        printf("3. Monochromatic emissive power (Planck's distribution law).\n");
        
        printf("q. Exit topic.\n");
        printf("Selection [1 - 3]: ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
                Lagging();
                break;
            case '2':
                FilmHTCoefficient();
                break;
            case '3':
                RadWavelength();
                break;
            case '4':
            case '0':
            case 'Q':
            case 'q':
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer value between 1 and 4.\n");
                break;
        }
    }
}

void B48BDtopic4(){
    //char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1){
        B48BDTopComm();
        control = 0;
    }
}

void B48BDtopic5(){
    //char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1){
        B48BDTopComm();
        control = 0;
    }
}

void B48BDtopic6(){
    //char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1){
        B48BDTopComm();
        control = 0;
    }
}

void B48BD(){
    char input[maxstrlen];      // Variable where character input is stored.
    int control = 0;            // Variable used to control user input.
    printf("Process Engineering B - Heat Transfer \n\n");
    
    control = 1;
    while(control == 1){
        printf("Please select from the following topics:\n");
        printf("T1: Introduction to Heat Transfer\nT2: Thermal Conduction\nT3: Convection and Radiation\nT4: Heat Transfer Equipment\nT5: Heat Exchanger Design\nT6: Boiling and Condensation\n\nq. Quit course\n\n");
        printf("Topic ");
        fgets(input,sizeof(input),stdin);
        switch(input[0]){
            case '1':
                B48BDtopic1();
                break;
            case '2':
                B48BDtopic2();
                break;
            case '3':
                B48BDtopic3();
                break;
            case '4':
                B48BDtopic4();
                break;
            case '5':
                B48BDtopic5();
                break;
            case '6':
                B48BDtopic6();
                break;
            case '0':
            case 'Q':
            case 'q':
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer between 1 and 6.\n");
                break;
        }
        fflush(stdout);
    }
}
