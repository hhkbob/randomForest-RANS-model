FOAM='/home/hhk/OpenFOAM/OpenFOAM-v2312/src/TurbulenceModels/turbulenceModels/lnInclude/'
Tur='/home/hhk/OpenFOAM/OpenFOAM-v2312/src/TurbulenceModels/'
FOAM_HOME='/home/hhk/Documents/PINNv/PINNkOmegaSST/'

cd $FOAM &&
ln -s $FOAM_HOME/PINNkOmegaSST.C &&
ln -s $FOAM_HOME/PINNkOmegaSST.H &&
ln -s $FOAM_HOME/PINNkOmegaSSTBase.C &&
ln -s $FOAM_HOME/PINNkOmegaSSTBase.H &&

sed -i '$a  #include \"PINNkOmegaSST.H\"' $Tur/incompressible/turbulentTransportModels/turbulentTransportModels.C &&
sed -i '$a  makeRASModel(PINNkOmegaSST);'  $Tur/incompressible/turbulentTransportModels/turbulentTransportModels.C &&

sed -i '$a  #include \"PINNkOmegaSST.H\"' $Tur/compressible/turbulentFluidThermoModels/turbulentFluidThermoModels.C &&
sed -i '$a  makeRASModel(PINNkOmegaSST);'  $Tur/compressible/turbulentFluidThermoModels/turbulentFluidThermoModels.C &&


cd $Tur &&
./Allwmake
