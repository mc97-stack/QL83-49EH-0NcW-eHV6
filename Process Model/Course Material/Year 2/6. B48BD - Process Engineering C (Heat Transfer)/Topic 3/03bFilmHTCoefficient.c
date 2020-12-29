//
//  03bFilmHTCoefficient.c
//  Process Model
//
//  Created by Matthew Cheung on 19/12/2020.
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
#include "B48BD_T3.h"
#include "03bFilmHTCoefficient.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: PSEUDO-MAIN FUNCTION
void FluidHTCoefficient(void)
{
    char input[maxstrlen];
    int whilmain = 0;
    int control = 0;
    printf("Fluid Heat Transfer Coefficient\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        printf("Please select from the following cases:\n");
        printf("1. Natural convection.\n");
        printf("2. Flat plate (Forced convection).\n");
        printf("3. Inside cylindrical tubes (Forced convection).\n");
        printf("4. Outside cylindrical tubes (Forced convection).\n");
        control = 1;
        while(control == 1)
        {
            printf("Selection [1 - 4]: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                    NaturalConvection();
                    control = 0;
                    break;
                case '2':
                    ForcedFlatPlate();
                    control = 0;
                    break;
                case '3':
                    InsideCylinder();
                    control = 0;
                    break;
                case '4':
                    OutsideCylinder();
                    control = 0;
                    break;
                case '0':
                case 'Q':
                case 'q':
                    goto end;
                    break;
                default:
                    printf("Input not recognised. Please enter an integer between 1 and 4.\n");
                    break;
            }
        }
        //  Continue function
        whilmain = Continue(whilmain);
    }
end:
    fflush(stdout);
}
