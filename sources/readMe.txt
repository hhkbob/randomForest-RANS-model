## env
python 3.11.7
scikit-learn version 1.2.2
OpenFoam-v2312
windows-10 WSL


## check python version 3.11.7
## check scikit-learn version
## conda install scikit-learn=1.2.2

##[1]
(1) Make sure the following path is correct in line 84 in the getInit/getInit.C
    system("python /home/hhk/Documents/PINNv/include/regressionSolverRANS.py");
(2) Make sure the following path is correct in line 139 in the getInit/getInit.C
    system("python /home/hhk/Documents/PINNv/include/checkData.py");
(3) Make sure the following path is correct in line 30-31 in the include/regressionSolverRANS.py
    model_path = '/mnt/hgfs/D/machineLearning/randomForest/PINN_RANS_Model.pkl'

##[2]
(1) Run Allwclean
(2) Run Allwmake
(3) Go to PINNkOmegaSST folder, and open run.sh. Make sure the path is correct.
    and then, run run.sh
    if there is no error, you will get the PINNkOmegaSST turbulence model.
(5) Go to kOmegaSST folder, and use these codes to replace the files in 
    your_openFoam/src/TurbulenceModels/turbulenceModels/Base/kOmegaSST
   And then, go to the path: your_openFoam/src/TurbulenceModels/turbulenceModels/
   Now, you can compile the kOmegaSST model by running Allwmake
(6) Go to testCases or getTrainData folder. Try to run a tutorial, or prepare your data.





