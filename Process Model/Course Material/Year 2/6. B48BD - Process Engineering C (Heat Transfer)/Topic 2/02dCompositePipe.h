//
//  02dCompositePipe.h
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

#ifndef _2dCompositePipeVariable_h
#define _2dCompositePipeVariable_h

typedef struct PipeMedium{
    double k[21];
    double h[21];
    double r[21];
    double R[21];
} PipeMedium;

#endif /* _2dCompositePipeVariable_h */

#ifndef _2dCompositePipeCalculation_h
#define _2dCompositePipeCalculation_h

typedef struct TempProfile{
    double k[5000];
    double h[5000];
    double r[5000];
    double T[5000];
} TempProfile;

#endif /* _2dCompositePipeCalculation_h */

#ifndef _2dCompositePipeDisplay_h
#define _2dCompositePipeDisplay_h



#endif /* _2dCompositePipeDisplay_h */

#ifndef _2dCompositePipeWrite_h
#define _2dCompositePipeWrite_h



#endif /* _2dCompositePipeWrite_h */
