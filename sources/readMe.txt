## env
python 3.11.7
scikit-learn version 1.2.2
OpenFoam-v2312
windows-10 WSL


## check python version 3.11.7
## check scikit-learn version
## conda install scikit-learn=1.2.2

##[1]
(1) Make sure the following path is correct in line 85 in the getInit/getInit.C
    system("python /home/hhk/Documents/PINNv/include/regressionSolverRANS.py");
(2) Make sure the following path is correct in line 140 in the getInit/getInit.C
    system("python /home/hhk/Documents/PINNv/include/checkData.py");
(3) Make sure the following path is correct in line 24 in the include/regressionSolverRANS.py
    model_path = '/mnt/hgfs/D/machineLearning/randomForest/PINN_RANS_Model.pkl'

##[2] define parameters in constant/transportProperties
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




