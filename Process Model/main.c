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
        printf("4. Reading\n");
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
                Reading();
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
