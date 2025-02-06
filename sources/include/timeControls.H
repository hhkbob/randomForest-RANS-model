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

    volScalarField pkf0 = Pkf;
    volScalarField dkf0 = Dkf;
    volScalarField pwf0 = Pwf;
    volScalarField Dwf0 = Dwf;

     timeControl tControl(runTime);