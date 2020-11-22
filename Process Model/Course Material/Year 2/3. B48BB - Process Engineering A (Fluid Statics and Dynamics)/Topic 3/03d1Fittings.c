//
//  03d1Fittings.c
//  Process Model
//
//  Created by Matthew Cheung on 02/07/2020.
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

//  Custom header files
#include "System.h"
#include "B48BB_T3.h"
#include "03dOneK.h"
#include "03dTwoK.h"
#include "03dThreeK.h"
#include "03dEquivLeng.h"

#define maxstrlen 128

void Fittings()
{
    //  Pseudo-main function.
    int whilmain = 1;
    printf("Pressure Loss through Pipe Fittings\n");
    
    while(whilmain == 1)
    {
        //Variable declaration
        char input[maxstrlen];
        
        int whilside = 1;
        while(whilside == 1)
        {
            //Data collection
            printf("Which method do you want to use to calculate friction losses:\n");
            printf("1. 1K (Lost velocity heads)(Excess heads method) (Recommended for small pipe sizes)\n");
            printf("2. 2K (Lost velocity heads)\n");
            printf("3. 3K (Lost velocity heads) (Recommended for NPS > NPS 12)\n");
            printf("4. Equivalent length\n");
            printf("Selection: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                    OneK();
                    whilside = 0;
                    break;
                case '2':
                    TwoK();
                    whilside = 0;
                    break;
                case '3':
                    ThreeK();
                    whilside = 0;
                    break;
                case '4':
                    EquivalentLength();
                    whilside = 0;
                    break;
                default:
                    printf("Input not recognised\n");
                    break;
            }
        }
        //Continue function
        whilmain = Continue(whilmain);
        printf("\n");
    }
    fflush(stdout);
}
