import numpy as np
import matplotlib.pyplot as plt

N = 1
menMeans = (39181)
menStd =   (25192)

ind = np.arange(N)  # the x locations for the groups
width = 0.35       # the width of the bars

fig, ax = plt.subplots()
rects1 = ax.bar(ind, menMeans, width, color='r')

womenMeans = (25192)
womenStd =   (25192)
rects2 = ax.bar(ind+width, womenMeans, width, color='b')

# add some text for labels, title and axes ticks
ax.set_ylabel('Time')
#ax.set_title('Scores by group and gender')
ax.set_xticks(ind+width)
ax.set_xticklabels( ('Key Insert/Delete/Lookup', 'Key Insert/Delete/Lookup') )

ax.legend( (rects1[0], rects2[0]), ('Chord', 'Pastry') )

def autolabel(rects):
    # attach some text labels
    for rect in rects:
        height = rect.get_height()
        ax.text(rect.get_x()+rect.get_width()/2., 1.05*height, '%d'%int(height),
                ha='center', va='bottom')

autolabel(rects1)
autolabel(rects2)

plt.show()