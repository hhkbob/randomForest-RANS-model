################################################################################
# These codes are presented here to regenerate the ML method showed in the paper
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
# plotting
import matplotlib.pyplot as plt  # for plotting
#import matplotlib as mp

from sklearn.metrics import accuracy_score

#save model
import pickle

import time, random, os

import math as mt

# func 1
################################################################################
#@param1: output  -  predict value
#@param2: targets - label value
#@return: RMS value
#aim: compute the RMS error
################################################################################
def error(outputs, targets):
    errors=[]
    for n in range(outputs.shape[0]):
        for m in range(outputs.shape[1]):
            value = ((outputs[n][m]-targets[n][m])*(outputs[n][m]-targets[n][m]))**0.5
            er =  value/max(((targets[n][m])**2)**0.5, 1e-5)     
            errors.append(er)
    return errors

# func 2
################################################################################
#@param1: error - RMS value
#@aim: write file for RMS error
################################################################################
def writeError(error):
    with open('error.txt', 'w') as f:
        for n in range(len(error)):
            f.write(repr(error[n])+'\n')
    f.close() 

# func 3
################################################################################
#@param1: error - RMS value
#@aim: write file for RMS error
################################################################################
def accuracy(y_true, y_pre):
    score = 0
    for n in range(y_true.shape[0]):
        for m in range(y_true.shape[1]):
            score = score + (y_true[n][m]-y_pre[n][m])*(y_true[n][m]-y_pre[n][m])
    score = mt.sqrt(score/(y_true.shape[0]*y_true.shape[1]))
    errors = error(y_pre, y_true)
    writeError(errors)
    return score


# func 4
################################################################################
#@param1: fileName - file name 
#@param2: input - an array for saving
#@param3: raws - the selected rows in input array
#@aim: Save the selected rows from input array
################################################################################
def writeFile(fileName, input, rows):
    k=0
    with open(fileName, 'w') as f:
        for n in range(len(rows)):
            for m in range(input.shape[1]):
                f.write(repr(input[rows[n]][m])+'\t');
            f.write('\n');
    f.close()


# func 5
################################################################################
#@param1: a - array a 
#@param2: b - array b
#@aim: Append a and b into a new array
################################################################################
def arrayAppend(a, b):
    rows = a.shape[0]+b.shape[0]
    colus = a.shape[1]
    temp = np.zeros((rows, colus))
    for n in range(temp.shape[0]):
        for m in range(temp.shape[1]):
            if(n<a.shape[0]):
                temp[n][m] = a[n][m]
            else:
                temp[n][m] = b[n-a.shape[0]][m]
    return temp


# func 6
################################################################################
#@aim: load inputFeature and outputFeatures
################################################################################      
def dataInput():
    trainFolder = [ 
      'Impingement_round_23000_H2',             #transition, flow separation, heat transfer, incompressible
      'Impingement_round_23000_H7',             #no transition, heat transfer, incompressible
      'Impingement_round_23000_H10',            #no transition, heat transfer, incompressible
      'Impingement_round_23000_H14',            #no transition, heat transfer, incompressible
      'Impingement_round_30000_H1',             #transition or flow separation, compressible
      'Impingement_plane_10000_H2',
      'Impingement_plane_20000_H4',
      'Impingement_plane_11000_H6',
      'Impingement_plane_20000_H9.2',
      'Swirling_pipe_flow_Re_10000',            #strong swirling flow, incompressible  
      'pit',  
      'T3A',                                    #transition, incompressible
      'T3B-',                                   #transition, incompressible
      'T3A2-',                                  #transition, incompressible
      'T3A-'                                    #transition, incompressible
      ]

    for n in range(len(trainFolder)):
        folder = trainFolder[n]
        os.system('cd '+folder+' && dataRANS')
        input = np.loadtxt(folder+'/dataRANS/inputFeatures.txt')
        data = np.loadtxt(folder+'/dataRANS/ratio.txt')
    
        if n==0:
            input_ = input
            data_ = data
        else:    
            input_ = arrayAppend(input_, input)  
            data_ = arrayAppend(data_, data) 
        
    trainSampleRow = random.sample(range(0, input_.shape[0]), int(input_.shape[0]*0.9)) 
    trainSampleRow = sorted(trainSampleRow)
    k = 0
    testSample=[]
    for n in range(input_.shape[0]):
        if n!=trainSampleRow[k]:
            testSample.append(n)
        elif n== trainSampleRow[k]:
            k = k+1
            if k >= len(trainSampleRow):
                break
        
    writeFile("dataRANS/train.txt", input_, trainSampleRow)    
    writeFile("dataRANS/trainRes.txt", data_, trainSampleRow)       
    writeFile("dataRANS/test.txt", input_, testSample)
    writeFile("dataRANS/testRes.txt", data_, testSample)       
     
# func 7
################################################################################
#@aim: load the training data
################################################################################            
def loadTrainingData():
    #dataInput()
    trainFeatures =  np.loadtxt("dataRANS/train.txt")
    trainResponses = np.loadtxt("dataRANS/trainRes.txt")       
    return trainFeatures, trainResponses

# func 8
################################################################################
#@aim: load the testing data
################################################################################    
def loadTestData():
    testFeatures = np.loadtxt("dataRANS/test.txt")
    testResponses = np.loadtxt("dataRANS/testRes.txt")
    return testFeatures, testResponses


# func 9
################################################################################
#@param1: trainFeatures - train features
#@param2: trainResponses - label values
#@param3: testFeatures - test features
#@param4: testResponses - label values for test
#@param5: score0 - initial score, for optimizing
#@param6: maxFeatures
#@param7: nTree
#@aim: train the regression model
################################################################################    
def randomForest(trainFeatures, trainResponses, testFeatures, testResponses, 
        score0, maxFeatures = 'log2', nTree=200):
    ## Settings of random forests regressor
    regModel = RandomForestRegressor(n_estimators=nTree, max_features=maxFeatures, 
               n_jobs=8, oob_score=True)    
    ## Train the random forests regressor
    regModel.fit(trainFeatures, trainResponses)
    importances = regModel.feature_importances_
    
    ## Prediction
    testResponsesPred = regModel.predict(testFeatures)
    score2 = regModel.score(testFeatures, testResponses)
    oob_error = 1-regModel.oob_score_
    score = accuracy(testResponses, testResponsesPred)
    print('score:', score2, 'oob_error:', oob_error)
    #  save model
    if(score<score0):
        with open("PINN_RANS_Model.pkl", "wb") as f:
            pickle.dump(regModel, f)
    return score, score2, importances


# func 10
################################################################################
#@param1: testResponsesPred - predicted values based on the test features
#@aim: save the predicted values
################################################################################
def output(testResponsesPred):
    fid=open('data_predict.txt','w')
    for n in range(testResponsesPred.shape[0]):
      for m in range(testResponsesPred.shape[1]):
         fid.write("%e  " % testResponsesPred[n][m])
      fid.write("\n")
    fid.close()


# func 11
################################################################################
#@aim: For optimizing, a mini train loop --- line 236 can be changed
################################################################################
def miniTrain(trainFeatures,trainResponses,testFeatures,testResponses,score0, 
              max_Feature, nTree=200):
    bestScore = score0
    print('Mini loop starts')
    for ml in range(1):
        score, score2, importance = randomForest(trainFeatures, trainResponses, 
                        testFeatures, testResponses, score0, max_Feature, nTree)
        if(score<bestScore):
            bestScore = score
            with open('structure.txt', 'w') as f:
                f.write('nTree: '+repr(nTree)+'\n');
                f.write('max_feature '+repr(max_Feature)+'\n')
                for mn in range(importance.shape[0]):
                    f.write(repr(importance[mn])+'\n')
            f.close()
        print('maxFreature: '+repr(max_Feature)+' nTree = '+repr(nTree)+' | score = '+repr(score)+' | best score = '+repr(bestScore));
        if(score<0.05):
            break
        if(score2<0):
            break
    print('Mini loop ends')
    return bestScore


################################################################################
# main
################################################################################      
trainFeatures, trainResponses = loadTrainingData()
testFeatures, testResponses = loadTestData()

score0 = 0.2
score = 1
score = miniTrain(trainFeatures,trainResponses,testFeatures,testResponses,score0, 9, 390)


# if want to optimize the max feature and nTree
"""
for n in range(1):
    for m in range(6, 16):
        for k in range(40):
            nTree = 200+10*k
            score = miniTrain(trainFeatures,trainResponses,testFeatures,testResponses,score0, m, nTree)
            score0 = score
            if(score<0.05):
                break
        if(score<0.05):
            break
    if(score<0.05):
        break          
"""            
            
            
            
            
