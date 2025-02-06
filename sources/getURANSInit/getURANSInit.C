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
    getURANSIniit

Description
    Do prediction and get the Pkf, Dkf, Pwf, Dwf based on randomForest

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

#include "PINN.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


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
    
    Info<<"create features for PINN using randomForest"<<endl;
    #include "createFeaturesURANS.H"

    Info<<"get features for PINN"<<endl;
    #include "getInputFeatures.H"
    
    mut = nut/(Uc*Lc);
    
    Info<<"output features for PINN"<<endl;
    #include "outputFeatures.H"
    
    system("python /home/hhk/OpenFOAM/PINNv/include/regressionSolverRANS.py");
    
    //read the data file
    FILE *dats = fopen("outputResult.txt", "r");
    double buffer=0;
    double critical = 2.;
    bool noTrue = false;
    if(dats!=NULL)
    {
        forAll(Pkf, celli)
        {
            fscanf(dats, "%lf", &buffer);
            Pkf[celli] = buffer;
            if(buffer>critical)
            {
                noTrue = true;  
            }
            fscanf(dats, "%lf", &buffer);
            Dkf[celli] = buffer;
            if(buffer>critical)
            {
                noTrue = true;  
            }
            fscanf(dats, "%lf", &buffer);
            Pwf[celli] = buffer;
            if(buffer>critical)
            {
                noTrue = true;  
            }
            fscanf(dats, "%lf", &buffer);
            Dwf[celli] = buffer;
            if(buffer>critical){
                noTrue = true;  
            }
            if(noTrue)
            {
                 Pkf[celli] = critical;
                 Dkf[celli] = critical;
                 Pwf[celli] = critical;
                 Dwf[celli] = critical;
            }
            noTrue = false;
        }
        fclose(dats);
        Pkf.write();
        Dkf.write();
        Pwf.write();
        Dwf.write();
    }

    system("mv constant/Pkf 0/Pkf");
    system("mv constant/Dkf 0/Dkf");
    system("mv constant/Pwf 0/Pwf");
    system("mv constant/Dwf 0/Dwf");
    Info<<"Check all output value"<<endl;
    system("python /home/hhk/OpenFOAM/PINNv/include/checkData.py");
    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
