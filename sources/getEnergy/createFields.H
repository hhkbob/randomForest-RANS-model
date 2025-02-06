Info<< "Reading field Pk\n" << endl;


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

    IOdictionary transportProperties
    (
       IOobject
       (
           "transportProperties",
           runTime.constant(),
           mesh,
           IOobject::MUST_READ_IF_MODIFIED,
           IOobject::NO_WRITE
       )
    );

    dimensionedScalar Xmin
    (
       "Xmin",
       dimless,
       transportProperties.lookupOrDefault("Xmin", -10e8)
    );
    dimensionedScalar Xmax
    (
       "Xmax",
       dimless,
       transportProperties.lookupOrDefault("Xmax", 10e8)
    );
    dimensionedScalar Ymax
    (
       "Ymax",
       dimless,
       transportProperties.lookupOrDefault("Ymax", 10e8)
    );
    dimensionedScalar Ymin
    (
       "Ymin",
       dimless,
       transportProperties.lookupOrDefault("Ymin", -10e8)
    );
    dimensionedScalar Zmin
    (
       "Zmin",
       dimless,
       transportProperties.lookupOrDefault("Zmin", -10e8)
    );
    dimensionedScalar Zmax
    (
       "Zmax",
       dimless,
       transportProperties.lookupOrDefault("Zmax", 10e8)
    );








