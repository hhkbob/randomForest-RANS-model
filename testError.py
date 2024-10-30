################################################################################
# These codes are presented here to regenerate the error showed in the paper
#
# Huakun Huang, Qingmo Xie, Tai'an Hu, Huan Hu, Peng Yu, A random forest machine 
# learning in turbulence closure modeling for complex flows and heat transfer
# based on the non-equilibrium turbulence assumption.
#
# Just an example

## Import system modules
# sci computing
import numpy as np
# sklearn importing
from sklearn.ensemble._forest import RandomForestRegressor
from sklearn.metrics import accuracy_score
#save model
import pickle

import time, random, os

import math as mt


# func 1
################################################################################
#@param1: output  -  predict value
#@param2: targets - label value
#@return: relative value
#aim: compute the relative error
################################################################################
def error(outputs, targets):
    errors=[]
    for n in range(outputs.shape[0]):
        for m in range(outputs.shape[1]):
            er = ((outputs[n][m]-targets[n][m]))/max(((targets[n][m])**2)**0.5, 1e-10)
            errors.append(er)
    return errors


# func 2
################################################################################
#@param1: error - relative value
#@aim: write file for RMS error
################################################################################
def writeError(error):
    with open('errors.txt', 'w') as f:
        for n in range(len(error)):
            f.write(repr(error[n])+'\n')
    f.close()

# func 3
################################################################################
#@aim: Load the regression model
################################################################################
def loadModel():
    model_path = './PINN_RANS_Model.pkl'
    with open(model_path, "rb") as f:
        regModel = pickle.load(f)
    return regModel 


################################################################################
# main
################################################################################
testFeatures = np.loadtxt('dataRANS/test.txt')
testResponse = np.loadtxt('dataRANS/testRes.txt')

regModel = loadModel()

pred = regModel.predict(testFeatures)

errors = error(pred, testResponse)
writeError(errors)