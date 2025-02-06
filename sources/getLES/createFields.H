Info<< "Reading field U\n" << endl;

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

volVectorField UMean
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

volScalarField k_
(
    IOobject
    (
        "k_",
         latestTime,
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("k_", dimensionSet(0, 2, -2, 0, 0, 0, 0), 1e-8)
);

volScalarField cells
(
    IOobject
    (
        "cells",
        runTime.constant(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("cells", dimless, 0)
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

    dimensionedScalar Lc
    (
       "Lc",
       dimensionSet(0, 1, 0, 0, 0, 0, 0),
       transportProperties.lookupOrDefault("Lc", 1e-5)
    );

    dimensionedScalar nu
    (
       "nu",
       dimensionSet(0, 2, -1, 0, 0, 0, 0),
       transportProperties.lookupOrDefault("nu", 1e-5)
    );

    dimensionedScalar rho
    (
       "rho",
       dimensionSet(1, -3, 0, 0, 0, 0, 0),
       transportProperties.lookupOrDefault("rho", 1.1716)
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

volScalarField nu_
(
    IOobject
    (
        "nu_",
         latestTime,
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("nu_", dimensionSet(0, 2, -1, 0, 0, 0, 0), nu.value())
);






