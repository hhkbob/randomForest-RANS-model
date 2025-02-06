Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
         latestTime,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field p_rgh\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
         latestTime,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volScalarField k_
(
    IOobject
    (
        "k",
         latestTime,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volSymmTensorField R
(
    IOobject
    (
        "R",
         latestTime,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volScalarField mut
(
    IOobject
    (
        "mut",
         latestTime,
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("mut", dimless, 0)
);

volScalarField nut
(
    IOobject
    (
        "nut",
         latestTime,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volScalarField omega
(
    IOobject
    (
        "omega",
         latestTime,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

surfaceScalarField phi
(
    IOobject
    (
        "phi",
         latestTime,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


volScalarField Pkf
(
    IOobject
    (
        "Pkf",
         latestTime,
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("Pkf", dimless, 0)
);
volScalarField Pwf
(
    IOobject
    (
        "Pwf",
         latestTime,
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("Pwf", dimless, 0)
);
volScalarField Dkf
(
    IOobject
    (
        "Dkf",
         latestTime,
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("Dkf", dimless, 0)
);
volScalarField Dwf
(
    IOobject
    (
        "Dwf",
         latestTime,
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("Dwf", dimless, 0)
);
