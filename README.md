This is an example for our paper "A random forest machine learning in turbulence closure modeling for complex flows and heat transfer based on the non-equilibrium turbulence assumption"

[1] First, download sources, and compile them. Detailed guidance can be found in the sources folder.

[2] Go to the getTrainData folder, you can prepare your data according to the guidance. Or download my training data directly from Google Drive and put these data into the dataRANS folder. The safe link: https://drive.google.com/drive/folders/174UHlnLEjkaPs7ElPy_h6lumgCCTHBng?usp=sharing

[3] Run the Python file "randomForest.py". 
    if no error, you may get the following information: 
    ![rf](https://github.com/user-attachments/assets/574075f6-46e4-4dcc-a32a-c66f3a6094b3)
    
[4] Compute the relative error. Run the Python file "testError.py". The output error file is "errors.txt"

[5] Plot the RMS error and the relative error. Run the Python file "errorPlot.py"
    ![RFErrors](https://github.com/user-attachments/assets/03adc12c-d8dd-4f96-ba12-400e0540310a)
    ![densitys](https://github.com/user-attachments/assets/4d87e1c1-162b-46f5-bb33-171125a755d4)

[6] If everything is OK, you can go to the testCase folder and try the method according to the guidance.
