
import matplotlib.pyplot as plt
import numpy as np

def Make2DPlot(filename, multiple_plots):
    with open(filename) as f:
        title=f.readline()
        xlabel=f.readline()
        ylabel=f.readline()
        data=np.loadtxt(f)
        f.close() 
    
    data=np.transpose(data)
    xpts=data[0]
    ypts=data[1]

    plt.xlabel(xlabel)
    plt.plot(xpts, ypts, label=title)
    if multiple_plots == False:
        plt.ylabel(ylabel)
        plt.title(title)

multiple_plots = True
if multiple_plots == False:
    Make2DPlot(r"C:\Users\Win10\Documents\TheConceptsAnd...ComputerProjects\Project 1\BSCall.txt", False)
    plt.show()
elif multiple_plots == True:
    FileNames = np.array([r"C:\Users\Win10\Documents\TheConceptsAnd...ComputerProjects\Project 1\BSPut.txt"
                          ,r"C:\Users\Win10\Documents\TheConceptsAnd...ComputerProjects\Project 1\Intrinsic value.txt"])
      
    for x in FileNames:
        Make2DPlot(x, multiple_plots)
    plt.title('BSPut vs. Intrinsic value (Strike = 100)')
    plt.ylabel('Price')
    plt.legend(loc=0)
    plt.show()





