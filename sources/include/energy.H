//PINN
volScalarField Pkf
(
    IOobject
    (
        "Pkf",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("Pkf", dimless, 1)
);
volScalarField Pwf
(
    IOobject
    (
        "Pwf",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("Pwf", dimless, 1)
);
volScalarField Dkf
(
    IOobject
    (
        "Dkf",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("Dkf", dimless, 1)
);
volScalarField Dwf
(
    IOobject
    (
        "Dwf",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("Dwf", dimless, 1)
);

volScalarField mut
(
    IOobject
    (
        "mut",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("mut", dimless, 0)
);
