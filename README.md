This is an example for our paper "Huakun Huang, Qingmo Xie, Tai'an Hu, Huan Hu, Peng Yu, A random forest machine learning in turbulence closure modeling for complex flows and heat transfer based on the non-equilibrium turbulence assumption" [Download the preprint](https://papers.ssrn.com/sol3/papers.cfm?abstract_id=5017217)

[1] Go to the getTrainData folder, you can prepare your data according to the guidance. Or download my training data directly from Google Drive and put these data into the dataRANS folder. The safe link: https://drive.google.com/drive/folders/174UHlnLEjkaPs7ElPy_h6lumgCCTHBng?usp=sharing

[2] Download sources, and compile them. Detailed guidance can be found in the sources folder.

[3] Run the Python file "randomForest.py". 
    if there is no error, you may get the following information: 
    
    <img src="https://github.com/user-attachments/assets/574075f6-46e4-4dcc-a32a-c66f3a6094b3" alt="output" width="600" title="output">

    You can also download our well-trained model through the following link:
    https://pan.baidu.com/s/1c5_if2aKbJk1xDyD-3vZxw?pwd=yxsj
    Extract the code: yxsj
    
[4] Compute the relative error. Run the Python file "testError.py". The output error file is "errors.txt"

[5] Plot the RMS error and the relative error. Run the Python file "errorPlot.py"
    ![RFErrors](https://github.com/user-attachments/assets/03adc12c-d8dd-4f96-ba12-400e0540310a)
    ![densitys](https://github.com/user-attachments/assets/4d87e1c1-162b-46f5-bb33-171125a755d4)

[6] If everything is OK, you can go to the testCase folder and try the method according to the guidance.

**Some possible problems:**
- When load the pkl model, the application is killed.
  
  Insufficient memory may cause the system to terminate processes.
