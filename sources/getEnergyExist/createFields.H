Info<< "Reading field Pk\n" << endl;


volScalarField Pk
(
    IOobject
    (
        "Pk",
         latestTime,
        mesh,
        IOobject::NO_READ, 
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
        IOobject::NO_READ,
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
        IOobject::NO_READ,
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
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
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

volScalarField k
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

