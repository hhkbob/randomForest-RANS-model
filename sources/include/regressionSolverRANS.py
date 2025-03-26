## Import system modules
# sci computing
import numpy as np
# sklearn importing
from sklearn.ensemble._forest import RandomForestRegressor
import threading

#save model
import pickle

import argparse

import time

# [1]  load the input features

def loadTrainData():
    data = np.loadtxt('inputFeatures.txt')
    return data


# [2]  load the model and predict
def loadModel(n):
    print('Load model---PINN_RANS_Model.pkl version-', n)
    #model_path = '/mnt/d/machineLearningVersion/v1_SUSTECH_26_08_2024/PINN_RANS_Model.pkl'
    #if n==1:
    #    model_path = '/home/hhk/OpenFOAM/PINN_RANS_Modelold.pkl'
    #    print('Select method in: /home/hhk/OpenFOAM/PINN_RANS_Modelold.pkl')
    #elif n==2:
    model_path = '/mnt/d/machineLearningVersion/randomForestV2/PINN_RANS_Model.pkl'
    print('Select method in: /mnt/d/machineLearningVersion/randomForestV2/PINN_RANS_Model.pkl')
    #else:
    #    raise Exception('Invalid version of method. Application abort')
    with open(model_path, "rb") as f:
        regModel = pickle.load(f)
    return regModel
    
def predict(inputFeatures, regModel):
    print('Predict data')
    ResponsesPred = regModel.predict(inputFeatures)
    return ResponsesPred

def output(ResponsesPred):
    print('Output outputResult.txt')
    with open('outputResult.txt', 'w') as f:
        for prediction in ResponsesPred:
                 f.write(" ".join(map(str, prediction.tolist())) + "\n")
    f.close()
    print('Machine learning is done')   

# [3] run the regression solver

#print('done')
def main():
    inputFeatures = loadTrainData()
    version = 2 
    regModel = loadModel(int(version))
    ResponsesPred = predict(inputFeatures, regModel)
    output(ResponsesPred)

if __name__ == '__main__':
    main()
