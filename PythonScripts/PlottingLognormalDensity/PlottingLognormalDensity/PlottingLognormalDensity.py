
import scipy.stats as stats
import numpy as np
import matplotlib.pyplot as plt
import math

def lognormalpdf(x, mu, sigma):
    if x == 0:
        return 0
    return (stats.norm.pdf(math.log(x), mu, sigma))/x

lognormalpdf = np.frompyfunc(lognormalpdf, 3, 1)

mu = 0
sigmapts = np.array([0.1,0.5,1.0])
xpts = np.linspace(0, 2, 100)
counter = 0

for sigma in sigmapts:
    counter+=1
    plt.subplot(1,3,counter)
    ypts = lognormalpdf(xpts, mu, sigma)
    plt.plot(xpts, ypts)
    plt.title(r'$\sigma$ = %1.1f '%sigma)
    mean, median, mode = math.exp(mu+0.5*sigma*sigma), math.exp(mu), math.exp(mu-sigma*sigma)
    m = np.array([mean, median, mode])
    ypts2 = np.array([0, 1.1* lognormalpdf(mode, mu, sigma)])
    for x in m:
        xpts2 = np.array([x, x])
        plt.plot(xpts2, ypts2)

plt.suptitle('Density of log-normal variable')
plt.show()