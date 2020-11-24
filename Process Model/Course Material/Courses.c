//
//  Courses.c
//  Process Model
//
//  Created by Matthew Cheung on 24/11/2020.
//

#include <stdio.h>

#include "main.h"
#include "Courses.h"

#define maxstrlen 128

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
