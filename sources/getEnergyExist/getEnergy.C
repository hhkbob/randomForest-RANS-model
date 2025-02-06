/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2022 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    getRANS

Description
    Output the Pk, Pw, Dk, Dw and neuro features input for RANS cases 
    for incompressible (0) and compressible case (1)

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "singlePhaseTransportModel.H"
#include "turbulentTransportModel.H"
#include "radiationModel.H"
#include "fvOptions.H"
#include "simpleControl.H"
#include "wallDist.H"
#include <vector>
#define COMPRESSIBLE 1

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
double normalization(double up, double down)
{
    return up/max(fabs(up)+fabs(down), VSMALL);
}

int main(int argc, char *argv[])
{
    argList::noParallel();
    // timeSelector::addOptions();
    timeSelector::addOptions(true, true);
    
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"
    
    
    Info<< "Times found:" << runTime.times()[0] << endl;
    
    //word timess = runTime.times()[0];

    instantList timeDirs = timeSelector::select0(runTime, args);
    
    //get the latestTime
    int size = timeDirs.size();
    
    //read velocity uMean
    
    char latestTime[100];
    sprintf(latestTime, "%g", timeDirs[size-1].value());
    
    #include "createFields.H"
   
    Info<<"output features for PINN"<<endl;
    #include "outputResults.H"

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
