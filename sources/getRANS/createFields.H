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

volScalarField Pk
(
    IOobject
    (
        "Pk",
         latestTime,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
volScalarField Pw
(
    IOobject
    (
        "Pw",
         latestTime,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
volScalarField Dk
(
    IOobject
    (
        "Dk",
         latestTime,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
volScalarField Dw
(
    IOobject
    (
        "Dw",
         latestTime,
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
