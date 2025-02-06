import math as mt
import numpy as np

data = np.loadtxt('outputResult.txt')
print('Minimum value of energy production term : '+repr(min(data[:,0])))
print('Minimum value of energy destruction term : '+repr(min(data[:,1])))
print('Minimum value of dissipation production term : '+repr(min(data[:,2])))
print('Minimum value of dissipation destruction term : '+repr(min(data[:,3])))
if min(data[:,0])<0 or min(data[:,1])<0 or min(data[:,2])<0 or min(data[:,3])<0 :
    print("Warning, it should be noted that any value should be larger than zero")
else:
    print("The prediction is OK")