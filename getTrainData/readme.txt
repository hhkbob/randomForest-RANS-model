##[1] define parameters in constant/transportProperties
Uc: reference velocity m/s
Lc: reference length m
com: compressible case-1, incompressible case-0
rho: reference density kg/m3
TRef: reference temperature


######################################
####### Get training data ############
######################################
##[1] To get Pk_rans, Dk_rans, Pw_rans, Dw_rans (energy.txt), in RANS folder, run
steady cases: getRANS
unsteady cases: getURANSEnergy

##[2] To get Pk_fidelity, Dk_fidelity, Pw_fidelity, Dw_fidelity (energy.txt), in Fidelity folder, run
steady cases: getEnergy/getLES (if LES or DNS)
unsteady cases: getURANSEnergy, getFeaturesURANS

##[3] To get Pk_f, Dk_f, Pw_f, Dw_f, run
dataRANS

*** Note: you can select a specific region by setting Xmin, Ymin, Zmin, Xmax, Ymax, Zmax
    in constant/transportProperties