
import scipy.stats as stats
import numpy as np
import matplotlib.pyplot as plt
import math

def lognormalpdf(x, mu, sigma):
    if x == 0:
        return 0
    return (stats.norm.pdf(math.log(x), mu, sigma))/x

lognormalpdf = np.frompyfunc(lognormalpdf, 3, 1)

mu, sigma = 0, 1
xpts = np.linspace(2, 5, 100)

ypts1 = lognormalpdf(xpts, mu, sigma)
ypts2 = stats.norm.pdf(xpts, mu, sigma)
plt.plot(xpts, ypts1, label='lognormal')
plt.plot(xpts, ypts2, label='normal')
plt.title('Tails of lognormal density versus normal density ($\mu, \sigma$ = (0,1))')
plt.legend(loc=0)
plt.show()
