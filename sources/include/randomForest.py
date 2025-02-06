## Import system modules
# sci computing
# in C++ codes, adding numpy.py, sklearn.py is needed

#import numpy as np
# sklearn importing
#from sklearn.ensemble._forest import RandomForestRegressor

#save model
#import pickle



def loadModel(n):
    return 5;

def predict(input):
    return 0, 1, 2, 4

"""
# [1]  load the model and predict
def loadModel(n):
    model_path = '/home/hhk/OpenFOAM/PINN_RANS_Model.pkl'
    with open(model_path, "rb") as f:
        regModel = pickle.load(f)
    return regModel
    
# [2] run the regression solver, do predict    
def predict(inputFeatures, regModel):
    ResponsesPred = regModel.predict(inputFeatures)
    return ResponsesPred
"""
