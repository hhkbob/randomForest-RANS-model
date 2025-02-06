    Info<<"Read nut for ML"<<endl;
    forAll(k_, celli)
    {
        k_[celli] = 1.0/2.0*(R[celli].xx()+R[celli].yy()+R[celli].zz());  
        if(k_[celli]<0)
            Info<<"error\n";
    }
    const volScalarField epsilon_ = omega*0.09*k_;

    tmp<volTensorField> tgradU = fvc::grad(U);
    volVectorField tgradP = fvc::grad(p_in);
    
    volTensorField S=0.5*(tgradU()+T(tgradU()));
    volTensorField O=0.5*(tgradU()-T(tgradU()));
    
    const volScalarField STRAIN((tr(S&T(S))));
    const volScalarField OMEGA((tr(O&T(O))));     

    const volScalarField& y_(wallDist::New(mesh).y());
    Info<<"Compute different parameters"<<endl;
    //const volScalarField& nu_ = nu.value();
    volVectorField U2 = U;
    forAll(U, celli)
    {
        U2[celli][0] = U[celli][0]*U[celli][0];
        U2[celli][1] = U[celli][1]*U[celli][1];
        U2[celli][2] = U[celli][2]*U[celli][2];
    }
    const volTensorField gradU2 = fvc::grad(U2);
    Info<<"compute qb7"<<endl;
    const volScalarField qb7 = mag(U*fvc::div(phi,U));
    Info<<"compute qb7_"<<endl;
    const volScalarField qb7_ = sqrt(mag(U*U & U&fvc::grad(U) &&U&fvc::grad(U)));
    Info<<"Compute q8"<<endl;
    volScalarField q8 = q1;
    const volVectorField gradk = fvc::grad(k_);
    forAll(q1, celli)
    {
       q8[celli] = 0;
       for(int j=0; j<3; j++)
          q8[celli] += U[celli][j]* gradk[celli][j];
    }
    
    Info<<"calculate the parameter 9 to 10"<<endl;
    dimensionedScalar vsmall
    (
        "vsmall",
        dimensionSet(0, 2, -2, 0, 0, 0, 0),
        VSMALL
    );
    const volTensorField tu = fvc::grad(U/ max(magSqr(U), vsmall));
    volScalarField qb10 = q1;
    forAll(qb10, celli)
    {
        qb10[celli] = U[celli][0]*tu[celli].xx()
                    + U[celli][1]*tu[celli].yy()
                    + U[celli][2]*tu[celli].zz();
        
    } 
    Info<<"calculate the parameter qb8"<<endl;
    const volScalarField qb8 = mag(R&S);
    const volScalarField mag2U = magSqr(U);
    const volScalarField magR = mag(R);
    
    Info<<"calculate the non-linear part of Reynolds stress"<<endl;
    //volSymmTensorField b = R/(2.*k_) - 1.0/3.0*E;
    forAll(U, celli)
    {
        b[celli].xx() = R[celli].xx()/(2.0*k_[celli]) - 1.0/3.0;
        b[celli].xy() = R[celli].xy()/(2.0*k_[celli]);
        b[celli].xz() = R[celli].xz()/(2.0*k_[celli]);

        b[celli].yx() = b[celli].xy();
        b[celli].yy() = R[celli].yy()/(2.0*k_[celli]) - 1.0/3.0;
        b[celli].yz() = R[celli].yz()/(2.0*k_[celli]);

        b[celli].zx() = b[celli].xz();
        b[celli].zy() = b[celli].yz();
        b[celli].zz() = R[celli].zz()/(2.0*k_[celli]) - 1.0/3.0;
    }

    Info<<"compute features for vortex streching parameter"<<endl;
    volScalarField::Internal XOmega
    (
        sqrt(
                magSqr
                (
                    (skew(tgradU()()) & skew(tgradU()()))
                    && symm(tgradU()())
                     / (pow(0.09*omega(),3.0))
                )
             )
     );
    if(int(com.value())==COMPRESSIBLE)
    {
        volTensorField Sij =S;
        forAll(Sij, celli)
        {                       
            Sij[celli].xx() = Sij[celli].xx()
                            -1.0/2.*tgradU.ref()[celli].xx();

            Sij[celli].yy() = Sij[celli].yy()
                            -1.0/2.*tgradU.ref()[celli].yy();
                            
            Sij[celli].zz() = Sij[celli].zz()
                            -1.0/2.*tgradU.ref()[celli].zz();
        }
        XOmega = mag
        (
            (
                (O & O) && Sij
                / (pow(0.09*omega(),3.0))
            )
        );
    }
    volScalarField::Internal fbeta
    (
        (1.0+90*XOmega*1.0)/(1.0+100*XOmega)
    );
    inputFeatures[10].ref() = fbeta;
    
    // add the FS1 feature to the inputfeature
    //-First inilization feature
    //- ref: Data-driven RANS closures for wind turbine wakes under neutral conditions
    /*volTensorField S_ = S/(mag(S)+omega*0.09);
    volTensorField O_ = O/(mag(O)+omega*0.09);

    Info<<"calculate Ap"<<endl;
    volTensorField Aps =MycrossProduct(-II, tgradP);
    volScalarField magUs = mag(U & tgradU);
    volTensorField Ap_ = S_*0;
    Ap_ = normTensorField(Ap_, Aps, omega*0.09*sqrt(k_));
    
    //volTensorField Ap_ = S_*0;
    Info<<"calculate Aks"<<endl;
    volTensorField Ak_ = S_*0;
    
    Info<<"calculate Ak"<<endl;
    volTensorField Aks =MycrossProduct(-II, gradk); 
    Ak_ = normTensorField(Ak_, Aks, magUs);
    

     inputFeatures[11] = S_&&S_;
     inputFeatures[12] = (S_&S_)&&S_;
     inputFeatures[13] = O_ && O_;
     inputFeatures[14] = Ap_&& Ap_;
     inputFeatures[15] = Ak_ && Ak_;
     inputFeatures[16] = (O_&O_)&&S_;
     inputFeatures[17] = O_&O_ & S_&&S_;
     inputFeatures[18] = O_&O_ & S_&O_ & S_&&S_;
     inputFeatures[19] = Ap_&Ap_ && S_;
     inputFeatures[20] = Ap_ & Ap_ & S_&&S_;
     inputFeatures[21] = Ap_ & Ap_ &S_&Ap_&S_&&S_;
     inputFeatures[22] = Ak_&Ak_ &&S_;
     inputFeatures[23] = Ak_&Ak_ & S_&&S_;
     inputFeatures[24] = Ak_&Ak_ &S_&Ak_&S_&&S_;
     inputFeatures[25] = O_&&Ap_;
     inputFeatures[26] = Ap_&&Ak_;
     inputFeatures[27] = O_&&Ak_;
     inputFeatures[28] = O_&Ap_&&S_;
     inputFeatures[29] = O_&Ap_&S_&&S_;
     inputFeatures[30] = O_&Ak_&&S_;
     inputFeatures[31] = O_&Ak_&S_&&S_;
     inputFeatures[32] = O_&Ap_&&S_;
     inputFeatures[33] = Ap_&Ak_&S_&&S_;
     inputFeatures[34] = O_&O_&Ap_&&S_;
     inputFeatures[35] = Ap_&Ap_&O_&&S_;
     inputFeatures[36] = O_&O_&Ap_&S_&&S_;
     inputFeatures[37] = Ap_&Ap_&O_&S_&&S_;
     inputFeatures[38] = O_&O_&S_&Ap_&S_&&S_;
     inputFeatures[39] = Ap_&Ap_&S_&O_&S_&&S_;
     inputFeatures[40] = O_&O_&Ak_&&S_;
     inputFeatures[41] = Ak_&Ak_&O_&&S_;
     inputFeatures[42] = O_&O_&Ak_&S_&&S_;
     inputFeatures[43] = Ak_&Ak_&O_&S_&&S_;
     inputFeatures[44] = O_&O_&S_&Ak_&S_&&S_;
     inputFeatures[45] =  Ak_&Ak_&S_&O_&S_&&S_;
     inputFeatures[46] =  Ap_&Ap_&Ak_&&S_;
     inputFeatures[47] =  Ak_&Ak_&Ap_&&S_;
     inputFeatures[48] =  Ap_&Ap_&S_&Ak_&S_&&S_;
     inputFeatures[49] =  Ak_&Ak_&S_&Ap_&S_&&S_;
     inputFeatures[50] =  O_&Ap_&&Ak_;
     inputFeatures[51]=  O_&Ap_&Ak_&&S_;
     inputFeatures[52] =  O_&Ak_&Ap_&&S_;
     inputFeatures[53] =  O_&Ap_&Ak_&S_&&S_;
     inputFeatures[54] =  O_&Ak_&Ap_&S_&&S_;
     inputFeatures[55] =  O_&Ap_&S_&Ak_&S_&&S_;*/



    //Info<<"get its and ksi"<<endl;
    //volScalarField ksi = q1*0;
    //volScalarField ita = q1*0;    

    //FILE *dat_ = fopen("eigenVector_ras.txt", "w");
    
    forAll(p, celli)
    {
        inputFeatures[0][celli] = normalization(0.5*(OMEGA[celli] - STRAIN[celli]), STRAIN[celli]);
        inputFeatures[1][celli] = normalization(k_[celli], 0.5*mag2U[celli]);
        inputFeatures[2][celli] = min(std::sqrt(k_[celli])*y_[celli]/(50*nu[celli]), 2.0);
        
        double qb4 = 0;
        
        qb4 = sqr(tgradP[celli].x())*sqr(U[celli].x())
                          + sqr(tgradP[celli].x())*sqr(U[celli].y())
                          + sqr(tgradP[celli].x())*sqr(U[celli].z());

        qb4 += sqr(tgradP[celli].y())*sqr(U[celli].x())
                          + sqr(tgradP[celli].y())*sqr(U[celli].y())
                          + sqr(tgradP[celli].y())*sqr(U[celli].z());

        qb4 += sqr(tgradP[celli].z())*sqr(U[celli].x())
                          + sqr(tgradP[celli].z())*sqr(U[celli].y())
                          + sqr(tgradP[celli].z())*sqr(U[celli].z());
        double q4 = U[celli].x()*tgradP[celli].x()
                  + U[celli].y()*tgradP[celli].y()
                  + U[celli].z()*tgradP[celli].z();
                          
        inputFeatures[3][celli] = normalization(q4, std::sqrt(qb4));
        double part1 = k_[celli]/max(epsilon_[celli], VSMALL);
        double part2 = 1.0/max(std::sqrt(STRAIN[celli]), VSMALL);
        inputFeatures[4][celli] = part1/(fabs(part1)+fabs(part2));
        //char buffer[20];
        double q6 = 0.5*rho[celli]*(gradU2[celli].xx()+gradU2[celli].yy()+gradU2[celli].zz());
        double maggradp = 0;
        maggradp += tgradP[celli][0]*tgradP[celli][0];
        maggradp += tgradP[celli][1]*tgradP[celli][1];
        maggradp += tgradP[celli][2]*tgradP[celli][2];
        maggradp = std::sqrt(maggradp);
        inputFeatures[5][celli] = normalization(maggradp, q6);

        inputFeatures[6][celli] = normalization(qb7[celli], qb7_[celli]);

        inputFeatures[7][celli] = normalization(q8[celli], qb8[celli]);
        inputFeatures[8][celli] = normalization(magR[celli], k_[celli]);
        inputFeatures[9][celli] = normalization(qb10[celli], 1.0/Lc.value());
        
        
        /*eigen eig;
        eig.getEigenvalue(b[celli]);
        ksi[celli] = eig.ksi;
        ita[celli] = eig.ita;  
        norm1[celli] = eig.norm1;
        norm2[celli] = eig.norm2;
        norm3[celli] = eig.norm3;
        magTensor[celli] = eig.magTensor;
        tensor eigenVector = eig.eigenVector_;
        for(int i=0; i<9; i++)
        {
            fprintf(dat_, "%g\t", eigenVector.xx());
            fprintf(dat_, "%g\t", eigenVector.xy());
            fprintf(dat_, "%g\t", eigenVector.xz());
            fprintf(dat_, "%g\t", eigenVector.yx());
            fprintf(dat_, "%g\t", eigenVector.yy());
            fprintf(dat_, "%g\t", eigenVector.yz());
            fprintf(dat_, "%g\t", eigenVector.zx());
            fprintf(dat_, "%g\t", eigenVector.zy());
            fprintf(dat_, "%g\n", eigenVector.zz());
        }*/
    } 
    //fclose(dat_);  
    tgradU.clear();
    tgradP.clear();
    
    
        
        