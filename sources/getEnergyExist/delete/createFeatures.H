    //=================================================================
    //  Part 1: define the input parameters
    //=================================================================

    volScalarField q1
    (
          IOobject
          (
                "q1",
                latestTime,
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE,
                true
          ),
          mesh,
          dimensionedScalar("q1", dimless, 0.0)
    );

    volTensorField E
    (
          IOobject
          (
                "E",
                 latestTime,
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE,
                true
          ),
          mesh,
          dimensionedTensor("E", dimless, tensor(1.0,0,0, 0,1.0,0, 0,0,1.0))
    );
    
    volTensorField b
    (
          IOobject
          (
                "b",
                 latestTime,
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE,
                true
          ),
          mesh,
          dimensionedTensor("b", dimless, tensor(0,0,0, 0,0,0, 0,0,0))
    );

    int inputFeaturesSize = 10;
    std::vector<volScalarField> inputFeatures;//(inputFeaturesSize);
    for(int i=0; i<inputFeaturesSize; i++)
    {
        inputFeatures.push_back(q1);
    }

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
       dimLength,
       transportProperties.lookup("Lc")
    );

    dimensionedScalar Uc
    (
       "Uc",
       dimVelocity,
       transportProperties.lookup("Uc")
    );

    volScalarField nu
    (
          IOobject
          (
                "nu",
                 latestTime,
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE,
                true
          ),
          mesh,
          dimensionedScalar("nu", dimensionSet(0, 2, -1, 0, 0, 0, 0), 0)
    );

    volScalarField rho
    (
          IOobject
          (
                "rho",
                 latestTime,
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE,
                true
          ),
          mesh,
          dimensionedScalar("rho", dimensionSet(1, -3, 0, 0, 0, 0, 0), 0)
    ); 

    volScalarField p_in
    (
          IOobject
          (
                "p_in",
                 latestTime,
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE,
                true
          ),
          mesh,
          dimensionedScalar("p_in", dimensionSet(0, 2, -2, 0, 0, 0, 0), 0)
    ); 

    dimensionedScalar com
    (
       "com",
       dimless,
       transportProperties.lookup("com")
    ); 

   if(int(com.value())==COMPRESSIBLE)
   {
        volScalarField rho_
        (
              IOobject
              (
                    "rho",
                     latestTime,
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::NO_WRITE,
                    true
              ),
              mesh
            ); 
          volScalarField mu
          (
              IOobject
              (
                    "mu",
                     latestTime,
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::NO_WRITE,
                    true
              ),
              mesh
            ); 
           rho = rho_; 
           nu =  mu/rho;  
           p_in = p/rho;  
   }
   else
   {
          dimensionedScalar nus
          (
                "nu",
                dimensionSet(0, 2,-1, 0, 0, 0, 0),
                transportProperties.lookup("nu")
          );
          dimensionedScalar rhos
          (
                "rho",
                dimensionSet(1, -3,0, 0, 0, 0, 0),
                transportProperties.lookup("rho")
          );
          p_in = p;
          nu = nus;
          rho = rhos;
   }
    
    // define the writeTime interval
    /*dimensionedScalar deltaT
    (
       "deltaT",
       dimless,
       transportProperties.lookup("deltaT")
    );*/

    volScalarField magTensor
    (
          IOobject
          (
                "magTensor",
                latestTime,
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE,
                true
          ),
          mesh,
          dimensionedScalar("magTensor", dimless, 0.0)
    );








