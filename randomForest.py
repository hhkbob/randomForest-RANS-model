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

def accuracy(y_true, y_pre):
    score = 0
    for n in range(y_true.shape[0]):
        for m in range(y_true.shape[1]):
            score = score + (y_true[n][m]-y_pre[n][m])*(y_true[n][m]-y_pre[n][m])
    score = mt.sqrt(score/(y_true.shape[0]*y_true.shape[1]))
    return score

def writeFile(fileName, input, rows):
    k=0
    with open(fileName, 'w') as f:
        for n in range(len(rows)):
            for m in range(input.shape[1]):
                f.write(repr(input[rows[n]][m])+'\t');
            f.write('\n');
    f.close()

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
      
#load inputFeature and outputFeatures
def dataInput():
    trainFolder = [ 
      'Impingement_round_23000_H2',             #transition, flow separation, heat transfer, incompressible
      'Impingement_round_23000_H7',             #no transition, heat transfer, incompressible
      'Impingement_round_23000_H10',            #no transition, heat transfer, incompressible
      'Impingement_round_23000_H14',            #no transition, heat transfer, incompressible
      'Impingement_round_30000_H1',             #transition or flow separation, compressible
      'Impingement_plane_10000_H2',
      'Impingement_plane_20000_H4',
      'Impingement_plane_20000_H5',
      'Impingement_plane_20000_H7',
      'Impingement_plane_30000_H2',
      'Impingement_plane_11000_H6',
      'Impingement_plane_20000_H9.2',
      'Swirling_pipe_flow_Re_10000',            #strong swirling flow, incompressible
      #'pit',                                    #flow separation, incompressible
      'T3A',                                    #transition, incompressible
      'T3B-',                                   #transition, incompressible
      'T3A2-',                                  #transition, incomressiblem
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
        
    trainSampleRow = random.sample(range(0, input_.shape[0]-1), int(input_.shape[0]*0.9)) 
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
     
            
def loadTrainingData():
    dataInput()
    trainFeatures =  np.loadtxt("dataRANS/train.txt")
    trainResponses = np.loadtxt("dataRANS/trainRes.txt")       
    return trainFeatures, trainResponses
    
def loadTestData():
    testFeatures = np.loadtxt("dataRANS/test.txt")
    testResponses = np.loadtxt("dataRANS/testRes.txt")
    return testFeatures, testResponses

    
def randomForest(trainFeatures, trainResponses, testFeatures, testResponses, score0, maxFeatures = 'log2', nTree=200):
    ## Settings of random forests regressor
    regModel = RandomForestRegressor(n_estimators=nTree, max_features=maxFeatures)    
    ## Train the random forests regressor
    regModel.fit(trainFeatures, trainResponses)
    importances = regModel.feature_importances_
    
    ## Prediction
    testResponsesPred = regModel.predict(testFeatures)
    score2 = regModel.score(testFeatures, testResponses)
    score = accuracy(testResponses, testResponsesPred)
    print(score2)
    #  save model
    if(score<score0):
        with open("/home/hhk/OpenFOAM/PINN_RANS_Model.pkl", "wb") as f:
            pickle.dump(regModel, f)
    return score, score2, importances

def output(testResponsesPred):
    fid=open('data_predict.txt','w')
    for n in range(testResponsesPred.shape[0]):
      for m in range(testResponsesPred.shape[1]):
         fid.write("%e  " % testResponsesPred[n][m])
      fid.write("\n")
    fid.close()

def miniTrain(trainFeatures,trainResponses,testFeatures,testResponses,score0, max_Feature, nTree=200):
    bestScore = score0
    print('Mini loop starts')
    for ml in range(1):
        score, score2, importance = randomForest(trainFeatures, trainResponses, testFeatures, testResponses, score0, max_Feature, nTree)
        if(score<bestScore):
            bestScore = score
            with open('structure.txt', 'w') as f:
                f.write('nTree: '+repr(nTree)+'\n');
                f.write('max_feature '+repr(max_Feature)+'\n')
                for mn in range(importance.shape[0]):
                    f.write(repr(importance[mn])+'\n')
            f.close()
        print('maxFreature: '+repr(max_Feature)+' nTree = '+repr(nTree)+' | score = '+repr(score)+' | best score = '+repr(bestScore));
        break
        """
        if(score<0.05):
            break
        if(score2<0):
            break
        """
    """
    print('Mini loop ends')
    return bestScore
    """


os.system('mkdir dataRANS')       
trainFeatures, trainResponses = loadTrainingData()
testFeatures, testResponses = loadTestData()

score0 = 0.105
score = 1



nTree = 300
feature = testFeatures.shape[1]
maxFeature = int(round(mt.log(feature, 2), 0))+1
score0 = 1
print(maxFeature)
score = miniTrain(trainFeatures,trainResponses,testFeatures,testResponses,score0, maxFeature, nTree)
score0 = score
print(score)
         
            
            
            