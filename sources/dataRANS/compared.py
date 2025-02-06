################################################################################
# Output the inputFeatures.txt
# Output the ratio.txt
# random
################################################################################

import numpy as np
import time, random, os

def check_directory_exists(dir_path, create):
    if os.path.isdir(dir_path):
        return True
    else:
        if create:
            os.system('mkdir ' + dir_path)
        else:
            print(dir_path+' does not exist')
        return False

# test dataRANS
dirs = 'dataRANS'
exists = check_directory_exists(dirs, True) 

#Test RANS folder
exists = check_directory_exists('RANS', False)
if exists==False:
    print('RANS folder does not exist')
exists2 = check_directory_exists('Fidelity', False)
if exists2==False:
    print('Fidelity folder does not exist')

if exists and exists2:
    ras = np.loadtxt('RANS/energy.txt')
    les = np.loadtxt('Fidelity/energy.txt')
    input = np.loadtxt('RANS/inputFeatures.txt')

    Pk_ras = ras[:,0]
    Pk_les = les[:,0]

    #delete odd data
    critical = 2.

    Pk = Pk_les/Pk_ras
    Dk = les[:,1]/ras[:,1]
    Pw = les[:,2]/ras[:,2]
    Dw = les[:,3]/ras[:,3]

###############################################
    size = 1
    try:
        size = np.loadtxt('size.txt')
    except (IOError, ValueError) as e:
        size = 1
###############################################
    maxmumCell = len(Dk)
    trainSampleRow = random.sample(range(0, maxmumCell), int(len(Dk)*size))
    print('Random output results')
    with open('dataRANS/inputFeatures.txt', 'w') as fi:
        with open('dataRANS/ratio.txt', 'w') as f:
          for n in range(len(trainSampleRow)):
            row = trainSampleRow[n]
            if(Pk[row]>critical or Dk[row]>critical or Pw[row]>critical or Dw[row]>critical):
                continue
            if Pk[row]<0 or Dk[row]<0 or Pw[row]<0 or Dw[row]<0 :
                continue
            f.write(repr(Pk[row])+'\t')
            f.write(repr(Dk[row])+'\t')
            f.write(repr(Pw[row])+'\t')
            f.write(repr(Dw[row])+'\n')
            for k in range(input.shape[1]):
                fi.write(repr(input[row][k])+'\t')
            fi.write('\n')
        f.close()
    fi.close()
else:
    print('Please check your folder')
