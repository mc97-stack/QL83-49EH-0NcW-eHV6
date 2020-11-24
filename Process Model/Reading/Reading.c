//
//  Reading.c
//  Process Model
//
//  Created by Matthew Cheung on 24/11/2020.
//

//  Standard header files
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//  Custom header files4
#include "main.h"
#include "Reading.h"

#define maxstrlen 128

void Reading()
{
    char input[maxstrlen];
    
    int control = 0;
    int selection = 0;
    
    control = 1;
    while(control == 1)
    {
        printf("Please select from the following books:\n");
        printf("1. The properties of gases and liquids - B. E. Poling, J. M. Prausitz and J. P. O'Connell.\n");
        
        printf("\nSelection [1]: ");
        selection = atoi(fgets(input, sizeof(input), stdin));
        switch(selection)
        {
            case 1:
                ThermoProps();
                break;
            case 0:
                control = 0;
                break;
            default:
                printf("Please enter an integer value.\n");
                break;
        }
    }
    
}
