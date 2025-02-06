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
    getLES

Description
    Output the energy.txt for LES or DNS cases
    for incompressible (0) and compressible case (1)

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "fvOptions.H"

#include "wallDist.H"
#include <vector>
#define COMPRESSIBLE 1

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
double normalization(double up, double down)
{
    return up/max(fabs(up)+fabs(down), VSMALL);
}


tmp<volScalarField> F1
(
    const volScalarField& CDkOmega,
    const volScalarField& nu,
    const volScalarField& y_,
    const volScalarField& omega_,
    const volScalarField& k_
) 
{
    scalar betaStar_ = 0.09;
    scalar alphaOmega2_ = 0.856;
    
    tmp<volScalarField> CDkOmegaPlus = max
    (
        CDkOmega,
        dimensionedScalar(dimless/sqr(dimTime), 1.0e-10)
    );

    tmp<volScalarField> arg1 = min
    (
        min
        (
            max
            (
                (scalar(1)/betaStar_)*sqrt(k_)/(omega_*y_),
                scalar(500)*(nu)/(sqr(y_)*omega_)
            ),
            (4*alphaOmega2_)*k_/(CDkOmegaPlus*sqr(y_))
        ),
        scalar(10)
    );

    return tanh(pow4(arg1));
}


tmp<volScalarField> F2
(
    const volScalarField& nu,
    const volScalarField& y_,
    const volScalarField& omega_,
    const volScalarField& k_
)
{
    scalar betaStar_ = 0.09;
    
    tmp<volScalarField> arg2 = min
    (
        max
        (
            (scalar(2)/betaStar_)*sqrt(k_)/(omega_*y_),
            scalar(500)*(nu)/(sqr(y_)*omega_)
        ),
        scalar(100)
    );

    return tanh(sqr(arg2));
}


tmp<Foam::volScalarField>S2
(
    const volTensorField& gradU
) 
{
    return 2*magSqr(symm(gradU));
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
    forAll(k_, celli)
    {
        k_[celli] = max(0.5*(R[celli].xx()+R[celli].yy()+R[celli].zz()), 1e-10);
    }
    const volScalarField epslion_ = 0.09*pow(k_, 3./2.)/Lc;
    const volScalarField omega_ = epslion_/(0.09*k_);
    
    //production term of k
    const volScalarField Pk = -R && fvc::grad(UMean);
    
    // destruction term of k
    const volScalarField Dk = 0.09*k_*omega_;
    
    const volScalarField& y_ = wallDist::New(mesh).y();
    
    
    scalar alphaOmega2_ = 0.856;
    const volScalarField CDkOmega
    (
        (2*alphaOmega2_)*(fvc::grad(k_) & fvc::grad(omega_))/omega_
    );

    tmp<volTensorField> tgradU = fvc::grad(UMean);
    const volScalarField S2_(S2(tgradU()));  
    volScalarField::Internal GbyNu(dev(twoSymm(tgradU()())) && tgradU()());
    

    const volScalarField F1_ = F1(CDkOmega, nu_, y_, omega_, k_);
    scalar gamma1 = 5./9.;
    scalar gamma2 = 0.44;
    scalar beta1 = 0.075;
    scalar beta2 = 0.0828;
    const volScalarField::Internal gamma(gamma1*F1_+(1-F1_)*gamma2);
    const volScalarField::Internal beta(beta1*F1_+(1-F1_)*beta2);
    
    // production of dissipation term
    const volScalarField::Internal Pw = Pk/(nu*rho);//gamma*GbyNu;
    
    const volScalarField::Internal Dw = beta*omega_*omega_;
    
   
    Info<<"output features for PINN"<<endl;
    #include "outputResults.H"
    
    cells.write();

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
