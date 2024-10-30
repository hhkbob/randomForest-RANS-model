import numpy as np
import matplotlib.pyplot as plt
import time
from mpl_toolkits.axes_grid1.inset_locator import inset_axes
import matplotlib.ticker as ticker

from scipy.stats import gaussian_kde

def count(data, down, up):
    num = 0
    for n in range(len(data)):
        if( data[n] > down and data[n]<up or abs(data[n]-down)<5e-5):
            num += 1
    return num/len(data)

def plotError(num):
    # read the RMS error
    data = np.loadtxt('error.txt')
    #2%
    num1 = count(data, 0, 0.05)
    #4%
    num2 = count(data, 0.05, 0.1) 
    #num3 = count(data, 0.04, 0.06) 
    #
    #num4 = count(data, 0.06, 0.08) 
    #
    #num5 = count(data, 0.08, 0.1) 
    #
    num6 = count(data, 0.1, 0.2)
    #
    num7 = count(data, 0.2, 0.4) 
    #
    num8 = count(data, 0.4, 0.6) 
    #
    num9 = count(data, 0.6, 0.8) 

    num10 = count(data, 0.8, 1e8) 

    categories2 = [0.025, 0.075, 0.15, 0.3, 0.5, 0.7, 0.9]
    categories = ['[0, 5)', '[5, 10)', '[10,20)', '[20,40)', '[40,60)', '[60,80)', '\\geq 80']
    values = [num1, num2, num6, num7, num8, num9, num10]
    for n in range(len(values)):
        categories[n] = '$\\mathrm{ '+categories[n]+ ' }$'
        values[n] = values[n]*100
    #colors = ['g', '#f16913', '#d94801', '#969696', '#a8ddb5', '#7bccc4', '#4eb3d3', '#2b8cbe', '#0868ac', '#084081']
    colors = ['#4e79a7', '#f28e2b', '#e15759', '#76b7b2', '#59a14f', '#edc948', '#b07aa1']

    fontSize = 14
    Fonts = 'DejaVu Sans'
    #- set font style
    config={
       "font.family":'serif',
       "font.size":fontSize,
       "mathtext.fontset":'stix',
       "font.serif":[Fonts],
    }
    plt.rcParams.update(config)

    # 设置刻度字体为Times New Roman
    plt.xticks(fontproperties='Times New Roman', fontsize=fontSize-1)
    plt.yticks(fontproperties='Times New Roman', fontsize=fontSize-1)

    # 设置背景颜色
    fig, ax = plt.subplots()
    #fig.patch.set_facecolor('lightgrey')
    #ax.set_facecolor('lightgrey')
    bars = ax.bar(categories, values, color=colors, width=0.5)
    #ax.plot(categories2, values, '-', linewidth=0.75, color='r')

    # 显示柱体数值大小
    for bar in bars:
        height = bar.get_height()
        ax.text(bar.get_x() + bar.get_width() / 2.0, height, f'{height:.2f}', ha='center', va='bottom', fontsize=fontSize-2, fontproperties='Times New Roman')

    plt.xlabel('$\\mathrm{Error \\ (\\%)}$',  fontsize=fontSize)
    plt.ylabel('$\\mathrm{Percentage \\ (\\%)}$', fontsize=fontSize)
    plt.ylim(0, 100)

    # 获取现有的 tick 标签
    yticks = ax.get_yticklabels()
    xticks = ax.get_xticklabels()
    ytickLabel=yticks 
    xtickLabel=xticks
    
    for m in range(len(yticks)):
        tick = yticks[m]
        text = tick.get_text()    
        ytickLabel[m] = '$\\mathrm{'+text+'}$' 
        
    #更改坐标轴的tick标签
    ax.yaxis.set_major_locator(ticker.FixedLocator(ax.get_yticks()))
    #ax.xaxis.set_major_locator(ticker.FixedLocator(ax.get_xticks()))

    ax.set_yticklabels(ytickLabel) 
    #ax.set_xticklabels(xtickLabel) 

    # 去掉图片空白
    plt.tight_layout()

    plt.savefig('RFErrors.pdf')
    plt.close()
    
    
    ##################################################################
    # read the ralative error
    data = np.loadtxt('errors.txt')
    fig, ax = plt.subplots()
    plt.rcParams.update(config)
    x0 = min(data)
    h = 0.01
    values=[]
    xv = []
    for n in range(len(data)):
        x1 = h+x0
        v = count(data, x0, x1)
        values.append(v*100)
        xv.append(x1*100)
        x0 = x1
        if x0+h >1:
            break
            
    ax.plot(xv, values)
    #plt.ylim(0, 70)
    #plt.xlim(-100, 100)
    
    plt.xlabel('$\\mathrm{Relative \\ error \\ (\\%)}$',  fontsize=fontSize)
    plt.ylabel('$\\mathrm{Percentage \\ (\\%)}$', fontsize=fontSize)
    #plt.ylim(0, 100)

    # 获取现有的 tick 标签
    yticks = ax.get_yticklabels()
    xticks = ax.get_xticklabels()
    ytickLabel=yticks 
    xtickLabel=xticks
    
    for m in range(len(yticks)):
        tick = yticks[m]
        text = tick.get_text()    
        ytickLabel[m] = '$\\mathrm{'+text+'}$' 

    for m in range(len(xticks)):
        tick = xticks[m]
        text = tick.get_text()    
        xtickLabel[m] = '$\\mathrm{'+text+'}$'
        
    #更改坐标轴的tick标签
    ax.yaxis.set_major_locator(ticker.FixedLocator(ax.get_yticks()))
    ax.xaxis.set_major_locator(ticker.FixedLocator(ax.get_xticks()))

    ax.set_yticklabels(ytickLabel) 
    ax.set_xticklabels(xtickLabel)    
    
    plt.tight_layout()
    plt.savefig('densitys.pdf')
    
plotError(1)