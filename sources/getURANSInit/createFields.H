Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "UMean",
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
        "pMean",
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
        "kMean",
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
        "UPrime2Mean",
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
        "mutMean",
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
        "nutMean",
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
        "omegaMean",
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
        "phiMean",
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
